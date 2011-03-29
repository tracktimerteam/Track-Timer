/***********************************************************
 * Includes
 **********************************************************/
#include "pic24_all.h"
#include "spi.h"
#include "vdip.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/***********************************************************
 * Macro Definitions
 **********************************************************/
#define VDIP_DEBUG 1
// Is this a VDIP_DEBUG build?
#ifndef VDIP_DEBUG
#define VDIP_DEBUG 1
#endif // VDIP_DEBUG

// Print output if this is a VDIP_DEBUG build
#if VDIP_DEBUG
#define VDIP_DEBUG_OUT(msg) \
    (outString("`"msg"`\n"))
#else
#define VDIP_DEBUG_OUT(msg)
#endif


#define REMOVE_LEADING_NEWLINES(c) \
    while((c) == CR)               \
    {                              \
        c = SPI_ReadWait();        \
    }
#define END_COMMAND(c) \
    while((c) != EOC)               \
    {                              \
        c = SPI_ReadWait();        \
    }

/***********************************************************
 * Function Definitions
 **********************************************************/

//**********************************************************
/**
 * @brief Initialize SPI and then Reset the VDIP
 */
//**********************************************************
void VDIP_Init(void)
{
    VDIP_DEBUG_OUT("VDIP_Init: Started.");
    CONFIG_RESET();

    SPI_Init();

    VDIP_Reset();

    // Syncs VDIP with PIC
    VDIP_Sync();

    // Put vdip in short command mode
    VDIP_SCS();

    VDIP_DEBUG_OUT("VDIP_Init: Finished.");
}

//**********************************************************
/**
 * @brief Status of VDIP1 uint8acter from SPI bus
 * @return uint8 The received uint8acter
 */
/**
 * @brief Sync the VDIP with the PIC. 'E' is sent to the
 *        VDIP, and then the PIC just reads until it gets
 *        the E back.
 * @return uint8 1 if everything syncs correctly
 * @todo Add some more error checking to verify that the PIC
 *       has failed to sync with the VDIP.
 */
//**********************************************************
uint8 VDIP_Sync(void)
{
	SPI_ReadWait();

	VDIP_DEBUG_OUT("VDIP_Sync: Started.");

	// Initialize the sync by sending and E
	SPI_WriteStr("E");
	DELAY_MS(10);

    uint8 c = SPI_ReadWait();

    REMOVE_LEADING_NEWLINES(c);

    // Wait for VDIP to send an 'E'

	while (c != 'E')
    {
		
          c = SPI_ReadWait();
        //putchar(c);
     }//end while
    VDIP_DEBUG_OUT("VDIP_Sync: Finished.");
    return 1;
}


//**********************************************************
/**
 * @brief Put VDIP in Short Command Set mode.
 * @return uint8 Are we in SCS mode?
 */
//**********************************************************
uint8 VDIP_SCS(void)
{
    VDIP_DEBUG_OUT("VDIP_SCS: Started. Setting"
	          " Short Command Set");

	//VDIP_Sync();

	SPI_WriteStr(SCS);
	uint8 c = SPI_ReadWait();

	REMOVE_LEADING_NEWLINES(c);

	if(c == EOC)
	{
	    VDIP_DEBUG_OUT("VDIP_SCS: Finished."
	              " In Short Command Set");
	    return 1;
	}

    VDIP_DEBUG_OUT("VDIP_SCS: Finished."
              " NOT In Short Command Set");
	return 0;
}


//**********************************************************
/**
 * @brief Reset the VDIP
 */
//**********************************************************
void VDIP_Reset(void)
{
    VDIP_DEBUG_OUT("VDIP_Reset: Started.");

    RESET = 0;
    DELAY_MS(1000);
    RESET = 1;
    DELAY_MS(1000);

    VDIP_DEBUG_OUT("VDIP_Reset: Finished.");
}


//**********************************************************
/**
 * @brief List the files and folders in the current
 *        directory
 * @return A character array of file and directory names.
 * @see VDIP_CleanupDirList
 */
