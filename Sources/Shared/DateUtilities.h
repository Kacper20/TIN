//
// Created by Kacper Harasim on 02.06.2016.
//

#ifndef TIN_DATEUTILITIES_H
#define TIN_DATEUTILITIES_H


class DateUtilities {
 public:
  static double secondsFromMidnightToNow();
  static double secondsFromMidnightToDate(time_t time);
  static time_t now();
};


#endif //TIN_DATEUTILITIES_H
