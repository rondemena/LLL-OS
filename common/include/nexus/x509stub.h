#ifndef __X509STUB_H__
#define __X509STUB_H__
/* This header file contains the stubs that the Nexus uses to get a
 * valid signature for an X509.  
 */

#define NEXUS_X509_NAME issuername
#define NEXUS_X509_NAME_LEN issuername_len
#define NEXUS_X509_SUBJ subjname
#define NEXUS_X509_SUBJ_LEN subjname_len
#define NEXUS_X509_SUBJ_IPD_OFFSET subjname_ipdoff

unsigned char issuername[] = {
  0x30, 0x7b, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
  0x02, 0x55, 0x53, 0x31, 0x11, 0x30, 0x0f, 0x06, 0x03, 0x55, 0x04, 0x08,
  0x13, 0x08, 0x4e, 0x65, 0x77, 0x20, 0x59, 0x6f, 0x72, 0x6b, 0x31, 0x0f,
  0x30, 0x0d, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x06, 0x49, 0x74, 0x68,
  0x61, 0x63, 0x61, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x04, 0x0a,
  0x13, 0x18, 0x43, 0x6f, 0x72, 0x6e, 0x65, 0x6c, 0x6c, 0x20, 0x55, 0x6e,
  0x69, 0x76, 0x65, 0x72, 0x73, 0x69, 0x74, 0x79, 0x20, 0x4e, 0x65, 0x78,
  0x75, 0x73, 0x31, 0x0d, 0x30, 0x0b, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13,
  0x04, 0x4e, 0x4f, 0x4e, 0x45, 0x31, 0x16, 0x30, 0x14, 0x06, 0x03, 0x55,
  0x04, 0x03, 0x13, 0x0d, 0x54, 0x72, 0x75, 0x73, 0x74, 0x65, 0x64, 0x20,
  0x4e, 0x65, 0x78, 0x75, 0x73
};
unsigned int issuername_len = 125;

unsigned char subjname[] = {
  0x30, 0x81, 0x96, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06,
  0x13, 0x02, 0x55, 0x53, 0x31, 0x11, 0x30, 0x0f, 0x06, 0x03, 0x55, 0x04,
  0x08, 0x13, 0x08, 0x4e, 0x65, 0x77, 0x20, 0x59, 0x6f, 0x72, 0x6b, 0x31,
  0x0f, 0x30, 0x0d, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x06, 0x49, 0x74,
  0x68, 0x61, 0x63, 0x61, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x04,
  0x0a, 0x13, 0x18, 0x43, 0x6f, 0x72, 0x6e, 0x65, 0x6c, 0x6c, 0x20, 0x55,
  0x6e, 0x69, 0x76, 0x65, 0x72, 0x73, 0x69, 0x74, 0x79, 0x20, 0x4e, 0x65,
  0x78, 0x75, 0x73, 0x31, 0x0d, 0x30, 0x0b, 0x06, 0x03, 0x55, 0x04, 0x0b,
  0x13, 0x04, 0x4e, 0x4f, 0x4e, 0x45, 0x31, 0x31, 0x30, 0x2f, 0x06, 0x03,
  0x55, 0x04, 0x03, 0x13, 0x28, 
  
  0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 
  0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 
  0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 
  0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 
  0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66
};
unsigned int subjname_len = 153;
unsigned int subjname_ipdoff = 153 - 40;


