#include <catch2/catch_test_macros.hpp>
#include "TimeEntry.h"
#include <chrono>
#include <thread>

TEST_CASE("TimeEntry создаётся с корректными данными", "[TimeEntry]") {
    auto now = std::chrono::system_clock::now();
    TimeEntry entry(1, "Тестовая задача", now);
    
    REQUIRE(entry.getId() == 1);
    REQUIRE(entry.getTaskName() == "Тестовая задача");
    REQUIRE(entry.isActive() == true);
}

TEST_CASE("TimeEntry завершается корректно", "[TimeEntry]") {
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto end = std::chrono::system_clock::now();
    
    TimeEntry entry(1, "Задача", start);
    entry.setEndTime(end);
    
    REQUIRE(entry.isActive() == false);
    REQUIRE(entry.validate() == true);
}

TEST_CASE("TimeEntry рассчитывает длительность", "[TimeEntry]") {
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    TimeEntry entry(1, "Задача", start);
    entry.setEndTime(std::chrono::system_clock::now());
    
    auto duration = entry.getDuration();
    REQUIRE(duration.count() >= 0);
}

TEST_CASE("TimeEntry не позволяет завершить раньше начала", "[TimeEntry]") {
    auto end = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto start = std::chrono::system_clock::now();
    
    TimeEntry entry(1, "Задача", start);
    entry.setEndTime(end);
    
    REQUIRE(entry.validate() == false);
}

TEST_CASE("TimeEntry сериализуется в JSON", "[TimeEntry]") {
    auto now = std::chrono::system_clock::now();
    TimeEntry entry(1, "Задача", now);
    
    std::string json = entry.toJson();
    REQUIRE(json.find("\"id\":1") != std::string::npos);
    REQUIRE(json.find("\"task\":\"Задача\"") != std::string::npos);
}

TEST_CASE("TimeEntry с кириллицей в названии", "[TimeEntry]") {
    auto now = std::chrono::system_clock::now();
    TimeEntry entry(1, "Задача на русском", now);
    
    REQUIRE(entry.getTaskName() == "Задача на русском");
    REQUIRE(entry.toJson().find("русском") != std::string::npos);
}

TEST_CASE("TimeEntry с пустым названием", "[TimeEntry]") {
    auto now = std::chrono::system_clock::now();
    TimeEntry entry(1, "", now);
    
    REQUIRE(entry.getTaskName() == "");
    REQUIRE(entry.validate() == true);
}