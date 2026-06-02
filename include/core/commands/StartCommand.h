#pragma once
#include "Command.h"
#include "TrackerService.h"

class StartCommand : public Command {
public:
    explicit StartCommand(TrackerService& service, const std::string& taskName);
    Result<std::string> execute() override;
    bool validate(const std::vector<std::string>& args) override;
    static std::string getHelp();
    
private:
    TrackerService& service_;
    std::string taskName_;
};