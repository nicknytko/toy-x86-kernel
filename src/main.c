#include "video.h"

int main( void *pMBHeader )
{
    screen_clear();
    screen_setCursor( 0, 0 );
    screen_printString( "Hello, World!" );

    return 0xDEADBABA;
}
