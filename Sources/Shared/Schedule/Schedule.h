#include <vector>
#include "../../Libraries/json/json.h"
//
// Created by Kacper Harasim on 22.05.2016.
//

#ifndef TIN_SCHEDULE_H
#define TIN_SCHEDULE_H

#include<iostream>

class Schedule {

 private:
  std::vector<int> timestamps;

 public:
  Schedule() {}
  Schedule(std::vector<int> timestamps) : timestamps(timestamps) {}
  Json::Value generateJson() {
    Json::Value array;
    for (auto const &timestamp : timestamps) {
      array.append(timestamp);
    }
    return array;
  }
};


#endif //TIN_SCHEDULE_H
