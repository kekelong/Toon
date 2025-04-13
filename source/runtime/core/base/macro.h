#pragma once

#include "core/log/log_system.h"
#include "runtime/function/global/global_context.h"

#include <chrono>
#include <thread>
using namespace Toon;
#define LOG_HELPER(LOG_LEVEL, format, ...) \
    g_runtime_global_context.m_logger_system->log(LOG_LEVEL, format, __VA_ARGS__);

#define LOG_DEBUG(format, ...) LOG_HELPER(LogSystem::LogLevel::debug, format, __VA_ARGS__);

#define LOG_INFO(format, ...) LOG_HELPER(LogSystem::LogLevel::info, format, __VA_ARGS__);

#define LOG_WARN(format, ...) LOG_HELPER(LogSystem::LogLevel::warn, format, __VA_ARGS__);

#define LOG_ERROR(format, ...) LOG_HELPER(LogSystem::LogLevel::error, format, __VA_ARGS__);

#define LOG_FATAL(format, ...) LOG_HELPER(LogSystem::LogLevel::fatal, format, __VA_ARGS__);

#define ToonSleep(_ms) std::this_thread::sleep_for(std::chrono::milliseconds(_ms));

#define ToonNameOf(name) #name

#ifdef NDEBUG
#define ASSERT(statement)
#define CORE_ASSERT(code, statement)
#else
#define ASSERT(statement) assert(statement)
#define CORE_ASSERT(code, statement) { if(!(code)) { LOG_ERROR(statement); ASSERT(code); } }
#endif
