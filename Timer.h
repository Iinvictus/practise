/**
 * @file Timer.h
 * @author your name (you@domain.com)
 * @brief 简单的计时器
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <chrono>
#include <iostream>

namespace zhuifeng {

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time_point;
    std::string m_process_name;
public:
    explicit Timer(std::string process_name) : m_process_name(process_name) {
        m_start_time_point = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto end_time_point = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time_point).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();
        auto duration = end - start;
        double ms = duration * 0.001;
        std::cout << m_process_name << " took:" << ms << "ms.\n";
    }
};

}



