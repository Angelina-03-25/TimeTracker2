#pragma once
#include "Command.h"
#include "TrackerService.h"

class DeleteCommand : public Command {
public:
    DeleteCommand(TrackerService& service, const std::vector<std::string>& args);
    Result<std::string> execute() override;
    bool validate(const std::vector<std::string>& args) override;
    static std::string getHelp();
    
private:
    TrackerService& service_;
    std::vector<std::string> args_;
};