#define fajr_angle  20
#define isya_angle  18

#define latitude    -6.8567017
#define longitude   110.5811363
#define time_zone   7

double times[sizeof(TimeName)/sizeof(char*)];
int hour_time, minute_time;

void adjust_time(int &hour, int &minute, int adjust)
{
    minute += adjust;

    if(minute >= 60)
    {
        hour += minute / 60;
        minute = minute % 60;
    }

    if(minute < 0)
    {
        hour -= (abs(minute) / 60) + 1;
        minute = 60 - abs(minute) % 60;
    }

    if (hour >= 24) 
    {
        hour = hour % 24;
    } 
    else if (hour < 0) 
    {
        hour = 24 + hour % 24;
    }
}

void update_prayer_time(void)
{
    set_calc_method(Egypt);
    set_asr_method(Shafii);
    set_high_lats_adjust_method(AngleBased);
    set_fajr_angle(fajr_angle);
    set_isha_angle(isya_angle);

    get_prayer_times(2000 + clock_data.date.year, (int)clock_data.date.month, clock_data.date.day, latitude, longitude, time_zone, times);

    // subuh
    get_float_time_parts(times[0], hour_time, minute_time);
    adjust_time(hour_time, minute_time, 2);
    data_set_subuh(hour_time, minute_time, false);

    // imsak
    adjust_time(hour_time, minute_time, -10);
    data_set_imsak(hour_time, minute_time, false);

    // dhuhur
    get_float_time_parts(times[2], hour_time, minute_time);
    adjust_time(hour_time, minute_time, 2);
    data_set_dhuhur(hour_time, minute_time, false);

    // ashar
    get_float_time_parts(times[3], hour_time, minute_time);
    adjust_time(hour_time, minute_time, 2);
    data_set_ashar(hour_time, minute_time, false);

    // maghrib
    get_float_time_parts(times[5], hour_time, minute_time);
    adjust_time(hour_time, minute_time, 2);
    data_set_maghrib(hour_time, minute_time, false);

    // isya
    get_float_time_parts(times[6], hour_time, minute_time);
    adjust_time(hour_time, minute_time, 2);
    data_set_isya(hour_time, minute_time, false);
}