//**********************************************************
uint8** VDIP_ListDir(void)
{
    VDIP_DEBUG_OUT("VDIP_ListDir: Started.");

	//VDIP_Sync();

    // Get the number of items in the directory
    uint32 u32_items = VDIP_DirItemCount();

    // Allocate memory for the array of pointers
    uint8 **data = (uint8**)malloc(sizeof(uint8*) * (u32_items + 1));

    // Null terminate the array so it will be easy to traverse
    data[u32_items] = '\0';
    uint32 u32_index = 0;

    // Allocate memory for the filenames. This could have
    // been done in one call, but contiguous memory space
    // may be sparse.
    for(u32_index = 0; u32_index < u32_items; u32_index++)
    {
        data[u32_index] = (uint8*)malloc(sizeof(uint8) * MAX_FILENAME_LEN);
    }

    // Request a directory listing
    SPI_Write(DIR);
    SPI_Write(CR);

    uint8 c = SPI_ReadWait();

    REMOVE_LEADING_NEWLINES(c);

    uint32 u32_row = 0,
           u32_col = 0;

    // Get the file names from the VDIP
    while(c != EOC)
    {
        // File names end with a line feed uint8acter
        if(c == CR)
        {
            data[u32_row][u32_col] = '\0';
            ++u32_row;
            u32_col = 0;
        }
        else
        {
            data[u32_row][u32_col++] = c;
        }
        c = SPI_ReadWait();
    }

    VDIP_DEBUG_OUT("VDIP_ListDir: Finished.");
    return data;
}


//**********************************************************
/**
 * @brief Clean up a multi-dimensional array returned
 *        from VDIP_ListDir
 * @see VDIP_ListDir
 */
//**********************************************************
void VDIP_CleanupDirList(uint8 **data)
{
    uint32 u32_index = 0;
    while(data[u32_index] != '\0')
    {
        free(data[u32_index++]);
    }
    free(data);
}


//**********************************************************
/**
 * @brief Return the number of files and folders in the
 *        current directory
 * @return The number of files and folders in the current
 *         directory.
 */
//**********************************************************
uint32 VDIP_DirItemCount(void)
{
    VDIP_DEBUG_OUT("VDIP_DirItemCount: Started.");

	VDIP_Sync();

    // Request a directory listing
    SPI_Write(DIR);
    SPI_Write(CR);

    uint8 c = SPI_ReadWait();

    REMOVE_LEADING_NEWLINES(c);

    // This will contain the number of files and
    // folders in the current directory.
    uint32 u32_items = 0;

    // Get the file names from the VDIP
    while(c != EOC)
    {
        // All file names are delimited by carriage
        // returns, so just count them.
        if(c == CR)
        {
            ++u32_items;
        }
        c = SPI_ReadWait();
    }

    VDIP_DEBUG_OUT("VDIP_DirItemCount: Finished.");
    return u32_items;
}


//**********************************************************
/**
 * @brief Find the size of the given file
 * @param[in] name The name of the file
 * @return uint8 The size of the file in bytes
 */
//**********************************************************
uint32 VDIP_FileSize(const uint8 *name)
{
    VDIP_DEBUG_OUT("VDIP_FileSize: Started.");

	//VDIP_Sync();

    // Make a DIR request
    SPI_Write(DIR);
    SPI_Write(SPACE);
    SPI_WriteStr(name);

    // The returned data will have this format:
    // FILENAME.EXT XXXX, where XXXX are four
    // bytes telling the size of the file

    // Parse the string
    uint32 u32_size = 0;
    uint8 ch_prior_space = 0,
         ch_shift = 0,
         c = SPI_ReadWait();

    while(c != EOC)
    {
        if(c == SPACE)
        {
            ch_prior_space = 1;
        }
        else
        {
            if(ch_prior_space)
            {
                // We have passed the space, start
                // to shift in the four bytes.
                u32_size |= (c << ch_shift++);
                ch_shift *= 8;
            }
        }

        c = SPI_ReadWait();
    }

    VDIP_DEBUG_OUT("VDIP_FileSize: Finished.");
    return u32_size;
}


//**********************************************************
/**
 * @brief Determine whether or not a disk exists
 * @return A boolean indication the existence of the disk.
 */
//**********************************************************
uint8 VDIP_DiskExists(void)
{
    VDIP_DEBUG_OUT("VDIP_DiskExists: Started.");

    // Make a DIR request
    SPI_Write(DIR);
    SPI_Write(CR);

    // The returned data will have this format:
    // \r\rND, where ND means No Disk.

    // Parse the string
    uint8 c = SPI_ReadWait();

    REMOVE_LEADING_NEWLINES(c);
    if(c == 'N')
    {
        c = SPI_ReadWait();
        if(c == 'D')
        {
            return 0x0;
        }
    }

    END_COMMAND(c);
    VDIP_DEBUG_OUT("VDIP_DiskExists: Finished.");
    return 0x1;
}


//**********************************************************
/**
 * @brief Determine whether or not a file exists
 * @param[in] name The name of the file
 * @return A boolean indication the existence of the file.
 */
