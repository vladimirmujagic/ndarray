#pragma once

#include <fstream>
#include <chrono>


struct Logger {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<float> duration;
    std::ofstream log;
    const char *method_name_;

    Logger(const char *method_name) {
        start = std::chrono::high_resolution_clock::now();
        log.open("ndarray.log", std::ios_base::app | std::ios_base::out);
        method_name_ = method_name;
    }

    ~Logger() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        log << method_name_ << " time: " << ms  << "ms" << std::endl;
        log.close();
    }
};