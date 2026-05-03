# Copyright (C) 2026 KJ7NYE
#
# Post-build script: convert firmware.hex -> firmware.uf2 for nRF52840 boards
# using Microsoft's uf2conv.py (vendored alongside in tools/). Produces the
# UF2 file alongside the existing firmware.zip in .pio/build/<env>/, ready for
# drag-drop onto the device's UF2 mass-storage bootloader.
#
# Family ID 0xADA52840 = "Adafruit nRF52840" — used by the Adafruit nRF52
# bootloader and most off-the-shelf nRF52840 boards (including Heltec T114).

import os
import subprocess
import sys

Import("env")

PROJECT_DIR = env["PROJECT_DIR"]
UF2CONV     = os.path.join(PROJECT_DIR, "tools", "uf2conv.py")
FAMILY      = "0xADA52840"

def make_uf2(source, target, env):
    build_dir = env.subst("$BUILD_DIR")
    hex_path  = os.path.join(build_dir, "firmware.hex")
    uf2_path  = os.path.join(build_dir, "firmware.uf2")
    if not os.path.exists(hex_path):
        print(f"[uf2] {hex_path} not found, skipping conversion")
        return
    print(f"[uf2] converting firmware.hex -> firmware.uf2 (family {FAMILY})")
    result = subprocess.run(
        [sys.executable, UF2CONV, hex_path, "-c", "-f", FAMILY, "-o", uf2_path],
        capture_output=True, text=True,
    )
    if result.returncode != 0:
        print(result.stdout, end="")
        print(result.stderr, end="", file=sys.stderr)
        raise SystemExit(f"[uf2] uf2conv.py failed (exit {result.returncode})")
    print(f"[uf2] wrote {uf2_path} ({os.path.getsize(uf2_path)} bytes)")

env.AddPostAction("$BUILD_DIR/firmware.hex", make_uf2)
