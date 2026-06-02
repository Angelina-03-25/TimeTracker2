#pragma once
#include "Command.h"
#include "TrackerService.h"

class StopCommand : public Command {
public:
    explicit StopCommand(TrackerService& service);
    Result<std::string> execute() override;
    bool validate(const std::vector<std::string>& args) override;
    static std::string getHelp();
    
private:
    TrackerService& service_;
};