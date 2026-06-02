cmake_minimum_required(VERSION 3.14)
project(TimeTracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# === Основной исполняемый файл ===
add_executable(timetracker
    src/main.cpp
    src/core/TimeEntry.cpp
    src/core/TrackerService.cpp
    src/core/commands/StartCommand.cpp
    src/core/commands/StopCommand.cpp
    src/core/commands/ListCommand.cpp
    src/core/commands/EditCommand.cpp
    src/core/commands/DeleteCommand.cpp
    src/data/JsonStorage.cpp
    src/ui/ConsoleUI.cpp
)

target_include_directories(timetracker PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core/commands  # <-- ДОБАВЛЕНО
    ${CMAKE_CURRENT_SOURCE_DIR}/include/data
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui
)

target_compile_options(timetracker PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# === Тесты и Catch2 ===
option(BUILD_TESTS "Сборка тестов" ON)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.0
    )
    FetchContent_MakeAvailable(Catch2)

    # Тестовый исполняемый файл (классы проекта + файлы тестов)
    add_executable(timetracker_tests
        tests/test_TimeEntry.cpp
        tests/test_TrackerService.cpp
        tests/test_JsonStorage.cpp
        tests/test_Commands.cpp
        tests/test_scenarios.cpp
        src/core/TimeEntry.cpp
        src/core/TrackerService.cpp
        src/core/commands/StartCommand.cpp
        src/core/commands/StopCommand.cpp
        src/core/commands/ListCommand.cpp
        src/core/commands/EditCommand.cpp
        src/core/commands/DeleteCommand.cpp
        src/data/JsonStorage.cpp
        src/ui/ConsoleUI.cpp
    )

    target_include_directories(timetracker_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/core
        ${CMAKE_SOURCE_DIR}/include/core/commands  # <-- ДОБАВЛЕНО
        ${CMAKE_SOURCE_DIR}/include/data
        ${CMAKE_SOURCE_DIR}/include/ui
    )

    target_link_libraries(timetracker_tests PRIVATE Catch2::Catch2WithMain)

    enable_testing()
    include(Catch)
    catch_discover_tests(timetracker_tests)
endif()