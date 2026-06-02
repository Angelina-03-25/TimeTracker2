#include "EditCommand.h"
#include <sstream>

EditCommand::EditCommand(TrackerService& service, const std::vector<std::string>& args)
    : service_(service), args_(args) {}

Result<std::string> EditCommand::execute() {
    if (args_.size() < 2) {
        return Result<std::string>::error("Использование: edit <id> <новое название>");
    }
    
    uint64_t id;
    try {
        id = std::stoull(args_[0]);
    } catch (...) {
        return Result<std::string>::error("Неверный ID.");
    }
    
    std::string newName;
    for (size_t i = 1; i < args_.size(); ++i) {
        if (i > 1) newName += " ";
        newName += args_[i];
    }
    
    return service_.editEntry(id, newName);
}

bool EditCommand::validate(const std::vector<std::string>& args) {
    return args.size() >= 2;
}

std::string EditCommand::getHelp() {
    return "edit <id> <название> - Редактировать задачу";
}