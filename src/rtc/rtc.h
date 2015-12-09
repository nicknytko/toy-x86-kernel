#ifndef RTC_H
#define RTC_H

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
#define RTC_REGISTER_DAY	0x07
#define RTC_REGISTER_MONTH	0x08
#define RTC_REGISTER_YEAR	0x09

void rtc_init( );

#endif
