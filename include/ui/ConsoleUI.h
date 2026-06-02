#pragma once
#include <string>
#include <vector>
#include "TrackerService.h"
#include "Command.h"

// Forward declarations для команд (чтобы избежать циклических зависимостей)
class StartCommand;
class StopCommand;
class ListCommand;
class EditCommand;
class DeleteCommand;

class ConsoleUI {
public:
    explicit ConsoleUI(TrackerService& service);
    void run();
    void showHelp();
    
private:
    TrackerService& service_;
    
    std::vector<std::string> parseArgs(const std::string& input);
    Command* createCommand(const std::string& cmd, const std::vector<std::string>& args);
    void printResult(const Result<std::string>& result);
};