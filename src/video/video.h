#ifndef VIDEO_H
#define VIDEO_H

/** @file video.h
 * @brief Text-mode video driver.
 */

#define VGA_BASE        	0x3D4

#define VGA_COLOR_BLACK		0x0
#define VGA_COLOR_BLUE		0x1
#define VGA_COLOR_GREEN		0x2
#define VGA_COLOR_CYAN		0x3
#define VGA_COLOR_RED		0x4
#define VGA_COLOR_MAGENTA	0x5
#define VGA_COLOR_BROWN		0x6
#define VGA_COLOR_LGRAY		0x7
#define VGA_COLOR_DGRAY		0x8
#define VGA_COLOR_LBLUE		0x9
#define VGA_COLOR_LGREEN	0xA
#define VGA_COLOR_LCYAN		0xB
#define VGA_COLOR_LRED		0xC
#define VGA_COLOR_LMAGENTA	0xD
#define VGA_COLOR_YELLOW	0xE
#define VGA_COLOR_WHITE		0xF

/** Clears the screen
 */
void screen_clear( );

/** Clears the screen to a certain background color
 */
void screen_clearColor( uint8 nBackground );

/** Sets the cursor to a certain position and updates the hardware cursor
 */
void screen_setCursor( uint32 x, uint32 y );

/** Set the text color
 */
void screen_setCursorColor( uint8 nColor );

/** Gets the cursor's X position
 */
uint16 screen_getCursorX( );

/** Gets the cursor's Y position
 */
uint16 screen_getCursorY( );

/** Get screen width
 */
uint16 screen_getWidth( );

/** Get screen height
 */
uint16 screen_getHeight( );

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
void screen_printString( const char* szStr );

/** Prints a character
 */
void screen_printChar( uint8 c );

/** Prints an unsigned hexadecimal number
 */
void screen_printHex( uint32 nHex );

/** Prints an unsigned decimal number
 */
void screen_printDec( uint32 nDec );

#endif
