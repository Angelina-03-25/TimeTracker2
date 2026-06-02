#include <catch2/catch_test_macros.hpp>
#include "TrackerService.h"
#include <filesystem>
#include <thread>

TEST_CASE("Сценарий TS-01: Запуск и остановка", "[Scenario]") {
    TrackerService service("scenario_test.json");
    
    auto startResult = service.startTask("Тестовая задача");
    REQUIRE(startResult.isSuccess() == true);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    auto stopResult = service.stopTask();
    REQUIRE(stopResult.isSuccess() == true);
    REQUIRE(stopResult.value().find("мин.") != std::string::npos);
}

TEST_CASE("Сценарий TS-02: Две активные задачи", "[Scenario]") {
    TrackerService service("scenario_test.json");
    
    service.startTask("Задача 1");
    auto result2 = service.startTask("Задача 2");
    
    REQUIRE(result2.isError() == true);
}

TEST_CASE("Сценарий TS-03: Остановка без активной", "[Scenario]") {
    TrackerService service("scenario_test.json");
    auto result = service.stopTask();
    
    REQUIRE(result.isError() == true);
}

TEST_CASE("Сценарий TS-04: Просмотр записей", "[Scenario]") {
    TrackerService service("scenario_test.json");
    service.startTask("Тест");
    service.stopTask();
    auto result = service.listEntries();
    
    REQUIRE(result.isSuccess() == true);
    REQUIRE(result.value().find("Тест") != std::string::npos);
}

TEST_CASE("Сценарий TS-05: Редактирование записи", "[Scenario]") {
    TrackerService service("scenario_test.json");
    service.startTask("Старое");
    service.stopTask();
    auto result = service.editEntry(1, "Новое");
    
    REQUIRE(result.isSuccess() == true);
}

TEST_CASE("Сценарий TS-06: Удаление записи", "[Scenario]") {
    TrackerService service("scenario_test.json");
    service.startTask("Тест");
    service.stopTask();
    auto result = service.deleteEntry(1);
    
    REQUIRE(result.isSuccess() == true);
}

TEST_CASE("Сценарий TS-09: Кириллица в названии", "[Scenario]") {
    TrackerService service("scenario_test.json");
    auto result = service.startTask("Задача на русском");
    
    REQUIRE(result.isSuccess() == true);
}

TEST_CASE("Сценарий TS-10: Сохранение между запусками", "[Scenario]") {
    TrackerService service1("persist_test.json");
    service1.startTask("Сохранить");
    service1.stopTask();
    service1.saveData();
    
    TrackerService service2("persist_test.json");
    service2.loadData();
    auto result = service2.listEntries();
    
    REQUIRE(result.value().find("Сохранить") != std::string::npos);
    
    std::filesystem::remove("persist_test.json");
}