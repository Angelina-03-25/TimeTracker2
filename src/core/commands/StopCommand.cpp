#include "StopCommand.h"

StopCommand::StopCommand(TrackerService& service) : service_(service) {}

Result<std::string> StopCommand::execute() {
    return service_.stopTask();
}

bool StopCommand::validate(const std::vector<std::string>& args) {
    return true;
}

std::string StopCommand::getHelp() {
    return "stop - Остановить активную задачу";
}