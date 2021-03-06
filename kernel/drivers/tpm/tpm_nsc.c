/*
 * Copyright (C) 2004 IBM Corporation
 *
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Dave Safford <safford@watson.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Maintained by: <tpmdd_devel@lists.sourceforge.net>
 *
 * Device driver for TCG/TCPA TPM (trusted platform module).
 * Specifications at www.trustedcomputinggroup.org	 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2 of the
 * License.
 *
 * KW: Modified for Nexus.
 * 
 */

#include "tpm.h"

/* National definitions */
enum tpm_nsc_addr {
	TPM_NSC_IRQ = 0x07,
	TPM_NSC_BASE0_HI = 0x60,
	TPM_NSC_BASE0_LO = 0x61,
	TPM_NSC_BASE1_HI = 0x62,
	TPM_NSC_BASE1_LO = 0x63
};

enum tpm_nsc_index {
	NSC_LDN_INDEX = 0x07,
	NSC_SID_INDEX = 0x20,
	NSC_LDC_INDEX = 0x30,
	NSC_DIO_INDEX = 0x60,
	NSC_CIO_INDEX = 0x62,
	NSC_IRQ_INDEX = 0x70,
	NSC_ITS_INDEX = 0x71
};

enum tpm_nsc_status_loc {
	NSC_STATUS = 0x01,
	NSC_COMMAND = 0x01,
	NSC_DATA = 0x00
};

/* status bits */
enum tpm_nsc_status {
	NSC_STATUS_OBF = 0x01,	/* output buffer full */
	NSC_STATUS_IBF = 0x02,	/* input buffer full */
	NSC_STATUS_F0 = 0x04,	/* F0 */
	NSC_STATUS_A2 = 0x08,	/* A2 */
	NSC_STATUS_RDY = 0x10,	/* ready to receive command */
	NSC_STATUS_IBR = 0x20	/* ready to receive data */
};

/* command bits */
enum tpm_nsc_cmd_mode {
	NSC_COMMAND_NORMAL = 0x01,	/* normal mode */
	NSC_COMMAND_EOC = 0x03,
	NSC_COMMAND_CANCEL = 0x22
};

/*
 * Wait for a certain status to appear
 */
static int wait_for_stat(struct tpm_chip *chip, u8 mask, u8 val, u8 * data)
{
	/* status immediately available check */
	int i;
	for (i = 0; i < 4; i++) {
	  *data = inb(chip->vendor->base + NSC_STATUS);
	  if ((*data & mask) == val) 
		  return 0;
	}

	/* wait for status */
	unsigned long stop = jiffies + 10 * HZ;
	do {
		nexusthread_sleep(TPM_TIMEOUT);
		*data = inb(chip->vendor->base + 1);
		if ((*data & mask) == val) 
			return 0;
	} while (time_before(jiffies, stop));
	return -EBUSY;
}

static int nsc_wait_for_ready(struct tpm_chip *chip)
{
	int status;

	/* status immediately available check */
	int i;
	for (i = 0; i < 4; i++) {
	  status = inb(chip->vendor->base + NSC_STATUS);
	  if (status & NSC_STATUS_OBF)
		  status = inb(chip->vendor->base + NSC_DATA);
	  if (status & NSC_STATUS_RDY)
		  return 0;
	}

	/* wait for status */
	unsigned long stop = jiffies + 100;
	do {
		nexusthread_sleep(TPM_TIMEOUT);
		status = inb(chip->vendor->base + NSC_STATUS);
		if (status & NSC_STATUS_OBF)
			status = inb(chip->vendor->base + NSC_DATA);
		if (status & NSC_STATUS_RDY) 
			return 0;
		printk_red(".");
	} while (time_before(jiffies, stop));
	printk_red("%s: wait for ready failed\n", chip->dev->name);
	return -EBUSY;
}


