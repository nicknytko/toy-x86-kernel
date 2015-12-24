#ifndef RTC_H
#define RTC_H

/* Good documentation for the RTC clock can be found here
   http://bos.asmhackers.net/docs/timer/docs/cmos.pdf */

// RTC Clock Data Ports

#define RTC_INDEX	0x70
#define RTC_DATA	0x71

// RTC Registers

#define RTC_REGISTER_A	0xA
#define RTC_REGISTER_B	0xB
#define RTC_REGISTER_C	0xC

#define RTC_REGISTER_SECOND	0x00
#define RTC_REGISTER_MINUTE	0x02
#define RTC_REGISTER_HOUR	0x04
#define RTC_REGISTER_DAYOFWEEK	0x06
#define RTC_REGISTER_DAY	0x07
#define RTC_REGISTER_MONTH	0x08
#define RTC_REGISTER_YEAR	0x09
#define RTC_REGISTER_CENTURY	0x32

/** Initializes the RTC Clock
 */
void rtc_init( );

/** Gets the current second of the minute 
 */
uint8 rtc_getSecond( );

/** Gets the current minute of the hour
 */
uint8 rtc_getMinute( );

/** Gets the current hour of the day
 */
uint8 rtc_getHour( );

/** Gets the current day of the month
 */
uint8 rtc_getDay( );

/** Gets the current day of the week (1 = sunday)
 */
uint8 rtc_getDayOfWeek( );

/** Gets the current month of the year
 */
uint8 rtc_getMonth( );

/** Gets the current year
 */
uint32 rtc_getYear( );

bool rtc_hasTime( );

#endif
