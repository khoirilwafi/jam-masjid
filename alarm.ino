void set_alarm_trigger(uint8_t index, bool active)
{
    if(active == true)
    {
        alarm_trigger = true;
        alarm_index = index;

        clock_data.imsak.blank = true;
        clock_data.subuh.blank = true;
        clock_data.dhuhur.blank = true;
        clock_data.ashar.blank = true;
        clock_data.maghrib.blank = true;
        clock_data.isya.blank = true;

        switch(index)
        {
            case 0 : clock_data.subuh.blank = false; break;
            case 1 : clock_data.dhuhur.blank = false; break;
            case 2 : clock_data.ashar.blank = false; break;
            case 3 : clock_data.maghrib.blank = false; break;
            case 4 : clock_data.isya.blank = false; break;
        }
    }
    else
    {
        alarm_trigger = false;
        digitalWrite(buzzer_pin, LOW);

        clock_data.imsak.blank = false;
        clock_data.subuh.blank = false;
        clock_data.dhuhur.blank = false;
        clock_data.ashar.blank = false;
        clock_data.maghrib.blank = false;
        clock_data.isya.blank = false;
    }
}

void check_alarm(void)
{
    uint8_t hour_now = clock_data.time_value.hour;
    uint8_t minute_now = clock_data.time_value.minute;

    if(clock_data.time_value.second == 15)
    {
        set_alarm_trigger(0, false);
        return;
    }

    if(clock_data.time_value.second != 0)
    {
        return;
    }
    
    // alarm subuh
    if(hour_now == clock_data.subuh.hour && minute_now == clock_data.subuh.minute)
    {
        set_alarm_trigger(0, true);
        return;
    }

    // alarm dhuhur
    if(hour_now == clock_data.dhuhur.hour && minute_now == clock_data.dhuhur.minute && clock_data.date.dow != Time::kFriday)
    {
        set_alarm_trigger(1, true);
        return;
    }

    // alarm ashar
    if(hour_now == clock_data.ashar.hour && minute_now == clock_data.ashar.minute)
    {
        set_alarm_trigger(2, true);
        return;
    }

    // alarm maghrib
    if(hour_now == clock_data.maghrib.hour && minute_now == clock_data.maghrib.minute)
    {
        set_alarm_trigger(3, true);
        return;
    }

    // alarm isya
    if(hour_now == clock_data.isya.hour && minute_now == clock_data.isya.minute)
    {
        set_alarm_trigger(4, true);
        return;
    }
}

