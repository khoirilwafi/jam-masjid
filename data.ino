void data_set_clock(uint8_t hour, uint8_t minute, uint8_t second, bool show_colon)
{
    clock_data.time_value.hour = hour;
    clock_data.time_value.minute = minute;
    clock_data.time_value.second = second;
    clock_data.time_value.show_colon = show_colon;
}

void data_set_date(uint8_t dow, uint8_t day, uint8_t month, uint8_t year)
{
    clock_data.date.dow = dow;
    clock_data.date.day = day;
    clock_data.date.month = month;
    clock_data.date.year = year;
}

void data_set_imsak(uint8_t hour, uint8_t minute, bool blank)
{
    clock_data.imsak.hour = hour;
    clock_data.imsak.minute = minute;
    clock_data.imsak.blank = blank;
}

void data_set_subuh(uint8_t hour, uint8_t minute, bool blank)
{
    clock_data.subuh.hour = hour;
    clock_data.subuh.minute = minute;
    clock_data.subuh.blank = blank;
}

void data_set_dhuhur(uint8_t hour, uint8_t minute, bool blank)
{
    clock_data.dhuhur.hour = hour;
    clock_data.dhuhur.minute = minute;
    clock_data.dhuhur.blank = blank;
}

void data_set_ashar(uint8_t hour, uint8_t minute, bool blank)
{
    clock_data.ashar.hour = hour;
    clock_data.ashar.minute = minute;
    clock_data.ashar.blank = blank;
}

void data_set_maghrib(uint8_t hour, uint8_t minute, bool blank)
{
    clock_data.maghrib.hour = hour;
    clock_data.maghrib.minute = minute;
    clock_data.maghrib.blank = blank;
}

void data_set_isya(uint8_t hour, uint8_t minute, bool blank)
{
    clock_data.isya.hour = hour;
    clock_data.isya.minute = minute;
    clock_data.isya.blank = blank;
}

