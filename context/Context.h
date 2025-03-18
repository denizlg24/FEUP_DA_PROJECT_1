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

class IContextValue {
public:
    virtual ~IContextValue();
};

inline IContextValue::~IContextValue() {}

template<typename T>
class ContextValue : public IContextValue {
public:
    explicit ContextValue(T val) : value(std::move(val)) {}
    T& get() { return value; }
protected:
    T value;
};

class Context {

public:
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
