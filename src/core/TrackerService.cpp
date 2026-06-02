#include "TrackerService.h"
#include <sstream>
#include <iomanip>
#include <ctime>

TrackerService::TrackerService() : dataPath_("records.json") {}

TrackerService::TrackerService(const std::string& dataPath) 
    : dataPath_(dataPath) {}

Result<uint64_t> TrackerService::startTask(const std::string& taskName) {
    if (activeId_.has_value()) {
        return Result<uint64_t>::error("Ошибка: уже есть активная задача. Остановите её сначала.");
    }
    
    if (taskName.empty()) {
        return Result<uint64_t>::error("Ошибка: название задачи не может быть пустым.");
    }
    
    TimeEntry entry(nextId_, taskName, std::chrono::system_clock::now());
    entries_.push_back(entry);
    activeId_ = nextId_++;
    
    saveData();
    return Result<uint64_t>::success(activeId_.value());
}

Result<std::string> TrackerService::stopTask() {
    TimeEntry* entry = findActiveEntry();
    if (!entry) {
        return Result<std::string>::error("Ошибка: нет активной задачи.");
    }
    
    entry->setEndTime(std::chrono::system_clock::now());
    activeId_ = std::nullopt;
    
    auto duration = entry->getDuration();
    std::ostringstream oss;
    oss << "Задача '" << entry->getTaskName() << "' завершена. Длительность: " 
        << duration.count() << " мин.";
    
    saveData();
    return Result<std::string>::success(oss.str());
}

Result<std::string> TrackerService::listEntries(const std::string& filter) {
    (void)filter; 
    if (entries_.empty()) {
        return Result<std::string>::success("Записей нет.");
    }
    
    std::ostringstream oss;
    oss << "=== Записи ===\n";
    
    for (const auto& entry : entries_) {
        if (entry.isActive()) {
            oss << "[ID:" << entry.getId() << "] " << entry.getTaskName() 
                << " — АКТИВНА\n";
        } else {
            oss << "[ID:" << entry.getId() << "] " << entry.getTaskName() 
                << " — " << entry.getDuration().count() << " мин.\n";
        }
    }
    
    return Result<std::string>::success(oss.str());
}

Result<std::string> TrackerService::editEntry(uint64_t id, const std::string& newTaskName) {
    TimeEntry* entry = findEntryById(id);
    if (!entry) {
        return Result<std::string>::error("Ошибка: запись не найдена.");
    }
    
    entry->setTaskName(newTaskName);
    saveData();
    return Result<std::string>::success("Запись обновлена.");
}

Result<std::string> TrackerService::deleteEntry(uint64_t id) {
    auto it = std::find_if(entries_.begin(), entries_.end(),
        [id](const TimeEntry& e) { return e.getId() == id; });
    
    if (it == entries_.end()) {
        return Result<std::string>::error("Ошибка: запись не найдена.");
    }
    
    if (activeId_.has_value() && activeId_.value() == id) {
        activeId_ = std::nullopt;
    }
    
    entries_.erase(it);
    saveData();
    return Result<std::string>::success("Запись удалена.");
}

Result<std::string> TrackerService::exportData(const std::string& path) {
    if (JsonStorage::getInstance(dataPath_).exportToFile(path, entries_)) {
        return Result<std::string>::success("Данные экспортированы в " + path);
    }
    return Result<std::string>::error("Ошибка экспорта.");
}

void TrackerService::loadData() {
    entries_ = JsonStorage::getInstance(dataPath_).load();
    for (const auto& entry : entries_) {
        if (entry.getId() >= nextId_) {
            nextId_ = entry.getId() + 1;
        }
        if (entry.isActive()) {
            activeId_ = entry.getId();
        }
    }
}

void TrackerService::saveData() {
    JsonStorage::getInstance(dataPath_).save(entries_);
}

TimeEntry* TrackerService::findActiveEntry() {
    if (!activeId_.has_value()) return nullptr;
    return findEntryById(activeId_.value());
}

TimeEntry* TrackerService::findEntryById(uint64_t id) {
    for (auto& entry : entries_) {
        if (entry.getId() == id) {
            return &entry;
        }
    }
    return nullptr;
}