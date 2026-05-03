/*
 * Minimal <SPIFFS.h> shim for nRF52 builds.
 *
 * Maps the SPIFFS-style API used across the codebase (begin/exists/open/remove)
 * onto Adafruit's InternalFileSystem (LittleFS on internal flash). Resolved
 * before the upstream ESP32 SPIFFS header because nrf52_common adds
 * `-I include/nrf52_shims` to build_flags.
 *
 * Only the call patterns actually used in this codebase are supported — this
 * is not a general-purpose SPIFFS replacement.
 */
#pragma once

#include <Arduino.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

// Match ESP32's SPIFFS API where FILE_APPEND is a "a" string mode passed to
// open(). Don't redefine if the BSP already exposed it.
#ifndef FILE_APPEND
#define FILE_APPEND "a"
#endif

class _SpiffsCompat {
public:
    bool begin(bool /*formatOnFail*/ = false) {
        return InternalFS.begin();
    }
    bool exists(const char* path) { return InternalFS.exists(path); }
    bool exists(const String& path) { return InternalFS.exists(path.c_str()); }

    Adafruit_LittleFS_Namespace::File open(const char* path,
                                           const char* mode = "r") {
        Adafruit_LittleFS_Namespace::File f(InternalFS);
        if (mode && (mode[0] == 'w' || mode[0] == 'a')) {
            f.open(path, Adafruit_LittleFS_Namespace::FILE_O_WRITE);
        } else {
            f.open(path, Adafruit_LittleFS_Namespace::FILE_O_READ);
        }
        return f;
    }
    Adafruit_LittleFS_Namespace::File open(const String& path,
                                           const char* mode = "r") {
        return open(path.c_str(), mode);
    }

    bool remove(const char* path) { return InternalFS.remove(path); }
    bool remove(const String& path) { return InternalFS.remove(path.c_str()); }
};

// Single shared instance via Meyers singleton — header-only, no .cpp needed.
inline _SpiffsCompat& _spiffs_compat_instance() {
    static _SpiffsCompat inst;
    return inst;
}
#define SPIFFS (_spiffs_compat_instance())

// File type alias so existing `File f = SPIFFS.open(...)` still works.
typedef Adafruit_LittleFS_Namespace::File File;
