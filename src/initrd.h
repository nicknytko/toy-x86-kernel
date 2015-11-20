#ifndef INITRD_H
#define INITRD_H

/** Gets the number of files in the initial ramdisk
 * @return number of files
 */

unsigned int initrd_getNumFiles( );

/** Loads the initrd from the first multiboot module
 * @return 1 if successfully loaded, 0 if the magic value is incorrect
 */

int initrd_load( );

#endif
