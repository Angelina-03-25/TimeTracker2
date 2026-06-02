#pragma once
#include <string>
#include <chrono>
#include <optional>
#include <cstdint>

class TimeEntry {
public:
    TimeEntry() = default;
    TimeEntry(uint64_t id, const std::string& taskName, 
              std::chrono::system_clock::time_point startTime);
    
    uint64_t getId() const { return id_; }
    const std::string& getTaskName() const { return taskName_; }
    const std::chrono::system_clock::time_point& getStartTime() const { return startTime_; }
    const std::optional<std::chrono::system_clock::time_point>& getEndTime() const { return endTime_; }
    
    void setEndTime(std::chrono::system_clock::time_point endTime);
    void setTaskName(const std::string& name) { taskName_ = name; }
    
    bool isActive() const { return !endTime_.has_value(); }
    bool validate() const;
    std::chrono::minutes getDuration() const;
    
    std::string toJson() const;
    static TimeEntry fromJson(const std::string& json);
    
private:
    uint64_t id_ = 0;
    std::string taskName_;
    std::chrono::system_clock::time_point startTime_;
    std::optional<std::chrono::system_clock::time_point> endTime_;
};