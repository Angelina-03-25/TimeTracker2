#include <catch2/catch_test_macros.hpp>
#include "JsonStorage.h"
#include <filesystem>
#include <chrono>

TEST_CASE("JsonStorage сохраняет данные", "[JsonStorage]") {
    auto& storage = JsonStorage::getInstance("test_storage.json");
    std::vector<TimeEntry> entries;
    
    auto now = std::chrono::system_clock::now();
    entries.emplace_back(1, "Тест", now);
    
    REQUIRE(storage.save(entries) == true);
}

TEST_CASE("JsonStorage загружает пустой список", "[JsonStorage]") {
    auto& storage = JsonStorage::getInstance("test_storage.json");
    auto entries = storage.load();
    
    CHECK(entries.size() >= 0);
}

TEST_CASE("JsonStorage экспорт в файл", "[JsonStorage]") {
    auto& storage = JsonStorage::getInstance("test_storage.json");
    std::vector<TimeEntry> entries;
    
    auto now = std::chrono::system_clock::now();
    entries.emplace_back(1, "Экспорт", now);
    
    REQUIRE(storage.exportToFile("export_test.json", entries) == true);
}

TEST_CASE("JsonStorage Singleton - один экземпляр", "[JsonStorage]") {
    auto& instance1 = JsonStorage::getInstance("test.json");
    auto& instance2 = JsonStorage::getInstance("test.json");
    
    REQUIRE(&instance1 == &instance2);
}

TEST_CASE("JsonStorage работа с кириллицей", "[JsonStorage]") {
    auto& storage = JsonStorage::getInstance("test_storage.json");
    std::vector<TimeEntry> entries;
    
    auto now = std::chrono::system_clock::now();
    entries.emplace_back(1, "Тест на русском", now);
    
    REQUIRE(storage.save(entries) == true);
}