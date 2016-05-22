#include <vector>
#include "../../Libraries/json/json.h"
ehe//
// Created by Kacper Harasim on 22.05.2016.
//

#ifndef TIN_SCHEDULE_H
#define TIN_SCHEDULE_H


class Schedule {

 private:
  std::vector<int> timestamps;

 public:
  Schedule(std::vector<int> timestamps) : timestamps(timestamps) {}
  Json::Value generateJson() {
    
  }
};


#endif //TIN_SCHEDULE_H
