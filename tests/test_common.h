#pragma once

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

inline void expect(const bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

inline void run_test(const std::string& name, const std::function<void()>& test) {
    std::cout << "[ RUN      ] " << name << "\n";
    test();
    std::cout << "[       OK ] " << name << "\n";
}
