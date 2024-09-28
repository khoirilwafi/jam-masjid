const char colon_flag = 0x7f; 

const char font_odd[10] = {
    0x81, // 0b10000001
    0xF5, // 0b11110101
    0xA2, // 0b10100010
    0xE0, // 0b11100000
    0xD4, // 0b11010100
    0xC8, // 0b11001000
    0x88, // 0b10001000
    0xE5, // 0b11100101
    0x80, // 0b10000000
    0xC0, // 0b11000000
};

const char font_even[10] = {
    0x08, // 0b00001000
    0x7B, // 0b01111011
    0x14, // 0b00010100
    0x11, // 0b00010001
    0x23, // 0b00100011
    0x81, // 0b10000001
    0x80, // 0b10000000
    0x5B, // 0b01011011
    0x00, // 0b00000000
    0x01, // 0b00000001
};


uint8_t screen_buffer[10];

uint8_t get_ones(uint8_t number)
{
    return number % 10;
}

uint8_t get_tens(uint8_t number)
{
    return number / 10;
}

void send_buffer(void)
{   
    for(uint8_t i=0; i<10; i++)
    {
        shiftOut(screen_data_pin, screen_clk_pin, MSBFIRST, screen_buffer[i]);
    }

    digitalWrite(screen_cs_pin, LOW);
    digitalWrite(screen_cs_pin, HIGH);
}

void refresh_screen()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t index = (uint8_t)(1 << i);

        screen_buffer[0] = index;
        screen_buffer[2] = index;
        screen_buffer[4] = index;
        screen_buffer[6] = index;
        screen_buffer[8] = index;

        switch(i)
        {
            case 0:
                screen_buffer[1] = (clock_data.maghrib.blank == true) ? 0xff : font_odd[get_tens(clock_data.maghrib.hour)];
                screen_buffer[3] = (clock_data.dhuhur.blank == true) ? 0xff : font_odd[get_tens(clock_data.dhuhur.hour)];
                screen_buffer[5] = (clock_data.imsak.blank == true) ? 0xff : font_odd[get_tens(clock_data.imsak.hour)];
                
                screen_buffer[7] = font_odd[get_tens(clock_data.date.day)];
                screen_buffer[9] = font_odd[get_tens(clock_data.time_value.hour)];
            break;

            case 1:
                screen_buffer[1] = (clock_data.maghrib.blank == true) ? 0xff : font_even[get_ones(clock_data.maghrib.hour)];
                screen_buffer[3] = (clock_data.dhuhur.blank == true) ? 0xff : font_even[get_ones(clock_data.dhuhur.hour)];
                screen_buffer[5] = (clock_data.imsak.blank == true) ? 0xff : font_even[get_ones(clock_data.imsak.hour)];
                
                screen_buffer[7] = font_even[get_ones(clock_data.date.day)];
                screen_buffer[9] = font_even[get_ones(clock_data.time_value.hour)];
            break;

            case 2:
                screen_buffer[1] = (clock_data.maghrib.blank == true) ? 0xff : font_odd[get_tens(clock_data.maghrib.minute)] & colon_flag;
                screen_buffer[3] = (clock_data.dhuhur.blank == true) ? 0xff : font_odd[get_tens(clock_data.dhuhur.minute)] & colon_flag;
                screen_buffer[5] = (clock_data.imsak.blank == true) ? 0xff : font_odd[get_tens(clock_data.imsak.minute)] & colon_flag;
                
                screen_buffer[7] = font_odd[get_tens(clock_data.date.month)]  & colon_flag;
                screen_buffer[9] = (clock_data.time_value.show_colon == true) ? font_odd[get_tens(clock_data.time_value.minute)] & colon_flag : font_odd[get_tens(clock_data.time_value.minute)];
            break;

            case 3:
                screen_buffer[1] = (clock_data.maghrib.blank == true) ? 0xff : font_even[get_ones(clock_data.maghrib.minute)];
                screen_buffer[3] = (clock_data.dhuhur.blank == true) ? 0xff : font_even[get_ones(clock_data.dhuhur.minute)];
                screen_buffer[5] = (clock_data.imsak.blank == true) ? 0xff : font_even[get_ones(clock_data.imsak.minute)];
                
                screen_buffer[7] = font_even[get_ones(clock_data.date.month)];
                screen_buffer[9] = font_even[get_ones(clock_data.time_value.minute)];
            break;

            case 4:
                screen_buffer[1] = (clock_data.isya.blank == true) ? 0xff : font_odd[get_tens(clock_data.isya.hour)];
                screen_buffer[3] = (clock_data.ashar.blank == true) ? 0xff : font_odd[get_tens(clock_data.ashar.hour)];
                screen_buffer[5] = (clock_data.subuh.blank == true) ? 0xff : font_odd[get_tens(clock_data.subuh.hour)];

                screen_buffer[7] = font_odd[get_tens(clock_data.date.year)]  & colon_flag;
            break;

            case 5:
                screen_buffer[1] = (clock_data.isya.blank == true) ? 0xff : font_even[get_ones(clock_data.isya.hour)];
                screen_buffer[3] = (clock_data.ashar.blank == true) ? 0xff : font_even[get_ones(clock_data.ashar.hour)];
                screen_buffer[5] = (clock_data.subuh.blank == true) ? 0xff : font_even[get_ones(clock_data.subuh.hour)];

                screen_buffer[7] = font_even[get_ones(clock_data.date.year)];
            break;

            case 6:
                screen_buffer[1] = (clock_data.isya.blank == true) ? 0xff : font_odd[get_tens(clock_data.isya.minute)]  & colon_flag;
                screen_buffer[3] = (clock_data.ashar.blank == true) ? 0xff : font_odd[get_tens(clock_data.ashar.minute)]  & colon_flag;
                screen_buffer[5] = (clock_data.subuh.blank == true) ? 0xff : font_odd[get_tens(clock_data.subuh.minute)]  & colon_flag;
            break;

            case 7:
                screen_buffer[1] = (clock_data.isya.blank == true) ? 0xff : font_even[get_ones(clock_data.isya.minute)];
                screen_buffer[3] = (clock_data.ashar.blank == true) ? 0xff : font_even[get_ones(clock_data.ashar.minute)];
                screen_buffer[5] = (clock_data.subuh.blank == true) ? 0xff : font_even[get_ones(clock_data.subuh.minute)];
            break;
        }

        send_buffer();
        delayMicroseconds(500);
    }
}

