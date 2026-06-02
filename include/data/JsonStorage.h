#pragma once
#include <string>
#include <vector>
#include "TimeEntry.h"

class JsonStorage {
public:
    JsonStorage(const JsonStorage&) = delete;
    JsonStorage& operator=(const JsonStorage&) = delete;
    
    static JsonStorage& getInstance(const std::string& filePath = "records.json");
    
    bool save(const std::vector<TimeEntry>& entries);
    std::vector<TimeEntry> load();
    bool exportToFile(const std::string& path, const std::vector<TimeEntry>& entries);
    
private:
    explicit JsonStorage(const std::string& filePath);
    std::string filePath_;
};