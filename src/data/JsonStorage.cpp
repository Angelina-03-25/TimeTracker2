#include "JsonStorage.h"
#include <fstream>
#include <sstream>
#include <string>

JsonStorage::JsonStorage(const std::string& filePath) : filePath_(filePath) {}

JsonStorage& JsonStorage::getInstance(const std::string& filePath) {
    static JsonStorage instance(filePath);
    return instance;
}

bool JsonStorage::save(const std::vector<TimeEntry>& entries) {
    std::ofstream out(filePath_);
    if (!out) return false;
    
    out << "[\n";
    for (size_t i = 0; i < entries.size(); ++i) {
        out << "  " << entries[i].toJson();
        if (i < entries.size() - 1) out << ",";
        out << "\n";
    }
    out << "]\n";
    
    return out.good();
}

std::vector<TimeEntry> JsonStorage::load() {
    std::vector<TimeEntry> entries;
    std::ifstream in(filePath_);
    if (!in) return entries;

    std::string line;
    while (std::getline(in, line)) {
        if (line.find('{') == std::string::npos) continue;

        uint64_t id = 0;
        std::string task;
        time_t startTs = 0;
        bool hasEnd = false;
        time_t endTs = 0;

        // Извлечение id
        size_t idPos = line.find("\"id\":");
        if (idPos != std::string::npos) {
            size_t valStart = idPos + 5;
            size_t valEnd = line.find_first_of(",}", valStart);
            try { id = std::stoull(line.substr(valStart, valEnd - valStart)); } catch(...) {}
        }

        // Извлечение task
        size_t taskPos = line.find("\"task\":\"");
        if (taskPos != std::string::npos) {
            size_t valStart = taskPos + 8;
            size_t valEnd = line.find("\"", valStart);
            if (valEnd != std::string::npos) task = line.substr(valStart, valEnd - valStart);
        }

        // Извлечение start
        size_t startPos = line.find("\"start\":");
        if (startPos != std::string::npos) {
            size_t valStart = startPos + 8;
            size_t valEnd = line.find_first_of(",}", valStart);
            try { startTs = std::stoll(line.substr(valStart, valEnd - valStart)); } catch(...) {}
        }

        // Извлечение end
        size_t endPos = line.find("\"end\":");
        if (endPos != std::string::npos) {
            size_t valStart = endPos + 6;
            if (line.substr(valStart, 4) == "null") {
                hasEnd = false;
            } else {
                hasEnd = true;
                size_t valEnd = line.find_first_of(",}", valStart);
                try { endTs = std::stoll(line.substr(valStart, valEnd - valStart)); } catch(...) {}
            }
        }

        auto tpStart = std::chrono::system_clock::from_time_t(startTs);
        TimeEntry entry(id, task, tpStart);
        if (hasEnd) {
            entry.setEndTime(std::chrono::system_clock::from_time_t(endTs));
        }
        entries.push_back(entry);
    }
    return entries;
}

bool JsonStorage::exportToFile(const std::string& path, const std::vector<TimeEntry>& entries) {
    std::ofstream out(path);
    if (!out) return false;
    
    out << "[\n";
    for (size_t i = 0; i < entries.size(); ++i) {
        out << "  " << entries[i].toJson();
        if (i < entries.size() - 1) out << ",";
        out << "\n";
    }
    out << "]\n";
    
    return out.good();
}