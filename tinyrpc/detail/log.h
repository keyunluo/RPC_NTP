#pragma once

#ifndef LOG_H_SPSC31OG
#define LOG_H_SPSC31OG

#ifdef TINYRPC_LOGGING

#include "core/fmt/format.h"
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <mutex>
#include <sstream>

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#ifdef _MSC_VER
#include <Windows.h>
#endif

namespace tinyrpc {
namespace detail {
class logger {
public:
    static logger &instance() {
        static logger inst;
        return inst;
    }

    template <typename... Args>
    void trace(const char *channel, const char *file, const char *func,
               std::size_t line, const char *msg, Args... args) {
        basic_log(
            "TRACE", channel,
            TINYRPC_FMT::format("{} ({}:{})", TINYRPC_FMT::format(msg, args...), file, line));
    }

    template <typename... Args>
    void debug(const char *channel, const char *file, const char *func,
               std::size_t line, const char *msg, Args... args) {
        basic_log(
            "DEBUG", channel,
            TINYRPC_FMT::format("{} ({}:{})", TINYRPC_FMT::format(msg, args...), file, line));
    }

    template <typename... Args>
    void warn(const char *channel, const char *msg, Args... args) {
        basic_log("WARN", channel, TINYRPC_FMT::format(msg, args...));
    }

    template <typename... Args>
    void error(const char *channel, const char *msg, Args... args) {
        basic_log("ERROR", channel, TINYRPC_FMT::format(msg, args...));
    }

    template <typename... Args>
    void info(const char *channel, const char *msg, Args... args) {
        basic_log("INFO", channel, TINYRPC_FMT::format(msg, args...));
    }

private:
    logger() {}

#ifdef _MSC_VER
    static std::string now() {
        std::stringstream ss;
        SYSTEMTIME t;
        GetSystemTime(&t);
        ss << TINYRPC_FMT::format("{}-{}-{} {}:{}:{}.{:03}", t.wYear, t.wMonth, t.wDay,
                          t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
        return ss.str();
    }
#else
    static std::string now() {
        std::stringstream ss;
        timespec now_t = {0};
        clock_gettime(CLOCK_REALTIME, &now_t);
        ss << std::put_time(
                  std::localtime(reinterpret_cast<time_t *>(&now_t.tv_sec)),
                  "%F %T")
           << TINYRPC_FMT::format(".{:03}",
                          round(static_cast<double>(now_t.tv_nsec) / 1.0e6));
        return ss.str();
    }
#endif

    void basic_log(const char *severity, const char *channel,
                   std::string const &msg) {
        using TINYRPC_FMT::arg;
        std::lock_guard<std::mutex> lock(mut_print_);
        TINYRPC_FMT::print("{time:16}  {severity:6}  {channel:12}    {msg:40}\n",
                   arg("severity", severity), arg("channel", channel),
                   arg("time", now()), arg("msg", msg));
    }

private:
    std::mutex mut_print_;
};
} /* detail */
} /* tinyrpc */

#define TINYRPC_CREATE_LOG_CHANNEL(Name)                                        \
    static constexpr const char *tinyrpc_channel_name = #Name;

TINYRPC_CREATE_LOG_CHANNEL(global)

#define LOG_INFO(...)                                                          \
    tinyrpc::detail::logger::instance().info(tinyrpc_channel_name, __VA_ARGS__)

#define LOG_WARN(...)                                                          \
    tinyrpc::detail::logger::instance().warn(tinyrpc_channel_name, __VA_ARGS__)

#define LOG_ERROR(...)                                                         \
    tinyrpc::detail::logger::instance().error(tinyrpc_channel_name, __VA_ARGS__)

#define LOG_DEBUG(...)                                                         \
    tinyrpc::detail::logger::instance().debug(tinyrpc_channel_name, __FILE__,    \
                                             __func__, __LINE__, __VA_ARGS__)

#define LOG_TRACE(...)                                                         \
    tinyrpc::detail::logger::instance().trace(tinyrpc_channel_name, __FILE__,    \
                                             __func__, __LINE__, __VA_ARGS__)

#define LOG_EXPR(Level, Expr) LOG_##Level("`" #Expr "` = {}", Expr)

#else

#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_DEBUG(...)
#define LOG_TRACE(...)
#define LOG_EXPR(...)
#define TINYRPC_CREATE_LOG_CHANNEL(...)

#endif

#endif /* end of include guard: LOG_H_SPSC31OG */
