#include <iostream>
#include <string>
#include "ConsoleUI.h"
#include "TrackerService.h"

int main(int argc, char* argv[]) {
    (void)argc; 
    (void)argv;
    try {
        // Инициализация сервиса с путём к файлу данных
        TrackerService service("records.json");
        service.loadData();
        
        ConsoleUI ui(service);
        ui.run();
        
        service.saveData();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }
}