//**********************************************************
uint8 VDIP_FileExists(const uint8 *name)
{
    VDIP_DEBUG_OUT("VDIP_FileExists: Started.");

    // Make a DIR request
    SPI_Write(DIR);
    SPI_Write(SPACE);
    SPI_WriteStr(name);

    // The returned data will have this format:
    // \r\rCF, where CF means Command Failed.

    // Parse the string
    uint8 c = SPI_ReadWait();

    REMOVE_LEADING_NEWLINES(c);
    if(c == 'C')
    {
        c = SPI_ReadWait();
        if(c == 'F')
        {
            return 0x0;
        }
    }

    END_COMMAND(c);
    VDIP_DEBUG_OUT("VDIP_FileExists: Finished.");
    return 0x1;
}


//**********************************************************
/**
 * @brief Read a file into a string
 * @param[in] name The name of the file
 * @return uint8* A string containing the contents
 *               of the file
 */
//**********************************************************
uint8* VDIP_ReadFile(const uint8 *name)
{
    VDIP_DEBUG_OUT("VDIP_ReadFile: Started.");

	//VDIP_Sync();

    uint32 u32_bytes = VDIP_FileSize(name) + 1,
           u32_index = 0;
    uint8 *data = (uint8*)malloc(u32_bytes);

    //printf("ReadFile->FileSize = `%u`\n", (unsigned)u32_bytes);

    SPI_Write(RD);
    SPI_Write(SPACE);
    SPI_WriteStr(name);

    uint8 c = SPI_ReadWait();

    REMOVE_LEADING_NEWLINES(c);

    while(c != EOC)
    {
        data[u32_index++] = c;
        c = SPI_ReadWait();
    }
    data[u32_index] = '\0';

    VDIP_DEBUG_OUT("VDIP_ReadFile: Finished.");
    return data;
}


//**********************************************************
/**
 * @brief Open a file for writing
 * @param[in] name The name of the file
 * @param[in] data The data to write
 */
//**********************************************************
void VDIP_WriteFile(const uint8 *name, const uint8 *data)
{
    VDIP_DEBUG_OUT("VDIP_WriteFile: Started.");

    uint32 u32_size = strlen(data);
    VDIP_WriteFileN(name, data, u32_size);

    VDIP_DEBUG_OUT("VDIP_WriteFile: Finished.");
}


//**********************************************************
/**
 * @brief Open a file for writing
 * @param[in] name The name of the file
 * @param[in] data The data to write
 * @param[in] size The number of bytes to write
 */
//**********************************************************
void VDIP_WriteFileN(const uint8 *name, const uint8 *data, uint32 u32_size)
{
    VDIP_DEBUG_OUT("VDIP_WriteFileN: Started.");

    VDIP_Sync();

  	VDIP_DEBUG_OUT("Put in Binary mode");
    //SPI_Write(IPA);
    SPI_Write(IPH);
    SPI_Write(CR);

    VDIP_DEBUG_OUT("Open the file for writing");
    SPI_Write(OPW);
    SPI_Write(SPACE);
    SPI_WriteStr(name);
    VDIP_Sync();

    // Tell the VDIP how much data to expect
    SPI_Write(WRF);
    SPI_Write(SPACE);

	// Shift the bytes in, MSB first
    int8 i8_byte  = 0;
    int32 u32_index;
    for(u32_index = 24; u32_index >= 0; u32_index -= 8)
    {
        i8_byte = (int8)(u32_size >> u32_index);
        SPI_Write(i8_byte);
    }
    SPI_Write(CR);

    VDIP_DEBUG_OUT("Write the actual message.");
    SPI_WriteStrN(data, u32_size);
    DELAY_MS(100);

    VDIP_DEBUG_OUT("Close the file");
    SPI_Write(CLF);
    SPI_Write(SPACE);
    SPI_WriteStr(name);
    DELAY_MS(100);
    VDIP_Sync();

    VDIP_DEBUG_OUT("VDIP_WriteFileN: Finished.");
}

//**********************************************************
/**
 * @brief Delete a file
 * @param[in] name The name of the file
 */
//**********************************************************
void VDIP_DeleteFile(const uint8 *name)
{
    VDIP_DEBUG_OUT("VDIP_DeleteFile: Started.");

    if(VDIP_FileExists(name))
    {
        SPI_Write(DLF);
        SPI_Write(SPACE);
        SPI_WriteStr(name);
    }

    VDIP_DEBUG_OUT("VDIP_DeleteFile: Finished.");
}


//**********************************************************
/**
 * @brief Print the files in the current directory
 */
//**********************************************************
void VDIP_PrintListDir(void)
{
    VDIP_DEBUG_OUT("VDIP_PrintListDir: Started.");

    uint8 **data = VDIP_ListDir();
    uint32 u32_index = 0;
    while(data[u32_index])
    {
        outUint32(u32_index);
        outString(": ");
        outString(data[u32_index]);
        outChar('\n');
        ++u32_index;
    }
    VDIP_CleanupDirList(data);

    VDIP_DEBUG_OUT("VDIP_PrintListDir: Finished.");
}
