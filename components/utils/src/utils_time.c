/*
EPOCH to human readable time and date converter for microcontrollers (PIC, AVR, Arduino, STM32)
Current EPOCH time can be found at https://www.epochconverter.com/
The code can be suitably modified to suit your requirements. I have extensively
tested this code with valid inputs. If you have any questions or if you find a bug, please contact me. 
Author: Siddharth Singh <sidsingh78@gmail.com>
Ver:1.0
Date: June 15, 2017 
*/
#include <stdlib.h>
#include <utils_time.h>
//Thu=4, Fri=5, Sat=6, Sun=0, Mon=1, Tue=2, Wed=3

int utils_time_date_from_epoch(unsigned int epoch, utils_time_date_t *date)
{
    int i;
    unsigned short temp_days;
    unsigned char month_days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    unsigned char week_days[7] = {4,5,6,0,1,2,3};

    date->leap_days = 0; 
    date->leap_year_ind = 0;

    // Add or substract time zone here. 
    //epoch += 19800; //GMT +5:30 = +19800 seconds 

    date->ntp_second = epoch%60;
    epoch /= 60;
    date->ntp_minute = epoch%60;
    epoch /= 60;
    date->ntp_hour  = epoch%24;
    epoch /= 24;

    date->days_since_epoch = epoch;      //number of days since epoch
    date->ntp_week_day = week_days[date->days_since_epoch%7];  //Calculating WeekDay

    date->ntp_year = 1970 + (date->days_since_epoch/365); // ball parking year, may not be accurate!
    for (i = 1972, date->leap_days = 0; i < date->ntp_year; i+=4) {
        // Calculating number of leap days since epoch/1970
        if(((i%4==0) && (i%100!=0)) || (i%400==0)) {
            date->leap_days++;
        }
    }

    date->ntp_year = 1970 + ((date->days_since_epoch - date->leap_days)/365); // Calculating accurate current year by (days_since_epoch - extra leap days)
    if (((date->ntp_year%4==0) && (date->ntp_year%100!=0)) || (date->ntp_year%400==0))  {
        month_days[1]=29;     //February = 29 days for leap years
        date->leap_year_ind = 1;    //if current year is leap, set indicator to 1 
    } else {
        month_days[1]=28; //February = 28 days for non-leap years 
        date->leap_year_ind = 0;    //if current year is leap, set indicator to 1 
    }
    for (i = 1972, date->leap_days = 0; i < date->ntp_year; i+=4) {
        // Calculating number of leap days since epoch/1970
        if(((i%4==0) && (i%100!=0)) || (i%400==0)) {
            date->leap_days++;
        }
    }
    date->day_of_year = date->days_since_epoch - date->leap_days - (date->ntp_year - 1970) * 365 + 1;


    temp_days = 0;

    for (date->ntp_month = 0; date->ntp_month <= 11; date->ntp_month++) {
        //calculating current Month
        if (date->day_of_year <= temp_days) {
            break; 
        }
        temp_days = temp_days + month_days[date->ntp_month];
    }

    temp_days = temp_days - month_days[date->ntp_month-1]; //calculating current Date
    date->ntp_date = date->day_of_year - temp_days;

    return 0;
}
