#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>


#define reset      "\033[0m"
#define bold       "\033[1m"
#define black      "\033[30m"
#define red        "\033[31m"
#define green      "\033[32m"
#define yellow     "\033[33m"
#define blue       "\033[34m"
#define magenta    "\033[35m"
#define cyan       "\033[36m"
#define white      "\033[37m"
#define gray       "\033[90m"
#define bg_black   "\033[40m"
#define bg_red     "\033[41m"
#define bg_green   "\033[42m"
#define bg_yellow  "\033[43m"
#define bg_blue    "\033[44m"
#define bg_magenta "\033[45m"
#define bg_cyan    "\033[46m"
#define bg_white   "\033[47m"
#define bg_navy    "\033[48;5;17m"
  
inline std::string now_time() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_val = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now_val), "%Y-%m-%d@%H:%M:%S");
        return oss.str();
    }
const std::string scan_time = now_time();