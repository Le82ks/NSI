#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace NSI::color {
inline constexpr char reset[] = "\033[0m";
inline constexpr char bold[] = "\033[1m";
inline constexpr char red[] = "\033[31m";
inline constexpr char green[] = "\033[32m";
inline constexpr char yellow[] = "\033[33m";
inline constexpr char blue[] = "\033[34m";
inline constexpr char bg_red[] = "\033[41m";
inline constexpr char bg_yellow[] = "\033[43m";
inline constexpr char bg_blue[] = "\033[44m";
inline constexpr char bg_navy[] = "\033[48;5;17m";

inline std::string now_time() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t value = std::chrono::system_clock::to_time_t(now);
    std::tm local{};
    if (localtime_r(&value, &local) == nullptr) {
        return "time unavailable";
    }
    std::ostringstream output;
    output << std::put_time(&local, "%Y-%m-%d@%H:%M:%S");
    return output.str();
}
}  // namespace NSI::color

// Keep the original names available to the existing UI code.
#define reset NSI::color::reset
#define bold NSI::color::bold
#define red NSI::color::red
#define green NSI::color::green
#define yellow NSI::color::yellow
#define blue NSI::color::blue
#define bg_red NSI::color::bg_red
#define bg_yellow NSI::color::bg_yellow
#define bg_blue NSI::color::bg_blue
#define bg_navy NSI::color::bg_navy
#define now_time NSI::color::now_time
