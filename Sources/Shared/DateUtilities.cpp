//
// Created by Kacper Harasim on 02.06.2016.
//

#include <ctime>
#include "DateUtilities.h"


double DateUtilities::secondsFromMidnightToDate(time_t time) {
  struct tm beginOfTheDay;

  beginOfTheDay = *localtime(&time);

  beginOfTheDay.tm_hour = 0; beginOfTheDay.tm_min = 0; beginOfTheDay.tm_sec = 0;
  return difftime(time,mktime(&beginOfTheDay));
}

double DateUtilities::secondsFromMidnightToNow() {
  time_t now;
  time(&now);  /* get current time; same as: now = time(NULL)  */
  return secondsFromMidnightToDate(now);
}

time_t DateUtilities::now() {
  time_t now;
  time(&now);
  return now;
}