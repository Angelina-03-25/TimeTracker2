#include "ConsoleUI.h"
#include <iostream>
#include <sstream>

#include "StartCommand.h"
#include "StopCommand.h"
#include "ListCommand.h"
#include "EditCommand.h"
#include "DeleteCommand.h"

ConsoleUI::ConsoleUI(TrackerService& service) : service_(service) {}

void ConsoleUI::run() {
    std::cout << "=== TimeTracker C++ ===\n";
    std::cout << "Введите 'help' для списка команд\n\n";
    
    std::string input;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) break;
        
        if (input.empty()) continue;
        if (input == "exit" || input == "quit") break;
        if (input == "help") {
            showHelp();
            continue;
        }
        
        auto args = parseArgs(input);
        if (args.empty()) continue;
        
        Command* cmd = createCommand(args[0], 
            std::vector<std::string>(args.begin() + 1, args.end()));
        
        if (cmd) {
            if (cmd->validate(args)) {
                printResult(cmd->execute());
            } else {
                std::cout << "Ошибка валидации. " << cmd->getHelp() << "\n";
            }
            delete cmd;
        } else {
            std::cout << "Неизвестная команда. Введите 'help'.\n";
        }
    }
}

void ConsoleUI::showHelp() {
    std::cout << Command::getHelp() << "\n";
}

std::vector<std::string> ConsoleUI::parseArgs(const std::string& input) {
    std::vector<std::string> args;
    std::istringstream iss(input);
    std::string arg;
    
    while (iss >> arg) {
        args.push_back(arg);
    }
    
    return args;
}

Command* ConsoleUI::createCommand(const std::string& cmd, 
                                   const std::vector<std::string>& args) {
    if (cmd == "start" && !args.empty()) {
        return new StartCommand(service_, args[0]);
    }
    if (cmd == "stop") {
        return new StopCommand(service_);
    }
    if (cmd == "list") {
        return new ListCommand(service_, args);
    }
    if (cmd == "edit") {
        return new EditCommand(service_, args);
    }
    if (cmd == "delete") {
        return new DeleteCommand(service_, args);
    }
    return nullptr;
}

void ConsoleUI::printResult(const Result<std::string>& result) {
    if (result.isSuccess()) {
        std::cout << result.value() << "\n";
    } else {
        std::cout << result.errorMessage() << "\n";
    }
}