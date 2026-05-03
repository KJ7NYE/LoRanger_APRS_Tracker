/*
 * Minimal logger.h shim for nRF52 builds. See logger_level.h for the rationale.
 *
 * Provides the same `logging::Logger` API surface used across the codebase
 * (`log()`, `setSerial()`, `setDebugLevel()`, syslog setters as no-ops) so that
 * existing `logger.log(LEVEL, "Module", fmt, ...)` call sites compile unchanged.
 * Output goes to a single Stream* (defaults to Serial); syslog is a no-op since
 * nRF52 has no IP networking.
 */
#pragma once

#include <Arduino.h>
#include <stdarg.h>
#include "logger_level.h"

namespace logging {

class Logger {
public:
    Logger() : _serial(&Serial), _level(LOGGER_LEVEL_INFO) {}
    Logger(LoggerLevel level) : _serial(&Serial), _level(level) {}
    Logger(Stream* serial) : _serial(serial), _level(LOGGER_LEVEL_INFO) {}
    Logger(Stream* serial, LoggerLevel level) : _serial(serial), _level(level) {}
    ~Logger() = default;

    void setSerial(Stream* serial) { _serial = serial; }
    void setDebugLevel(LoggerLevel level) { _level = level; }

    // Syslog calls are no-ops on nRF (no IP stack).
    void setSyslogServer(const String&, unsigned int, const String&) {}
    void setSyslogServer(uint32_t, unsigned int, const String&) {}

    void log(LoggerLevel level, const String& module, const char* fmt, ...) {
        if (level > _level || _serial == nullptr) return;
        _serial->print('[');
        _serial->print(levelTag(level));
        _serial->print("] ");
        _serial->print(module);
        _serial->print(": ");
        char buf[256];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt, args);
        va_end(args);
        _serial->println(buf);
    }

private:
    static const char* levelTag(LoggerLevel l) {
        switch (l) {
            case LOGGER_LEVEL_ERROR: return "ERR";
            case LOGGER_LEVEL_WARN:  return "WRN";
            case LOGGER_LEVEL_INFO:  return "INF";
            case LOGGER_LEVEL_DEBUG: return "DBG";
            case LOGGER_LEVEL_TRACE: return "TRC";
            default:                 return "---";
        }
    }
    Stream*     _serial;
    LoggerLevel _level;
};

} // namespace logging
