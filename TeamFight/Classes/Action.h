#pragma once
#include <functional>
#include <unordered_map>

template<typename ...Args>
class Action {
public:
    using Callback = std::function<void(Args...)>;
    using CallbackId = std::size_t;

    CallbackId add(Callback callback) {
        CallbackId id = nextId++;
        callbacks[id] = std::move(callback);
        return id;
    }

    void remove(CallbackId id) {
        callbacks.erase(id);
    }

    void invoke(Args... args) const {
        for (const auto& [id, cb] : callbacks) {
            cb(args...);
        }
    }
    
private:
    std::unordered_map<CallbackId, Callback> callbacks;
    CallbackId nextId = 1;
};
