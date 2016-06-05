//
// Created by Kacper Harasim on 05.06.2016.
//

#ifndef TIN_PROCESSSTATISTICSCOLLECTOR_H
#define TIN_PROCESSSTATISTICSCOLLECTOR_H
#import "../Shared/Responses/Response.h"

typedef std::function<void(std::shared_ptr<Response>)> ResponseCompletion;

class ProcessStatisticsCollector {

 public:
  ResponseCompletion responseCompletion;
  //Function called when someone

};


#endif //TIN_PROCESSSTATISTICSCOLLECTOR_H
