#ifndef QUARK_LOGGER_H
#define QUARK_LOGGER_H

#include <concepts>
#include <cstdint>
#include <iostream>
#include <string_view>

namespace quark {

enum struct LogLevel : std::uint8_t { Debug, Info, Warning, Error, Fatal };

namespace details {

template <typename ValueType, typename Stream>
concept HasPutToOperator =
    requires(const ValueType& value, Stream& stream) { stream << value; };

struct Logger {
    template <typename... Args>
    void log(LogLevel level, const Args&... args) const noexcept {
        if (level < log_level) {
            return;
        }

        (out << ... << args);
    }

    std::ostream& out;
    LogLevel log_level = LogLevel::Info;
};

[[nodiscard]] auto& get_logger() noexcept {
    static Logger instance{std::cout};
    return instance;
}

} // namespace details

template <details::HasPutToOperator<std::ostream>... Args>
void print(LogLevel level, const Args&... args) noexcept {
    details::get_logger().log(level, args...);
}

template <typename... Args> void debug(const Args&... args) noexcept {
    print(LogLevel::Debug, "debug: ", args...);
}

template <typename... Args> void info(const Args&... args) noexcept {
    print(LogLevel::Info, "info: ", args...);
}

template <typename... Args> void warning(const Args&... args) noexcept {
    print(LogLevel::Warning, "warning: ", args...);
}

template <typename... Args> void error(const Args&... args) noexcept {
    print(LogLevel::Error, "error: ", args...);
}

template <typename... Args> void fatal(const Args&... args) noexcept {
    print(LogLevel::Fatal, "fatal: ", args...);
}

} // namespace quark

#endif
