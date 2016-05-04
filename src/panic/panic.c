#include <base.h>

#include "panic.h"
#include <video/video.h>

#define KP_MESSAGE_1 "FLAGRANT SYSTEM ERROR"
#define KP_MESSAGE_2 "Computer over."
#define KP_MESSAGE_3 "Panic = Very Yes."

uint32 strlen( const char* szString )
{
    const char* szStart = szString;

    while ( *szString != 0 )
    {
        szString++;
    }

    return szString - szStart;
}

void kpanic( const char* szError )
{
    uint32 nHalfWidth = screen_getWidth( )/2;
    uint32 nHalfHeight = screen_getHeight( )/2 - 3;
    
    screen_clearColor( VGA_COLOR_LBLUE );
    
    screen_setCursor( nHalfWidth - sizeof( KP_MESSAGE_1 )/2, nHalfHeight );
    screen_printString( KP_MESSAGE_1 );
    
    screen_setCursor( nHalfWidth - sizeof( KP_MESSAGE_2 )/2, nHalfHeight + 2 );
    screen_printString( KP_MESSAGE_2 );
    
    screen_setCursor( nHalfWidth - sizeof( KP_MESSAGE_3 )/2, nHalfHeight + 3 );
    screen_printString( KP_MESSAGE_3 );

    screen_setCursor( nHalfWidth - strlen( szError )/2, nHalfHeight + 5 );
    screen_printString( szError );
}
