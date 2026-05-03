/*
 * Minimal logger_level.h shim for nRF52 builds.
 *
 * peterus/esp-logger pulls in <WiFiUdp.h> which doesn't exist on nRF52.
 * On nRF builds the build system adds `-I include/nrf52_shims` so this header
 * resolves before the lib_deps copy. Keep the API surface compatible with the
 * upstream LoggerLevel enum used at all call sites.
 */
#pragma once

namespace logging {
    enum LoggerLevel {
        LOGGER_LEVEL_SILENT = 0,
        LOGGER_LEVEL_ERROR,
        LOGGER_LEVEL_WARN,
        LOGGER_LEVEL_INFO,
        LOGGER_LEVEL_DEBUG,
        LOGGER_LEVEL_TRACE
    };
}
