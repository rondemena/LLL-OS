/******************************************************************************
 * include/xen-private/grant_table.h
 * 
 * Mechanism for granting foreign access to page frames, and receiving
 * page-ownership transfers.
 * 
 * Copyright (c) 2004-2005 K A Fraser
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __XEN_GRANT_TABLE_H__
#define __XEN_GRANT_TABLE_H__

#include <linux/config.h>
#include <public/grant_table.h>
#include <asm/grant_table.h>

/* Active grant entry - used for shadowing GTF_permit_access grants. */
struct active_grant_entry {
    u32           pin;    /* Reference count information.  */
    domid_t       domid;  /* Domain being granted access.  */
    unsigned long frame;  /* Frame being granted.          */
};

 /* Count of writable host-CPU mappings. */
#define GNTPIN_hstw_shift    (0)
#define GNTPIN_hstw_inc      (1 << GNTPIN_hstw_shift)
#define GNTPIN_hstw_mask     (0xFFU << GNTPIN_hstw_shift)
 /* Count of read-only host-CPU mappings. */
#define GNTPIN_hstr_shift    (8)
#define GNTPIN_hstr_inc      (1 << GNTPIN_hstr_shift)
#define GNTPIN_hstr_mask     (0xFFU << GNTPIN_hstr_shift)
 /* Count of writable device-bus mappings. */
#define GNTPIN_devw_shift    (16)
#define GNTPIN_devw_inc      (1 << GNTPIN_devw_shift)
#define GNTPIN_devw_mask     (0xFFU << GNTPIN_devw_shift)
 /* Count of read-only device-bus mappings. */
#define GNTPIN_devr_shift    (24)
#define GNTPIN_devr_inc      (1 << GNTPIN_devr_shift)
#define GNTPIN_devr_mask     (0xFFU << GNTPIN_devr_shift)

#define NR_GRANT_FRAMES      (1U << ORDER_GRANT_FRAMES)
#define NR_GRANT_ENTRIES     \
    ((NR_GRANT_FRAMES << PAGE_SHIFT) / sizeof(grant_entry_t))

/*
 * Tracks a mapping of another domain's grant reference. Each domain has a
 * table of these, indexes into which are returned as a 'mapping handle'.
 */
struct grant_mapping {
    u32      ref;           /* grant ref */
    u16      flags;         /* 0-4: GNTMAP_* ; 5-15: unused */
    domid_t  domid;         /* granting domain */
};

/* Fairly arbitrary. [POLICY] */
#define MAPTRACK_MAX_ENTRIES 16384

/* Per-domain grant information. */
struct grant_table {
    /* Shared grant table (see include/public/grant_table.h). */
    struct grant_entry   *shared;
    /* Active grant table. */
    struct active_grant_entry *active;
    /* Mapping tracking table. */
    struct grant_mapping *maptrack;
    unsigned int          maptrack_head;
    unsigned int          maptrack_order;
    unsigned int          maptrack_limit;
    unsigned int          map_count;
    /* Lock protecting updates to active and shared grant tables. */
    spinlock_t            lock;
};

/* Create/destroy per-domain grant table context. */
int grant_table_create(
    struct domain *d);
void grant_table_destroy(
    struct domain *d);

/* Domain death release of granted mappings of other domains' memory. */
void
gnttab_release_mappings(
    struct domain *d);

#endif /* __XEN_GRANT_TABLE_H__ */
