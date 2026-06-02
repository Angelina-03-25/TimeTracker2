#include "StartCommand.h"

StartCommand::StartCommand(TrackerService& service, const std::string& taskName)
    : service_(service), taskName_(taskName) {}

Result<std::string> StartCommand::execute() {
    auto result = service_.startTask(taskName_);
    if (result.isSuccess()) {
        return Result<std::string>::success(
            "Задача '" + taskName_ + "' запущена (ID: " + 
            std::to_string(result.value()) + ")");
    }
    return Result<std::string>::error(result.errorMessage());
}

bool StartCommand::validate(const std::vector<std::string>& args) {
    (void)args; 
    return !taskName_.empty();
}

std::string StartCommand::getHelp() {
    return "start <название> - Запустить новую задачу";
}