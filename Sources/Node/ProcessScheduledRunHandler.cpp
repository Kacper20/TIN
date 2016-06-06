//
// Created by Kacper Harasim on 02.06.2016.
//

#include "ProcessScheduledRunHandler.h"
#include "../Shared/DateUtilities.h"
#include <thread>

#define SCHEDULER_SLEEP_TIME 1000000

std::pair<time_t, int> ProcessScheduledRunHandler::closestTimeFromCommand(std::shared_ptr<StartProcessWithScheduleCommand> command) {
  time_t best = -1;
  int indx = -1;
  int bestDiff = INT32_MAX;
  double ourTime = DateUtilities::secondsFromMidnightToNow();
  for (int i = 0; i < command->schedule.timestamps.size(); i++) {
    time_t scheduledTime = (time_t)command->schedule.timestamps[i];
    double another = DateUtilities::secondsFromMidnightToDate(scheduledTime);
    double diff = another - ourTime;
    if (diff < 0) { continue; }
    if (diff < bestDiff) {
      bestDiff = int(diff);
      best = int(another);
      indx = i;
    }
  }
  return std::make_pair(best, indx);
}

void ProcessScheduledRunHandler::scheduleProcess(std::shared_ptr<StartProcessWithScheduleCommand> process) {
  queueOfCommandsToSchedule.push(process);
}

void ProcessScheduledRunHandler::monitorScheduledProcessesEndings(std::shared_ptr<StartProcessWithScheduleCommand> command,
                                                                  int pidToWait,
                                                                  ResponseCompletion responseCompletion) {
  //TODO: Implement this.
  pid_t childPid;
  int status;
  struct rusage processUsage;
  childPid = wait4(pidToWait, &status, 0, &processUsage);
  collector.addDataForProcessWithId(command->processId, processUsage.ru_utime, processUsage.ru_stime);


}

void ProcessScheduledRunHandler::monitorScheduledProcessesToRun() {
  while (1) {
    std::vector<std::shared_ptr<StartProcessWithScheduleCommand> > processesFromQueue;
    std::shared_ptr<StartProcessWithScheduleCommand> command;
    while ((command = queueOfCommandsToSchedule.tryPop()) != nullptr)  {
      processesFromQueue.push_back(command);
    }
    for (auto &command: processesFromQueue) {

      auto bestTimeWithIndex = closestTimeFromCommand(command);
      time_t bestTime = bestTimeWithIndex.first;

      if (bestTime != -1) {
        schedulerPriorityQueue.push(std::make_pair(bestTime, command));
      }
    }
    //Now we need to pop everything from queue and run processes;
    while (true) {
      if (schedulerPriorityQueue.size() == 0) { break; }
      auto topElement = schedulerPriorityQueue.top();
      if (topElement.first <= DateUtilities::now()) {
        //It's element that is ready to run
        //TODO: We need to reschedule it

      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(SCHEDULER_SLEEP_TIME));
  }
}

void ProcessScheduledRunHandler::removeProcessData(std::string processId) {
  //TODO: To implement
}