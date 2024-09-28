void init_rtc(void)
{
    rtc.halt(false);
}

void update_rtc(void)
{
    // kSunday    = minggu
    // kMonday    = senin
    // kTuesday   = selasa
    // kWednesday = rabu
    // kThursday  = kamis
    // kFriday    = jumat
    // kSaturday  = sabtu
    
    // Saturday, 21 September 2024, at 01:38:50.
    // rtc.writeProtect(false);
    // Time t(2024, 9, 22, 12, 59, 30, Time::kFriday);
    // rtc.time(t);
}

void update_time_now(void)
{
    Time t = rtc.time();
    data_set_clock((uint8_t)t.hr, (uint8_t)t.min, (uint8_t)t.sec, !clock_data.time_value.show_colon);
}

void update_date_now(void)
{
     Time t = rtc.time();
     data_set_date((uint8_t)t.day, (uint8_t)t.date, (uint8_t)t.mon, (uint8_t)(t.yr - 2000));
}

