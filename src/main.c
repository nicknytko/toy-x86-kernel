#include "video.h"

int main( void *pMBHeader )
{
    screen_clear();
    screen_setCursor( 0, 0 );
    return 0xDEADBABA;
}
