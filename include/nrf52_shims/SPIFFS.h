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
    bool begin(bool formatOnFail = false) {
        if (InternalFS.begin()) return true;
        if (!formatOnFail) return false;
        // Match SPIFFS.begin(true) semantics: try to format and re-mount.
        // The append-loop bug we hit during T114 bring-up could leave the
        // partition in a state where lfs metadata refuses to mount; only
        // format-and-retry recovers without an external tool.
        InternalFS.format();
        return InternalFS.begin();
    }
    bool exists(const char* path) { return InternalFS.exists(path); }
    bool exists(const String& path) { return InternalFS.exists(path.c_str()); }

    Adafruit_LittleFS_Namespace::File open(const char* path,
                                           const char* mode = "r") {
        // Return as a prvalue so C++ copy elision (mandatory for prvalues
        // since C++17, and almost always applied by NRVO before that)
        // constructs the File directly in the caller's variable. Adafruit's
        // File class auto-closes in its destructor when _opened is true and
        // has no proper copy/move ctor — so a named local + `return f;`
        // makes the *temporary*'s destructor close the file before the
        // caller can use it, leaving the caller with a stale handle.
        const uint8_t flags =
            (mode && (mode[0] == 'w' || mode[0] == 'a'))
                ? Adafruit_LittleFS_Namespace::FILE_O_WRITE
                : Adafruit_LittleFS_Namespace::FILE_O_READ;
        return Adafruit_LittleFS_Namespace::File(path, flags, InternalFS);
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
