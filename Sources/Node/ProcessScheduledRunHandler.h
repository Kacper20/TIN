//
// Created by Kacper Harasim on 02.06.2016.
//

#ifndef TIN_PROCESSSCHEDULEDRUNHANDLER_H
#define TIN_PROCESSSCHEDULEDRUNHANDLER_H


#include "../Shared/Commands/StartProcessWithScheduleCommand.h"
#include "../Shared/MessagesQueue.h"
#include "../Shared/Responses/Response.h"
#include "ProcessStatisticsCollector.h"

typedef std::function<void(std::shared_ptr<Response>)> ResponseCompletion;


class ProcessScheduledRunHandler {

  struct ProcessScheduledRunMonitoringTask {
    ProcessScheduledRunHandler &processHandler;
    int pidToWait;
    ResponseCompletion &completion;
    std::shared_ptr<StartProcessWithScheduleCommand> command;
    ProcessScheduledRunMonitoringTask(ProcessScheduledRunHandler &handler,
                                    int pidToWait,
                                    std::shared_ptr<StartProcessWithScheduleCommand> command,
                                    ResponseCompletion &completion) : processHandler(handler),
                                                                      pidToWait(pidToWait),
                                                                      completion(completion), command(command) { }
    void operator()() {
      processHandler.monitorScheduledProcessesEndings(command, pidToWait, completion);
    }
  };

  typedef std::pair<time_t, std::shared_ptr<StartProcessWithScheduleCommand>> TimestampWithSchedule;

  struct PqueueTypeCompare
  {
    bool operator()(const TimestampWithSchedule& l, const TimestampWithSchedule& r)
    {
      return l.first > r.first;
    }
  };
 private:

  //Queue that is used by dispatcher to push commands.
  MessagesQueue<StartProcessWithScheduleCommand> queueOfCommandsToSchedule;
  //Internal scheduler queue
  std::priority_queue<TimestampWithSchedule, std::vector<TimestampWithSchedule>, PqueueTypeCompare > schedulerPriorityQueue;
  std::pair<time_t, int> closestTimeFromCommand(std::shared_ptr<StartProcessWithScheduleCommand> command);
  ProcessStatisticsCollector& collector;
 public:
  ProcessScheduledRunHandler(ProcessStatisticsCollector &collector) : collector(collector) { }

  ResponseCompletion responseCompletion;

  void monitorScheduledProcessesEndings(std::shared_ptr<StartProcessWithScheduleCommand>, int pidToWait, ResponseCompletion responseCompletion);
  void scheduleProcess(std::shared_ptr<StartProcessWithScheduleCommand> process);
  void monitorScheduledProcessesToRun();
  void removeProcessData(std::string processId);

};


#endif //TIN_PROCESSSCHEDULEDRUNHANDLER_H
