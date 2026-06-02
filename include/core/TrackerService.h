#pragma once
#include <vector>
#include <optional>
#include <string>
#include "TimeEntry.h"
#include "Result.h"
#include "JsonStorage.h"

class TrackerService {
public:
    TrackerService();
    explicit TrackerService(const std::string& dataPath);
    
    Result<uint64_t> startTask(const std::string& taskName);
    Result<std::string> stopTask();
    Result<std::string> listEntries(const std::string& filter = "");
    Result<std::string> editEntry(uint64_t id, const std::string& newTaskName);
    Result<std::string> deleteEntry(uint64_t id);
    Result<std::string> exportData(const std::string& path);
    
    void loadData();
    void saveData();
    
private:
    std::vector<TimeEntry> entries_;
    std::optional<uint64_t> activeId_;
    std::string dataPath_;
    uint64_t nextId_ = 1;
    
    TimeEntry* findActiveEntry();
    TimeEntry* findEntryById(uint64_t id);
};