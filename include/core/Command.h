#pragma once
#include <string>
#include <vector>
#include <optional>
#include "Result.h"

class Command {
public:
    virtual ~Command() = default;
    virtual Result<std::string> execute() = 0;
    virtual bool validate(const std::vector<std::string>& args) = 0;
    
    // Статический метод с реализацией в заголовке
    static std::string getHelp() {
        return "Доступные команды:\n"
               "  start <task>  - Запустить задачу\n"
               "  stop          - Остановить задачу\n"
               "  list          - Показать записи\n"
               "  edit <id> <name> - Редактировать задачу\n"
               "  delete <id>   - Удалить задачу\n"
               "  export <path> - Экспорт в JSON\n"
               "  help          - Показать справку\n"
               "  exit          - Выход";
    }
};