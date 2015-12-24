#include <base.h>
#include "rtc.h"

#include <interrupt/interrupt.h>
#include <video/video.h>

static uint8 nRTCSecond, nRTCMinute, nRTCHour, nRTCDay, nRTCDayOfWeek, nRTCMonth;
static uint32 nRTCYear;

static bool bIntFired;

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
    nRTCDayOfWeek = rtc_readRegister( RTC_REGISTER_DAYOFWEEK );
    nRTCMonth = rtc_readRegister( RTC_REGISTER_MONTH );
    nRTCYear = rtc_readRegister( RTC_REGISTER_CENTURY ) * 100 + rtc_readRegister( RTC_REGISTER_YEAR );

    bIntFired = true;
}

// getters

uint8 rtc_getSecond( )
{
    return nRTCSecond;
}

uint8 rtc_getMinute( )
{
    return nRTCMinute;
}

uint8 rtc_getHour( )
{
    return nRTCHour;
}

uint8 rtc_getDay( )
{
    return nRTCDay;
}

uint8 rtc_getDayOfWeek( )
{
    return nRTCDayOfWeek;
}

uint8 rtc_getMonth( )
{
    return nRTCMonth;
}

uint32 rtc_getYear( )
{
    return nRTCYear;
}

bool rtc_hasTime( )
{
    return bIntFired;
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
    
    nData |= 0x40;

    // set clock data type to binary, instead of bcd

    nData |= 0x4;

    // give our modified mask back to the rtc clock
    
    outb( RTC_DATA, nData );
    irq_loadHandler( (uint32)rtc_irq, 8 );

    // re-enable interrupts and nmi's
    
    int_sti( );

    // acknowledge rtc clock

    rtc_readRegister( RTC_REGISTER_C );
}
