#include <base.h>
#include "video.h"

#define VGA_WIDTH 	80
#define VGA_HEIGHT 	25

#define VGA_OFFSET	0xB8000
#define VGA_END		VGA_OFFSET + ((VGA_WIDTH * VGA_HEIGHT) * 2)

#define vgaoffset( x, y ) (uint8*)(VGA_OFFSET + ((y * VGA_WIDTH) + x) * 2);

uint16 nVGACursorX, nVGACursorY;

void screen_clear( )
{
    uint8* pData = (uint8*) VGA_OFFSET;
    
    while ((uint32)pData < VGA_END)
    {
	pData[0] = 0;
	pData[1] = 0xF;
	pData += 2;
    }

    screen_setCursor( 0, 0 );
}

void screen_setCursor( uint32 nCursorX, uint32 nCursorY )
{
    uint16 nCell = (nCursorY * VGA_WIDTH) + nCursorX;

    nVGACursorX = nCursorX;
    nVGACursorY = nCursorY;

    // if the cursor x is larger than the screen width, wrap around to the next line
    
    if (nVGACursorX >= VGA_WIDTH)
    {
	uint16 nShiftAmt = nVGACursorX / VGA_WIDTH;
	nVGACursorX -= nShiftAmt * VGA_WIDTH;
	nVGACursorY += nShiftAmt;
    }
    
    // send high byte of our cell
    
    outb( VGA_BASE, 0xE );
    outb( VGA_BASE + 1, word_hbyte( nCell ) );

    // send low byte of our cell
    
    outb( VGA_BASE, 0xF );
    outb( VGA_BASE + 1, word_lbyte( nCell ) );
}

uint16 screen_getCursorX( )
{
    return nVGACursorX;
}

uint16 screen_getCursorY( )
{
    return nVGACursorY;
}

void screen_scroll( )
{
    uint8* pData = (uint8*) VGA_OFFSET;
    uint32 nLastLine = VGA_END - VGA_WIDTH;

    // copy data until last line, where there is no data to copy from
    
    while ((uint32)pData < nLastLine)
    {
	pData[0] = pData[VGA_WIDTH*2];
	pData[1] = pData[VGA_WIDTH*2 + 1];
	pData += 2;
    }

    // clear the last line

    while ((uint32)pData < VGA_END)
    {
	pData[0] = 0;
	pData[1] = 0xF;
	pData += 2;
    }

    screen_setCursor( nVGACursorX, nVGACursorY - 1 );
}

void screen_newline( )
{
    screen_setCursor( 0, nVGACursorY + 1 );
}

void screen_tab( )
{
    screen_setCursor( (nVGACursorX & 0xFFFFFFFC) + 4, nVGACursorY );
}

void screen_printHex( uint32 nHex )
{
    uint8* pData = vgaoffset( nVGACursorX, nVGACursorY );
    uint8 i;

    // prefix our number with '0x'
    
    pData[0] = '0';
    pData[1] = 0xF;
    pData[2] = 'x';
    pData[3] = 0xF;

    pData += 4;

    // a hexadecimal number is a max of 8 digits, so print 8 digits
    
    for (i=0;i < 8;i++)
    {
	uint8 nDigit = (nHex >> ((7-i) * 4)) & 0xF;
	
	if (nDigit < 10)
	{
	    pData[0] = '0' + nDigit;
	    pData[1] = 0xF;
	    pData += 2;
	}
	else
	{
	    pData[0] = 'A' + (nDigit - 10);
	    pData[1] = 0xF;
	    pData += 2;
	}
    }

    screen_setCursor( nVGACursorX + 11, nVGACursorY );
}

void screen_printChar( uint8 c )
{
    uint8* pData = vgaoffset( nVGACursorX, nVGACursorY );

    pData[0] = c;
    pData[1] = 0xF;

    screen_setCursor( nVGACursorX + 1, nVGACursorY );
}

void screen_printDec( uint32 nDec )
{
    uint8* pData = vgaoffset( nVGACursorX, nVGACursorY );
    uint8 nDigits = 0;

    uint32 nTemp = nDec;
    
    while (nTemp != 0)
    {
	nDigits++;
	nTemp /= 10;
    }

    if (nDigits == 0)
	nDigits = 1;
    
    for (uint32 i = nDigits * 2;i > 0;i -= 2)
    {
	pData[i-2] = '0' + (nDec % 10);
	pData[i-1] = 0xF;

	nDec /= 10;
    }

    screen_setCursor( nVGACursorX + nDigits, nVGACursorY );
}

void screen_printString( char* szStr )
{
    if (szStr == 0)
	return;

    uint8* pData = vgaoffset( nVGACursorX, nVGACursorY );

    while (*szStr != 0)
    {
	switch (*szStr)
	{
	case '\n':
	{
	    uint32 nOffset = ((uint32)pData - VGA_OFFSET) / 2;
	    nOffset = ((nOffset / VGA_WIDTH) + 1) * VGA_WIDTH;

	    pData = (uint8 *)(VGA_OFFSET + nOffset*2);
	    break;
	}
	case '\t':
	{
	    uint32 nOffset = ((uint32)pData - VGA_OFFSET) / 2;
	    nOffset = (nOffset & 0xFFFFFFFC) + 4;
	    
	    pData = (uint8 *)(VGA_OFFSET + nOffset*2);
	    break;
	}
	default:
	{
	    *pData = *szStr;
	    pData++;
	    *pData = 0xF;
	    pData++;
	    break;
	}
	}
	
	szStr++;
    }

    uint16 nCursorX, nCursorY;

    nCursorY = (((uint32)pData - VGA_OFFSET) / 2) / VGA_WIDTH;
    nCursorX = (((uint32)pData - VGA_OFFSET) / 2) - nCursorY * VGA_WIDTH;

    screen_setCursor( nCursorX, nCursorY );
}