#if 0
//XXX kill this code:
unsigned char nexus_tosign[] = {
  0x30, 0x82, 0x02, 0x73, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x01, 0x00,
  0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
  0x05, 0x05, 0x00, 0x30, 0x7b, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55,
  0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x11, 0x30, 0x0f, 0x06, 0x03,
  0x55, 0x04, 0x08, 0x13, 0x08, 0x4e, 0x65, 0x77, 0x20, 0x59, 0x6f, 0x72,
  0x6b, 0x31, 0x0f, 0x30, 0x0d, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x06,
  0x49, 0x74, 0x68, 0x61, 0x63, 0x61, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x03,
  0x55, 0x04, 0x0a, 0x13, 0x18, 0x43, 0x6f, 0x72, 0x6e, 0x65, 0x6c, 0x6c,
  0x20, 0x55, 0x6e, 0x69, 0x76, 0x65, 0x72, 0x73, 0x69, 0x74, 0x79, 0x20,
  0x4e, 0x65, 0x78, 0x75, 0x73, 0x31, 0x0d, 0x30, 0x0b, 0x06, 0x03, 0x55,
  0x04, 0x0b, 0x13, 0x04, 0x4e, 0x4f, 0x4e, 0x45, 0x31, 0x16, 0x30, 0x14,
  0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x0d, 0x54, 0x72, 0x75, 0x73, 0x74,
  0x65, 0x64, 0x20, 0x4e, 0x65, 0x78, 0x75, 0x73, 0x30, 0x1e, 0x17, 0x0d,
  0x30, 0x37, 0x30, 0x33, 0x30, 0x37, 0x32, 0x31, 0x33, 0x39, 0x30, 0x34,
  0x5a, 0x17, 0x0d, 0x31, 0x37, 0x30, 0x33, 0x30, 0x34, 0x32, 0x31, 0x33,
  0x39, 0x30, 0x34, 0x5a, 0x30, 0x81, 0x96, 0x31, 0x0b, 0x30, 0x09, 0x06,
  0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x11, 0x30, 0x0f,
  0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x08, 0x4e, 0x65, 0x77, 0x20, 0x59,
  0x6f, 0x72, 0x6b, 0x31, 0x0f, 0x30, 0x0d, 0x06, 0x03, 0x55, 0x04, 0x07,
  0x13, 0x06, 0x49, 0x74, 0x68, 0x61, 0x63, 0x61, 0x31, 0x21, 0x30, 0x1f,
  0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x18, 0x43, 0x6f, 0x72, 0x6e, 0x65,
  0x6c, 0x6c, 0x20, 0x55, 0x6e, 0x69, 0x76, 0x65, 0x72, 0x73, 0x69, 0x74,
  0x79, 0x20, 0x4e, 0x65, 0x78, 0x75, 0x73, 0x31, 0x0d, 0x30, 0x0b, 0x06,
  0x03, 0x55, 0x04, 0x0b, 0x13, 0x04, 0x4e, 0x4f, 0x4e, 0x45, 0x31, 0x31,
  0x30, 0x2f, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x28, 0x64, 0x65, 0x61,
  0x64, 0x62, 0x65, 0x65, 0x66, 0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65,
  0x66, 0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 0x64, 0x65, 0x61,
  0x64, 0x62, 0x65, 0x65, 0x66, 0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65,
  0x66, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
  0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f,
  0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00, 0xc6, 0x71,
  0x62, 0x7a, 0xd3, 0x88, 0xd3, 0x94, 0x42, 0x0e, 0x1f, 0x4f, 0x6f, 0x05,
  0x75, 0xef, 0xcd, 0xa8, 0xf9, 0x1d, 0x2c, 0x13, 0x34, 0x69, 0x09, 0xe0,
  0x0b, 0xb3, 0xba, 0xb3, 0x32, 0x54, 0xdb, 0xc1, 0x78, 0x9e, 0x22, 0x90,
  0x98, 0xa0, 0xf0, 0x39, 0x44, 0x6e, 0x07, 0xdc, 0x8b, 0x5f, 0xa8, 0x0d,
  0x8e, 0xa7, 0xe2, 0x35, 0xf6, 0x5e, 0x07, 0x8d, 0x3a, 0x7d, 0xa1, 0x0f,
  0x1a, 0x6b, 0xba, 0x5d, 0x53, 0xf3, 0x8e, 0x77, 0x93, 0xe2, 0x07, 0xd9,
  0x00, 0xa4, 0xc7, 0x4e, 0x04, 0x44, 0x88, 0xc4, 0xdf, 0xbd, 0x23, 0xbf,
  0x07, 0xa8, 0xbe, 0x12, 0x25, 0x38, 0xd8, 0x00, 0x7d, 0x19, 0x26, 0xfe,
  0x82, 0xc2, 0x76, 0x14, 0x62, 0x23, 0x2e, 0x5e, 0x4e, 0x1d, 0x00, 0xc3,
  0xae, 0xb2, 0x52, 0xa3, 0x4a, 0x3e, 0x22, 0x71, 0xe8, 0xdb, 0x8e, 0x71,
  0xeb, 0x14, 0xa2, 0x7a, 0x34, 0x7f, 0x94, 0x56, 0xb9, 0x04, 0xd6, 0x64,
  0x11, 0xf9, 0x0b, 0x49, 0x79, 0x60, 0xd0, 0x86, 0x7a, 0x5f, 0x84, 0x26,
  0x02, 0x2e, 0xd0, 0x51, 0x70, 0x21, 0x13, 0x10, 0x28, 0x71, 0x9b, 0x19,
  0xe7, 0x28, 0x71, 0x37, 0x9a, 0x0e, 0x54, 0xc6, 0x0f, 0x81, 0x5c, 0xdb,
  0xad, 0x11, 0xd1, 0xfe, 0xc0, 0xd1, 0x79, 0xdb, 0xf8, 0xe4, 0xd2, 0x76,
  0xa3, 0x78, 0x9c, 0x7e, 0xe1, 0x96, 0x3c, 0x1d, 0xcc, 0x9b, 0xe8, 0x8e,
  0x32, 0xab, 0x18, 0xdf, 0xc5, 0x81, 0xac, 0x93, 0x2c, 0x5a, 0xb1, 0x61,
  0xb2, 0x83, 0x04, 0x0d, 0x6d, 0x4f, 0x3c, 0xb4, 0x16, 0x40, 0xd2, 0x96,
  0x47, 0xe1, 0x4d, 0xbd, 0x1f, 0x2a, 0x42, 0x75, 0x1b, 0x0e, 0x9d, 0x3e,
  0x3b, 0xf8, 0xf9, 0x78, 0x61, 0xe3, 0x90, 0x21, 0x3a, 0x8d, 0xd3, 0xb3,
  0x4a, 0x36, 0xd9, 0xd1, 0xc5, 0xb0, 0xd8, 0x03, 0x61, 0xfe, 0xd8, 0xaa,
  0xdf, 0xbf, 0x02, 0x03, 0x01, 0x00, 0x01
};
unsigned int nexus_tosign_len = 631;
#if 0
unsigned char nexus_tosign[] = {
  0x30, 0x82, 0x02, 0xa9, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x01, 0x00,
  0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
  0x05, 0x05, 0x00, 0x30, 0x7b, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55,
  0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x11, 0x30, 0x0f, 0x06, 0x03,
  0x55, 0x04, 0x08, 0x13, 0x08, 0x4e, 0x65, 0x77, 0x20, 0x59, 0x6f, 0x72,
  0x6b, 0x31, 0x0f, 0x30, 0x0d, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x06,
  0x49, 0x74, 0x68, 0x61, 0x63, 0x61, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x03,
  0x55, 0x04, 0x0a, 0x13, 0x18, 0x43, 0x6f, 0x72, 0x6e, 0x65, 0x6c, 0x6c,
  0x20, 0x55, 0x6e, 0x69, 0x76, 0x65, 0x72, 0x73, 0x69, 0x74, 0x79, 0x20,
  0x4e, 0x65, 0x78, 0x75, 0x73, 0x31, 0x0d, 0x30, 0x0b, 0x06, 0x03, 0x55,
  0x04, 0x0b, 0x13, 0x04, 0x4e, 0x4f, 0x4e, 0x45, 0x31, 0x16, 0x30, 0x14,
  0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x0d, 0x54, 0x72, 0x75, 0x73, 0x74,
  0x65, 0x64, 0x20, 0x4e, 0x65, 0x78, 0x75, 0x73, 0x30, 0x1e, 0x17, 0x0d,
  0x30, 0x37, 0x30, 0x33, 0x30, 0x35, 0x31, 0x38, 0x30, 0x33, 0x33, 0x32,
  0x5a, 0x17, 0x0d, 0x31, 0x37, 0x30, 0x33, 0x30, 0x32, 0x31, 0x38, 0x30,
  0x33, 0x33, 0x32, 0x5a, 0x30, 0x00, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d,
  0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05,
  0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82,
  0x01, 0x01, 0x00, 0xc6, 0x71, 0x62, 0x7a, 0xd3, 0x88, 0xd3, 0x94, 0x42,
  0x0e, 0x1f, 0x4f, 0x6f, 0x05, 0x75, 0xef, 0xcd, 0xa8, 0xf9, 0x1d, 0x2c,
  0x13, 0x34, 0x69, 0x09, 0xe0, 0x0b, 0xb3, 0xba, 0xb3, 0x32, 0x54, 0xdb,
  0xc1, 0x78, 0x9e, 0x22, 0x90, 0x98, 0xa0, 0xf0, 0x39, 0x44, 0x6e, 0x07,
  0xdc, 0x8b, 0x5f, 0xa8, 0x0d, 0x8e, 0xa7, 0xe2, 0x35, 0xf6, 0x5e, 0x07,
  0x8d, 0x3a, 0x7d, 0xa1, 0x0f, 0x1a, 0x6b, 0xba, 0x5d, 0x53, 0xf3, 0x8e,
  0x77, 0x93, 0xe2, 0x07, 0xd9, 0x00, 0xa4, 0xc7, 0x4e, 0x04, 0x44, 0x88,
  0xc4, 0xdf, 0xbd, 0x23, 0xbf, 0x07, 0xa8, 0xbe, 0x12, 0x25, 0x38, 0xd8,
  0x00, 0x7d, 0x19, 0x26, 0xfe, 0x82, 0xc2, 0x76, 0x14, 0x62, 0x23, 0x2e,
  0x5e, 0x4e, 0x1d, 0x00, 0xc3, 0xae, 0xb2, 0x52, 0xa3, 0x4a, 0x3e, 0x22,
  0x71, 0xe8, 0xdb, 0x8e, 0x71, 0xeb, 0x14, 0xa2, 0x7a, 0x34, 0x7f, 0x94,
  0x56, 0xb9, 0x04, 0xd6, 0x64, 0x11, 0xf9, 0x0b, 0x49, 0x79, 0x60, 0xd0,
  0x86, 0x7a, 0x5f, 0x84, 0x26, 0x02, 0x2e, 0xd0, 0x51, 0x70, 0x21, 0x13,
  0x10, 0x28, 0x71, 0x9b, 0x19, 0xe7, 0x28, 0x71, 0x37, 0x9a, 0x0e, 0x54,
  0xc6, 0x0f, 0x81, 0x5c, 0xdb, 0xad, 0x11, 0xd1, 0xfe, 0xc0, 0xd1, 0x79,
  0xdb, 0xf8, 0xe4, 0xd2, 0x76, 0xa3, 0x78, 0x9c, 0x7e, 0xe1, 0x96, 0x3c,
  0x1d, 0xcc, 0x9b, 0xe8, 0x8e, 0x32, 0xab, 0x18, 0xdf, 0xc5, 0x81, 0xac,
  0x93, 0x2c, 0x5a, 0xb1, 0x61, 0xb2, 0x83, 0x04, 0x0d, 0x6d, 0x4f, 0x3c,
  0xb4, 0x16, 0x40, 0xd2, 0x96, 0x47, 0xe1, 0x4d, 0xbd, 0x1f, 0x2a, 0x42,
  0x75, 0x1b, 0x0e, 0x9d, 0x3e, 0x3b, 0xf8, 0xf9, 0x78, 0x61, 0xe3, 0x90,
  0x21, 0x3a, 0x8d, 0xd3, 0xb3, 0x4a, 0x36, 0xd9, 0xd1, 0xc5, 0xb0, 0xd8,
  0x03, 0x61, 0xfe, 0xd8, 0xaa, 0xdf, 0xbf, 0x02, 0x03, 0x01, 0x00, 0x01,
  0xa3, 0x81, 0xca, 0x30, 0x81, 0xc7, 0x30, 0x09, 0x06, 0x03, 0x55, 0x1d,
  0x23, 0x04, 0x02, 0x30, 0x00, 0x30, 0x81, 0x86, 0x06, 0x03, 0x55, 0x1d,
  0x20, 0x01, 0x01, 0xff, 0x04, 0x7c, 0x30, 0x7a, 0x30, 0x78, 0x06, 0x03,
  0x2a, 0x03, 0x04, 0x30, 0x71, 0x30, 0x37, 0x06, 0x08, 0x2b, 0x06, 0x01,
  0x05, 0x05, 0x07, 0x02, 0x01, 0x16, 0x2b, 0x68, 0x74, 0x74, 0x70, 0x3a,
  0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x65, 0x6e, 0x64, 0x6f, 0x72, 0x73,
  0x65, 0x6d, 0x65, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x69, 0x74, 0x79, 0x2e,
  0x63, 0x6f, 0x6d, 0x2f, 0x70, 0x6f, 0x6c, 0x69, 0x63, 0x79, 0x2e, 0x74,
  0x78, 0x74, 0x30, 0x36, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07,
  0x02, 0x02, 0x30, 0x2a, 0x1a, 0x28, 0x64, 0x65, 0x61, 0x64, 0x62, 0x65,
  0x65, 0x66, 0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 0x64, 0x65,
  0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 0x64, 0x65, 0x61, 0x64, 0x62, 0x65,
  0x65, 0x66, 0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 0x30, 0x23,
  0x06, 0x03, 0x55, 0x1d, 0x11, 0x01, 0x01, 0xff, 0x04, 0x19, 0x30, 0x17,
  0x81, 0x15, 0x64, 0x6a, 0x77, 0x69, 0x6c, 0x6c, 0x40, 0x63, 0x73, 0x2e,
  0x63, 0x6f, 0x72, 0x6e, 0x65, 0x6c, 0x6c, 0x2e, 0x65, 0x64, 0x75, 0x30,
  0x0c, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x02, 0x30,
  0x00
};
unsigned int nexus_tosign_len = 685;
#endif
//int tosign_pubkeyoff = 0xdb;
int tosign_pubkeyoff = 0x172;
//int tosign_hashoff = 0x252;
int tosign_hashoff = 0x129;

//int tosign_time1off = 0x9c;
//int tosign_time2off = 0xab;
//int tosign_timelen = 12;

/* a valid X509 is    | preamble | tosign | presig | sig over tosign | */

//unsigned char tosign_preamble[] =  {0x30, 0x82, 0x03, 0xc1};
unsigned char tosign_preamble[] =  {0x30, 0x82, 0x03, 0x8b};
unsigned char tosign_presig[] = {
  0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 
  0x05, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00
};

int tosign_preamble_len = 4;
int tosign_presig_len = 20;

#define NEWCERT_TOTAL_LEN  (tosign_preamble_len + nexus_tosign_len + tosign_presig_len + TCPA_SIG_SIZE)
#define NEWCERT_HASH_OFF   (tosign_hashoff + tosign_preamble_len)
#define NEWCERT_PUBKEY_OFF (tosign_pubkeyoff + tosign_preamble_len)

#endif
#endif
