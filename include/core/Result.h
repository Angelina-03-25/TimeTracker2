#pragma once
#include <optional>
#include <string>

template<typename T>
class Result {
public:
    static Result<T> success(T value) {
        Result<T> r;
        r.success_ = true;
        r.value_ = std::move(value);
        return r;
    }
    
    static Result<T> error(const std::string& message) {
        Result<T> r;
        r.success_ = false;
        r.errorMessage_ = message;
        return r;
    }
    
    bool isSuccess() const { return success_; }
    bool isError() const { return !success_; }
    
    const T& value() const { return *value_; }
    const std::string& errorMessage() const { return errorMessage_; }
    
    bool hasValue() const { return success_ && value_.has_value(); }
    
private:
    bool success_ = false;
    std::optional<T> value_;
    std::string errorMessage_;
};

// Специализация для void
template<>
class Result<void> {
public:
    static Result<void> success() {
        Result<void> r;
        r.success_ = true;
        return r;
    }
    
    static Result<void> error(const std::string& message) {
        Result<void> r;
        r.success_ = false;
        r.errorMessage_ = message;
        return r;
    }
    
    bool isSuccess() const { return success_; }
    bool isError() const { return !success_; }
    const std::string& errorMessage() const { return errorMessage_; }
    
private:
    bool success_ = false;
    std::string errorMessage_;
};