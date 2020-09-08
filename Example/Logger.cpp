#include "Logger.h"
#include "spdlog/spdlog.h"

void Logger::init() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%m/%d %H:%M:%S.%e][%P/%t][%l][%s:%#/%!]$ %v");
}

