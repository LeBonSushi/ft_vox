#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>

enum LogType
{
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO
};

class Logger
{
public:
    Logger() = default;

private:
    static std::string getColorCode(LogType type) {
        switch (type) {
            case LOG_ERROR:   return "\033[31m"; // Red
            case LOG_WARNING: return "\033[33m"; // Yellow
            case LOG_INFO:     return "\033[0m";  // Default
        }
        return "\033[0m";
    }
	static void logInternal(const std::string& message, LogType type) {
		const auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm tm{};
		
		#ifdef _WIN32
			localtime_s(&tm, &now_c);
		#else
			localtime_r(&now_c, &tm);
		#endif

		std::string color = getColorCode(type);
		std::string reset = "\033[0m";

		std::cout << color
				<< "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] "
				<< message
				<< reset << std::endl;
	}
public:

    template<typename First, typename... Rest>
    static void log(LogType type, const First& first, const Rest&... rest) {
        std::ostringstream oss;
        oss << first;
        (void)(oss << ... << rest);
        logInternal(oss.str(), type);
    }
};