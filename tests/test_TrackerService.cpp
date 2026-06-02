#include <catch2/catch_test_macros.hpp>
#include "TrackerService.h"
#include <filesystem>
#include <thread>

TEST_CASE("TrackerService запускает задачу", "[TrackerService]") {
    TrackerService service("test_records.json");
    auto result = service.startTask("Тест");
    
    REQUIRE(result.isSuccess() == true);
    REQUIRE(result.value() == 1);
}

TEST_CASE("TrackerService запрещает вторую активную задачу", "[TrackerService]") {
    TrackerService service("test_records.json");
    service.startTask("Задача 1");
    auto result = service.startTask("Задача 2");
    
    REQUIRE(result.isError() == true);
    REQUIRE(result.errorMessage().find("уже есть активная") != std::string::npos);
}

TEST_CASE("TrackerService останавливает задачу", "[TrackerService]") {
    TrackerService service("test_records.json");
    service.startTask("Тест");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto result = service.stopTask();
    
    REQUIRE(result.isSuccess() == true);
    REQUIRE(result.value().find("завершена") != std::string::npos);
}

TEST_CASE("TrackerService ошибка остановки без активной", "[TrackerService]") {
    TrackerService service("test_records.json");
    auto result = service.stopTask();
    
    REQUIRE(result.isError() == true);
    REQUIRE(result.errorMessage().find("нет активной") != std::string::npos);
}

TEST_CASE("TrackerService список записей", "[TrackerService]") {
    TrackerService service("test_records.json");
    service.startTask("Задача 1");
    service.stopTask();
    auto result = service.listEntries();
    
    REQUIRE(result.isSuccess() == true);
    REQUIRE(result.value().find("Задача 1") != std::string::npos);
}

TEST_CASE("TrackerService редактирование записи", "[TrackerService]") {
    TrackerService service("test_records.json");
    service.startTask("Старое имя");
    service.stopTask();
    auto result = service.editEntry(1, "Новое имя");
    
    REQUIRE(result.isSuccess() == true);
}

TEST_CASE("TrackerService удаление записи", "[TrackerService]") {
    TrackerService service("test_records.json");
    service.startTask("На удаление");
    service.stopTask();
    auto result = service.deleteEntry(1);
    
    REQUIRE(result.isSuccess() == true);
}