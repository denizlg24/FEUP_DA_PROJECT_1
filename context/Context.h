//
// Created by deniz on 3/18/2025.
//

#ifndef CONTEXT_H
#define CONTEXT_H
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
using namespace std;
/// @class IContextValue
/// @brief Abstract base class for storing context values of any type.
class IContextValue {
public:
    /// @brief Virtual destructor for proper cleanup of derived classes.
    virtual ~IContextValue();
};

inline IContextValue::~IContextValue() {}

/// @class ContextValue
/// @brief Template class for storing typed values within the Context.
/// @tparam T The type of the value being stored.
template<typename T>
class ContextValue : public IContextValue {
public:
    /// @brief Constructs a ContextValue object with a given value.
    /// @param val The value to store.
    explicit ContextValue(T val) : value(std::move(val)) {}
    /// @brief Retrieves the stored value.
    /// @return Reference to the stored value.
    T& get() { return value; }
protected:
    T value;
};

/// @class Context
/// @brief Manages key-value storage for various types dynamically.
class Context {

public:
    /// @brief Stores a value in the context.
    /// @tparam T The type of the value being stored.
    /// @param key The key under which the value is stored.
    /// @param value The value to store.
    template<typename T>
    void set(const std::string& key, T value) {
        data[key] = std::make_unique<ContextValue<T>>(std::move(value));
    }

    template<typename T>
    T* get(const std::string& key) {
        const auto it = data.find(key);
        if (it != data.end()) {
            auto* typedValue = dynamic_cast<ContextValue<T>*>(it->second.get());
            if (typedValue) {
                return &typedValue->get();
            } else {
                std::cerr << "Error: Type mismatch for key '" << key << "'\n";
            }
        }
        return nullptr;
    }
protected:
    std::unordered_map<std::string, std::unique_ptr<IContextValue>> data;
};
#endif //CONTEXT_H
