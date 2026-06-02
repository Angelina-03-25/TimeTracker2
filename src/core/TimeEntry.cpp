#include "TimeEntry.h"
#include <sstream>
#include <iomanip>
#include <ctime>

TimeEntry::TimeEntry(uint64_t id, const std::string& taskName,
                     std::chrono::system_clock::time_point startTime)
    : id_(id), taskName_(taskName), startTime_(startTime) {}

void TimeEntry::setEndTime(std::chrono::system_clock::time_point endTime) {
    endTime_ = endTime;
}

bool TimeEntry::validate() const {
    if (!endTime_.has_value()) return true;
    return endTime_.value() >= startTime_;
}

std::chrono::minutes TimeEntry::getDuration() const {
    if (!endTime_.has_value()) {
        auto now = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::minutes>(now - startTime_);
    }
    return std::chrono::duration_cast<std::chrono::minutes>(endTime_.value() - startTime_);
}

std::string TimeEntry::toJson() const {
    std::ostringstream oss;
    auto start = std::chrono::system_clock::to_time_t(startTime_);
    
    oss << "{\"id\":" << id_ 
        << ",\"task\":\"" << taskName_ << "\""
        << ",\"start\":" << start;
    
    if (endTime_.has_value()) {
        auto end = std::chrono::system_clock::to_time_t(endTime_.value());
        oss << ",\"end\":" << end;
    } else {
        oss << ",\"end\":null";
    }
    
    oss << "}";
    return oss.str();
}

TimeEntry TimeEntry::fromJson(const std::string& json) {
    (void)json;
    TimeEntry entry;
    // В полной версии использовать JSON-библиотеку
    return entry;
}