#include <catch2/catch_test_macros.hpp>
#include "StartCommand.h"
#include "StopCommand.h"
#include "ListCommand.h"
#include "TrackerService.h"

TEST_CASE("StartCommand создаётся корректно", "[Command]") {
    TrackerService service("test.json");
    StartCommand cmd(service, "Задача");
    
    REQUIRE(cmd.validate({"Задача"}) == true);
}

TEST_CASE("StartCommand execute успешный", "[Command]") {
    TrackerService service("test.json");
    StartCommand cmd(service, "Тест");
    auto result = cmd.execute();
    
    REQUIRE(result.isSuccess() == true);
}

TEST_CASE("StopCommand без активной задачи", "[Command]") {
    TrackerService service("test.json");
    StopCommand cmd(service);
    auto result = cmd.execute();
    
    REQUIRE(result.isError() == true);
}

TEST_CASE("ListCommand пустой список", "[Command]") {
    TrackerService service("test.json");
    ListCommand cmd(service, {});
    auto result = cmd.execute();
    
    REQUIRE(result.isSuccess() == true);
}

TEST_CASE("Command валидация аргументов", "[Command]") {
    TrackerService service("test.json");
    StartCommand cmd(service, "");
    
    REQUIRE(cmd.validate({}) == false);
}

TEST_CASE("Command справка", "[Command]") {
    std::string help = Command::getHelp();
    
    REQUIRE(help.find("start") != std::string::npos);
    REQUIRE(help.find("stop") != std::string::npos);
    REQUIRE(help.find("help") != std::string::npos);
}

TEST_CASE("Command неизвестная команда", "[Command]") {
    TrackerService service("test.json");
    ListCommand cmd(service, {});
    
    REQUIRE(cmd.validate({}) == true);
}