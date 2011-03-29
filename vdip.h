#ifndef _VDIP_FUNC_H_
#define _VDIP_FUNC_H_

#include "pic24_all.h"

/***********************************************************
 * Pin Mappings
 **********************************************************/

// Reset pin on the VDIP
#define RESET _LATF1		
#define CONFIG_RESET() CONFIG_RF1_AS_DIG_OUTPUT()


/***********************************************************
 * Common Characters
 **********************************************************/

// Carriage Return
#define CR 0xd

// Carriage Return
#define LF 0xa

// DIR command
#define DIR 0x1

// RD: Read a file
#define RD 0x4

// WRF: Write File command
#define WRF 0x8

// CLF: Close File command
#define CLF 0xA

// OPR: Open file for reading
#define OPR 0xE

// OPW: Open file for writing
#define OPW 0x9

// DLF: Delete file
#define DLF 0x7

// IPA: Ascii
#define IPA 0x90

// IPA: Binary
#define IPH 0x91

// Space
#define SPACE 0x20

// End of Command
#define EOC '>'

// SCS: Short Command Set
#define SCS "SCS"

// The largest filename is 12 characters
#define MAX_FILENAME_LEN 12+1


/***********************************************************
 * Function Definitions
 **********************************************************/
void   VDIP_Init(void);
void   VDIP_Reset(void);
void   VDIP_Sync_E(void);
uint8  VDIP_Sync(void);
uint8  VDIP_SCS(void);

void   VDIP_WriteFile (const uint8 *,
                       const uint8 *);
void   VDIP_WriteFileN(const uint8 *,
                       const uint8 *,
                       uint32);

uint8* VDIP_ReadFile(const uint8 *);
void   VDIP_DeleteFile(const uint8 *);

uint8  VDIP_FileExists(const uint8 *);
uint32 VDIP_FileSize(const uint8 *);
uint32 VDIP_DirItemCount(void);

uint8** VDIP_ListDir(void);
void    VDIP_CleanupDirList(uint8 **);

void VDIP_PrintListDir(void);

#endif // VDIP_H
