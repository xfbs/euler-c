#include "solve.h"

uint32_t solve(date_t start, date_t end) {
  int count = (start.day == 1 && start.weekday == SUNDAY) ? 1 : 0;

  while (start.year < end.year || start.month < end.month) {
    start = next_month(start);
    count += start.weekday == SUNDAY ? 1 : 0;
  }

  return count;
}

bool is_leap_year(date_t date) {
  if ((date.year % 4) == 0 && (date.year % 100) != 0)
    return true;
  if ((date.year % 400) == 0)
    return true;
  return false;
}

size_t month_length(date_t date) {
  switch (date.month) {
  case SEPTEMBER:
  case APRIL:
  case JUNE:
  case NOVEMBER:
    return 30;
  case FEBRUARY:
    if (is_leap_year(date)) {
      return 29;
    } else {
      return 28;
    }
  default:
    return 31;
  }
}

date_t next_month(date_t date) {
  // find out how many days the next first of the month is away
  size_t distance = month_length(date);
  distance -= (date.day - 1);

  // set day to first of month
  date.day = 1;

  // advances weekday by the required amount
  date.weekday = (date.weekday + distance) % WEEKDAY_MAX;

  // adjust month and year forward
  if (date.month == DECEMBER) {
    date.year += 1;
  }

  date.month += 1;
  date.month %= MONTH_MAX;

  return date;
}
