//
// Created by Kacper Harasim on 02.06.2016.
//

#include "ProcessScheduledRunHandler.h"
#include "../Shared/DateUtilities.h"
#include <thread>
#include <zconf.h>
#include <cstdio>
#include <fcntl.h>
#include "../Shared/FileManager.h"
#include "PathConstants.h"
#include "ProcessUtilities.h"
#include "../Shared/Responses/ScheduledProcessEndedResponse.h"

#define SCHEDULER_SLEEP_TIME 500

std::pair<time_t, int> ProcessScheduledRunHandler::closestTimeFromCommand(std::shared_ptr<StartProcessWithScheduleCommand> command) {
  time_t best = -1;
  int indx = -1;
  int bestDiff = INT32_MAX;
  double ourTime = DateUtilities::secondsFromMidnightToNow();
  for (int i = 0; i < command->schedule.timestamps.size(); i++) {
    time_t scheduledTime = (time_t)command->schedule.timestamps[i];
    double diff = scheduledTime - ourTime;
    if (diff < 0) { continue; }
    if (diff < bestDiff) {
      bestDiff = int(diff);
      best = int(scheduledTime);
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
                                                                  int timestamp,
                                                                  ResponseCompletion responseCompletion) {
  int status;
  pid_t childPid;
  struct rusage processUsage;
  childPid = wait4(pidToWait, &status, 0, &processUsage);
  collector.addDataForProcessWithId(command->processId, processUsage.ru_utime, processUsage.ru_stime);
  std::lock_guard<std::mutex> guard(threadsInfoMutex);
  tasksInProgress.erase(childPid);

  auto response = std::make_shared<ScheduledProcessEndedResponse>(command->processId, "presentation_day!", timestamp);
  responseCompletion(response);

}

void ProcessScheduledRunHandler::monitorScheduledProcessesToRun() {
  while (1) {
    std::vector<std::shared_ptr<StartProcessWithScheduleCommand> > processesFromQueue;
    std::shared_ptr<StartProcessWithScheduleCommand> command;
    while ((command = queueOfCommandsToSchedule.tryPop()) != nullptr)  {
      processesFromQueue.push_back(command);
      queueOfCommandsToSchedule.pop();

      ProcessUtilities::writeProcessToPersistentStorage(command->generateJSON(),
                                                        command->processContent,
                                                        command->processId);
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
      auto now = DateUtilities::secondsFromMidnightToNow();
      if (topElement.first <= now) {
        //It's element that is ready to run
        //TODO: We need to reschedule it - remember about it - another process has to be rescheduled
        schedulerPriorityQueue.pop();
        std::string basePath = ProcessUtilities::directoryForProcessWithId(topElement.second->processId);
        int newProcessId = ProcessUtilities::runProcess(basePath, std::to_string((int)topElement.first));

        //Create monitoring task
        auto monitoringTask = std::make_shared<ProcessScheduledRunMonitoringTask>(ProcessScheduledRunMonitoringTask(*this,
                                                                                                                newProcessId,
                                                                                                                    topElement.second,
                                                                                                                responseCompletion,
                                                                                                                    (int)topElement.first));
        std::thread monitoringThread(*monitoringTask);
        std::lock_guard<std::mutex> guard(threadsInfoMutex);
        tasksInProgress.insert(std::make_pair(newProcessId, monitoringTask));
        monitoringThread.detach();

      } else {
        break;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(SCHEDULER_SLEEP_TIME));
  }
}

void ProcessScheduledRunHandler::removeProcessData(std::string processId) {
  //TODO: To implement
}