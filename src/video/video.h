#ifndef VIDEO_H
#define VIDEO_H

#define VGA_BASE	0x3D4

/** Clears the screen
 */
void screen_clear( );

/** Sets the cursor to a certain position and updates the hardware cursor
 */
void screen_setCursor( uint32 x, uint32 y );

/** Gets the cursor's X position
 */
uint16 screen_getCursorX( );

/** Gets the cursor's Y position
 */
uint16 screen_getCursorY( );

/** Scrolls the screen up by one line
 */
void screen_scroll( );

/** Skips to the next line
 */
void screen_newline( );

/** @brief Inserts a tab indent.
 * "Rounds" up the cursor's X to the nearest divisible-by-4 position
 */
void screen_tab( );

/** Prints a null terminated string
 */
void screen_printString( char* szStr );

/** Prints an unsigned hexadecimal number
 */
void screen_printHex( uint32 nHex );

/** Prints an unsigned decimal number
 */
void screen_printDec( uint32 nDec );

#endif
