#ifndef KA_LOGGER_H_
#define KA_LOGGER_H_

#include <iostream>

#include <spdlog/spdlog.h>

class Logger {
public:
    static void init();

    template<typename FormatString, typename... Args>
    static void log(const char *filename, int lineno, const char *function,
            spdlog::level::level_enum lvl,
            const FormatString &fmt, const Args &... args)
    {
        spdlog::default_logger_raw()->log(spdlog::source_loc{filename, lineno, function}, lvl, fmt, args...);
    }
    
    template<typename FormatString, typename... Args>
    static void debug(const FormatString &fmt, const Args &... args)
    {
        spdlog::debug(fmt, args...);
    }

    template<typename FormatString, typename... Args>
    static void info(const FormatString &fmt, const Args &... args)
    {
        spdlog::info(fmt, args...);
    }

    template<typename FormatString, typename... Args>
    static void warn(const FormatString &fmt, const Args &... args)
    {
        spdlog::warn(fmt, args...);
    }

    template<typename FormatString, typename... Args>
    static void error(const FormatString &fmt, const Args &... args)
    {
        spdlog::error(fmt, args...);
    }

};

#define LOGD(...) Logger::log(__FILE__, __LINE__, __FUNCTION__, spdlog::level::debug, __VA_ARGS__)
#define LOGI(...) Logger::log(__FILE__, __LINE__, __FUNCTION__, spdlog::level::info, __VA_ARGS__)
#define LOGW(...) Logger::log(__FILE__, __LINE__, __FUNCTION__, spdlog::level::warn, __VA_ARGS__)
#define LOGE(...) Logger::log(__FILE__, __LINE__, __FUNCTION__, spdlog::level::err, __VA_ARGS__)
#endif //KA_LOGGER_H_