static int tpm_nsc_recv(struct tpm_chip *chip, u8 * buf, size_t count)
{
	u8 *buffer = buf;
	u8 data, *p;
	u32 size;
	__be32 *native_size;

	if (count < 6)
		return -EIO;

	if (wait_for_stat(chip, NSC_STATUS_F0, NSC_STATUS_F0, &data) < 0) {
		printk("%s: F0 timeout\n", chip->dev->name);
		return -EIO;
	}
	if ((data =
	     inb(chip->vendor->base + NSC_DATA)) != NSC_COMMAND_NORMAL) {
		 printk("%s: not in normal mode (0x%x)\n", chip->dev->name,
				data);
		return -EIO;
	}

	/* read the whole packet */
	for (p = buffer; p < &buffer[count]; p++) {
		if (wait_for_stat
		    (chip, NSC_STATUS_OBF, NSC_STATUS_OBF, &data) < 0) {
		 printk("%s: OBF timeout (while reading data)\n", chip->dev->name);
			return -EIO;
		}
		if (data & NSC_STATUS_F0)
			break;
		*p = inb(chip->vendor->base + NSC_DATA);
	}

	if ((data & NSC_STATUS_F0) == 0 &&
	(wait_for_stat(chip, NSC_STATUS_F0, NSC_STATUS_F0, &data) < 0)) {
		printk("%s: F0 not set\n", chip->dev->name);
		return -EIO;
	}
	if ((data = inb(chip->vendor->base + NSC_DATA)) != NSC_COMMAND_EOC) {
		printk("%s: expected end of command(0x%x)\n", chip->dev->name,
				data);
		return -EIO;
	}

	native_size = (__be32 *) (buf + 2);
	size = be32_to_cpu(*native_size);

	if (count < size)
		return -EIO;

	return size;
}

static int tpm_nsc_send(struct tpm_chip *chip, u8 * buf, size_t count)
{
	u8 data;
	int i;

	/*
	 * If we hit the chip with back to back commands it locks up
	 * and never set IBF. Hitting it with this "hammer" seems to
	 * fix it. Not sure why this is needed, we followed the flow
	 * chart in the manual to the letter.
	 */
	outb(NSC_COMMAND_CANCEL, chip->vendor->base + NSC_COMMAND);

	if (nsc_wait_for_ready(chip) != 0)
		return -EIO;

	if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
		printk("%s: IBF timeout\n", chip->dev->name);
		return -EIO;
	}

	outb(NSC_COMMAND_NORMAL, chip->vendor->base + NSC_COMMAND);
	if (wait_for_stat(chip, NSC_STATUS_IBR, NSC_STATUS_IBR, &data) < 0) {
		printk("%s: IBR timeout\n", chip->dev->name);
		return -EIO;
	}

	for (i = 0; i < count; i++) {
		if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
			printk("%s: IBF timeout (while writing data)\n", chip->dev->name);
			return -EIO;
		}
		outb(buf[i], chip->vendor->base + NSC_DATA);
	}

	if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
		printk("%s: IBF timeout\n", chip->dev->name);
		return -EIO;
	}
	outb(NSC_COMMAND_EOC, chip->vendor->base + NSC_COMMAND);

	return count;
}

static void tpm_nsc_cancel(struct tpm_chip *chip)
{
	outb(NSC_COMMAND_CANCEL, chip->vendor->base + NSC_COMMAND);
}

static u8 tpm_nsc_status(struct tpm_chip *chip)
{
	return inb(chip->vendor->base + NSC_STATUS);
}

static void cleanup_nsc(void);

static struct tpm_vendor_specific tpm_nsc = {
	.recv = tpm_nsc_recv,
	.send = tpm_nsc_send,
	.cancel = tpm_nsc_cancel,
	.status = tpm_nsc_status,
	.req_complete_mask = NSC_STATUS_OBF,
	.req_complete_val = NSC_STATUS_OBF,
	.req_canceled = NSC_STATUS_RDY,
	.ops = { 
		.open = tpm_open,
		.read = tpm_read,
		.write = tpm_write,
		.release = tpm_release,
		.shutdown = cleanup_nsc,
	},
	.name = "nsc",
};

static struct tpm_chip *nsc_chip_present = NULL;

static void __devexit tpm_nsc_remove(struct lpc_dev *dev)
{
	struct tpm_chip *chip = dev->driver_data;
	assert(chip == nsc_chip_present);
	if (chip) {
		release_region(chip->vendor->base, 2);
		tpm_remove_hardware(chip);
		nsc_chip_present = NULL;
	}
}

