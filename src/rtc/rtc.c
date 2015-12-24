#include <base.h>
#include "rtc.h"

#include <interrupt/interrupt.h>

static uint8 nRTCSecond, nRTCMinute, nRTCHour, nRTCDay, nRTCMonth;
static uint32 nRTCYear;

static uint8 rtc_readRegister( uint8 nRegister )
{
    outb( RTC_INDEX, nRegister );
    return inb( RTC_DATA );
}

IRQ_HANDLER_NOARGS( rtc_irq )
{
    // read from register c to determine what kind of interrupt
    // this has to be done or else the rtc won't send any more irq's
    
    outb( RTC_INDEX, RTC_REGISTER_C );
    uint8 nInt = inb( RTC_DATA );

    // get data from rtc
    
    nRTCSecond = rtc_readRegister( RTC_REGISTER_SECOND );
    nRTCMinute = rtc_readRegister( RTC_REGISTER_MINUTE );
    nRTCHour = rtc_readRegister( RTC_REGISTER_HOUR );
    nRTCDay = rtc_readRegister( RTC_REGISTER_DAY );
    nRTCMonth = rtc_readRegister( RTC_REGISTER_MONTH );
    nRTCYear = rtc_readRegister( RTC_REGISTER_YEAR );
}

void rtc_init( )
{
    // disable interrupts and nmi's
    
    int_cli( );

    // get the current value in rtc's "b" register

    uint8 nData = rtc_readRegister( RTC_REGISTER_B );
    
    // a read will reset the register to d, so set it back to b
    
    outb( RTC_INDEX, RTC_REGISTER_B );

    // enable RTC interrupts by setting the 6'th bit
    
    outb( RTC_DATA, nData | 0x40 );
    irq_loadHandler( (uint32)rtc_irq, 8 );

    // re-enable interrupts and nmi's
    
    int_sti( );
}
