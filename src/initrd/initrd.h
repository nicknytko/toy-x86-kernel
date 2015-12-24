#ifndef INITRD_H
#define INITRD_H

/** Gets the number of files in the initial ramdisk
 * @return number of files
 */

uint32 initrd_getNumFiles( );

/** Loads the initrd from the first multiboot module
 * @return 1 if successfully loaded, 0 if the magic value is incorrect
 */

bool initrd_load( );

/** Gets the name of a file in the initial ramdisk
 * @param nFileNumber File ID
 * @return Pointer to null-terminated string
 */
char* initrd_getFileName( uint32 nFileNumber );

/** Gets the size of a file in the initial ramdisk
 * @param nFileNumber File ID
 * @return Size in bytes
 */
uint32 initrd_getFileSize( uint32 nFileNumber );

/** Gets the data of a file in the initial ramdisk
 * @param nFileNumber File ID
 * @return Pointer to file data
 */
char* initrd_getData( uint32 nFileNumber );

#endif