int __init init_nsc(void)
{
	int rc = 0;
	int lo, hi;
	int nscAddrBase = TPM_ADDR;

	/* verify that it is a National Semiconductor chip (SID) */
	if (tpm_read_index(TPM_ADDR, NSC_SID_INDEX) != 0xEF) {
		nscAddrBase = (tpm_read_index(TPM_SUPERIO_ADDR, 0x2C)<<8)|
			(tpm_read_index(TPM_SUPERIO_ADDR, 0x2B)&0xFE);
		if (tpm_read_index(nscAddrBase, NSC_SID_INDEX) != 0xF6)
			return -ENODEV;
	}

	hi = tpm_read_index(nscAddrBase, TPM_NSC_BASE0_HI);
	lo = tpm_read_index(nscAddrBase, TPM_NSC_BASE0_LO);
	tpm_nsc.base = (hi<<8) | lo;

	/* enable the DPM module */
	tpm_write_index(nscAddrBase, NSC_LDC_INDEX, 0x01);

	if (request_region(tpm_nsc.base, 2, "tpm_nsc0") == NULL)
		return -EBUSY;

	if ((rc = tpm_register_hardware("tpm", &tpm_nsc, &nsc_chip_present)) < 0) {
		release_region(tpm_nsc.base, 2);
		return rc;
	}

	printk("%s: NSC LDN 0x%x, SID 0x%x, SRID 0x%x\n",
		nsc_chip_present->dev->name,
		tpm_read_index(nscAddrBase,0x07), tpm_read_index(nscAddrBase,0x20),
		tpm_read_index(nscAddrBase,0x27));
	printk("%s: NSC SIOCF1 0x%x SIOCF5 0x%x SIOCF6 0x%x SIOCF8 0x%x\n",
		nsc_chip_present->dev->name,
		tpm_read_index(nscAddrBase,0x21), tpm_read_index(nscAddrBase,0x25),
		tpm_read_index(nscAddrBase,0x26), tpm_read_index(nscAddrBase,0x28));
	printk("%s: NSC IO Base0 0x%x\n",
		nsc_chip_present->dev->name,
		(tpm_read_index(nscAddrBase,0x60) << 8) | tpm_read_index(nscAddrBase,0x61));
	printk("%s: NSC IO Base1 0x%x\n",
		nsc_chip_present->dev->name,
		(tpm_read_index(nscAddrBase,0x62) << 8) | tpm_read_index(nscAddrBase,0x63));
	printk("%s: NSC Interrupt number and wakeup 0x%x\n",
		nsc_chip_present->dev->name,
		tpm_read_index(nscAddrBase,0x70));
	printk("%s: NSC IRQ type select 0x%x\n",
		nsc_chip_present->dev->name,
		tpm_read_index(nscAddrBase,0x71));
	printk("%s: NSC DMA channel select0 0x%x, select1 0x%x\n",
		nsc_chip_present->dev->name,
		tpm_read_index(nscAddrBase,0x74), tpm_read_index(nscAddrBase,0x75));
	printk("%s: NSC Config "
		"0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
		nsc_chip_present->dev->name,
		tpm_read_index(nscAddrBase,0xF0), tpm_read_index(nscAddrBase,0xF1),
		tpm_read_index(nscAddrBase,0xF2), tpm_read_index(nscAddrBase,0xF3),
		tpm_read_index(nscAddrBase,0xF4), tpm_read_index(nscAddrBase,0xF5),
		tpm_read_index(nscAddrBase,0xF6), tpm_read_index(nscAddrBase,0xF7),
		tpm_read_index(nscAddrBase,0xF8), tpm_read_index(nscAddrBase,0xF9));
	printk("%s: NSC TPM revision %d\n",
		nsc_chip_present->dev->name,
		tpm_read_index(nscAddrBase, 0x27) & 0x1F);

	return 0;
}

static void cleanup_nsc(void)
{
	if (nsc_chip_present)
		tpm_nsc_remove(nsc_chip_present->dev);
}

//module_init(init_nsc);
//module_exit(cleanup_nsc);

MODULE_AUTHOR("Leendert van Doorn (leendert@watson.ibm.com)");
MODULE_DESCRIPTION("TPM Driver");
//MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
