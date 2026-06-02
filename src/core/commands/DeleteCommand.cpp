#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(TrackerService& service, const std::vector<std::string>& args)
    : service_(service), args_(args) {}

Result<std::string> DeleteCommand::execute() {
    if (args_.empty()) {
        return Result<std::string>::error("Использование: delete <id>");
    }
    
    uint64_t id;
    try {
        id = std::stoull(args_[0]);
    } catch (...) {
        return Result<std::string>::error("Неверный ID.");
    }
    
    return service_.deleteEntry(id);
}

bool DeleteCommand::validate(const std::vector<std::string>& args) {
    return !args.empty();
}

std::string DeleteCommand::getHelp() {
    return "delete <id> - Удалить задачу";
}