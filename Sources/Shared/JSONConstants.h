//
// Created by Kacper Harasim on 13.05.2016.
//

#ifndef TIN_JSONCONSTANTS_H
#define TIN_JSONCONSTANTS_H

namespace JSONConstants {
  const std::string CommandType = "commandType";
  const std::string ResponseType = "responseType";
  const std::string ProcessContent = "content";
  const std::string ProcessDetails = "processDetails";
  const std::string ProcessIdentifier = "processIdentifier";
  const std::string StandardError = "standardError";
  const std::string StandardOutput = "standardOutput";
  const std::string SchedulesIdentifier = "schedules";
  const std::string Date = "date";
  const std::string Timestamp = "timestamp";
  const std::string Error = "errorMessage";
  const std::string ResponseStartNewProcess = "startNewProcess";
  const std::string ResponseScheduledProcessEnded = "scheduledProcessEnded";
  const std::string ResponseProcessDeleted = "processDelete";
  const std::string ResponseProcessLaunched = "processLaunch";
  const std::string CommandStartNewProcess = "startNewProcess";
  const std::string CommandStartNewProcessWithSchedule = "startNewProcessWithSchedule";
  const std::string CommandLaunchProcess = "launchProcess";
  const std::string CommandDeleteProcess = "deleteProcess";
  const std::string CommandRequestData = "getRunData";
}

#endif //TIN_JSONCONSTANTS_H
