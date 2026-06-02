#include "ListCommand.h"

ListCommand::ListCommand(TrackerService& service, const std::vector<std::string>& args)
    : service_(service), args_(args) {}

Result<std::string> ListCommand::execute() {
    std::string filter = args_.empty() ? "" : args_[0];
    return service_.listEntries(filter);
}

bool ListCommand::validate(const std::vector<std::string>& args) {
    return true;
}

std::string ListCommand::getHelp() {
    return "list [фильтр] - Показать все записи";
}