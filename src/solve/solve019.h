#include <euler/common.h>
#pragma once

typedef enum {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY,
    WEEKDAY_MAX
} weekday_t;

typedef enum {
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER,
    MONTH_MAX
} month_t;

typedef struct {
    weekday_t weekday;
    int day;
    month_t month;
    int year;
} date_t;

uint32_t solve(date_t start, date_t end);
bool is_leap_year(date_t date);
size_t month_length(date_t date);
date_t next_month(date_t date);
