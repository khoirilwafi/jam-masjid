#include <DS1302.h>
#include "PrayerTimes.h"

#define screen_clk_pin  7 
#define screen_cs_pin   6
#define screen_data_pin 5

#define rtc_data_pin    3 
#define rtc_clk_pin     4
#define rtc_rst_pin     2

#define buzzer_pin      13
#define button_pin      12

uint64_t last_half_of_second = 0;
uint64_t last_one_of_second = 0;

uint8_t hour_now = 0;
uint8_t day_now = 0;

bool alarm_trigger = false;
bool alarm_index = 0;

struct database 
{
    struct time_value { uint8_t hour; uint8_t minute; uint8_t second; bool show_colon; } time_value;
    struct date { uint8_t dow; uint8_t day; uint8_t month; uint8_t year; } date;
    struct imsak { uint8_t hour; uint8_t minute; bool blank; } imsak;
    struct subuh { uint8_t hour; uint8_t minute; bool blank; } subuh;
    struct dhuhur { uint8_t hour; uint8_t minute; bool blank; } dhuhur;
    struct ashar { uint8_t hour; uint8_t minute; bool blank; } ashar;
    struct maghrib { uint8_t hour; uint8_t minute; bool blank; } maghrib;
    struct isya { uint8_t hour; uint8_t minute; bool blank; } isya;
};

struct database clock_data;
DS1302 rtc(rtc_rst_pin, rtc_data_pin, rtc_clk_pin);

void setup(void)
{
    pinMode(screen_cs_pin, OUTPUT);
    pinMode(screen_clk_pin, OUTPUT);
    pinMode(screen_data_pin, OUTPUT);
    pinMode(buzzer_pin, OUTPUT);
    pinMode(button_pin, INPUT_PULLUP);

    Serial.begin(9600);

    init_rtc();
    update_rtc();
    
    update_time_now();
    update_date_now();
    update_prayer_time();
}

void loop(void)
{
    if(millis() - last_half_of_second > 500)   
    {
        update_time_now();
        check_alarm();
        
        last_half_of_second = millis();
    }

    if(millis() - last_one_of_second > 1000)   
    {
        if(alarm_trigger == true)
        {
            digitalWrite(buzzer_pin, !digitalRead(buzzer_pin));
        }
        
        last_one_of_second = millis();
    }

    if(clock_data.time_value.hour != hour_now)
    {
        hour_now = clock_data.time_value.hour;
        update_date_now();
    }

    if(clock_data.date.dow != day_now)
    {
        day_now = clock_data.date.dow;
        update_prayer_time();
    }

    refresh_screen();
}

