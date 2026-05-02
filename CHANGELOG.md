# LoRanger APRS Tracker — Changelog

Running log of changes in this fork ([KJ7NYE/LoRanger_APRS_Tracker](https://github.com/KJ7NYE/LoRanger_APRS_Tracker))
on top of upstream [richonguzman/LoRa_APRS_Tracker](https://github.com/richonguzman/LoRa_APRS_Tracker).

Fork divergence point: upstream commit [`bfd531a`](https://github.com/richonguzman/LoRa_APRS_Tracker/commit/bfd531a) — *"winlink challenge fisher-yates update"* (2026-04-23).

Newest entries first. Format: `YYYY-MM-DD — short title (commit)` followed by a brief description.

---

## 2026-05-02 — `tracker_conf` standard settings for event support ([`032df10`](../../commit/032df10))

Updated the default [data/tracker_conf.json](data/tracker_conf.json) to event-friendly defaults:

- `other.sendCommentAfterXBeacons`: **10 → 4**
- `other.path`: **`WIDE1-1` → `WIDE2-2`**
- `lora[0]` (EU 433.775 MHz): **SF12/125 kHz → SF8/62.5 kHz**

Goal: more frequent comments and broader digi reach during event use, with a faster RF profile on the EU channel.

## 2026-05-02 — Tune Car SmartBeacon `minDeltaBeacon` 12s → 10s ([`9bdebcc`](../../commit/9bdebcc))

[src/smartbeacon_utils.cpp](src/smartbeacon_utils.cpp) — shortens the minimum spacing
between beacons in the Car profile from 12s to 10s.

## 2026-05-02 — Add serial setup CLI for USB config without WiFi AP ([`be37b9f`](../../commit/be37b9f))

New USB-serial command-line interface (115200 baud) for first-flash provisioning,
scripted bulk configuration, or quick edits while tethered — no need to bring up
the `LoRaTracker-AP` web UI.

- New: [include/serial_setup.h](include/serial_setup.h), [src/serial_setup.cpp](src/serial_setup.cpp)
- Wired into [src/LoRa_APRS_Tracker.cpp](src/LoRa_APRS_Tracker.cpp) and [src/configuration.cpp](src/configuration.cpp)
- Logger is paused (errors only) while in setup mode
- Full reference: [SERIAL_SETUP.md](SERIAL_SETUP.md)

## 2026-05-01 — 30-second startup AP window for web config ([`87be561`](../../commit/87be561))

[src/wifi_utils.cpp](src/wifi_utils.cpp) — every boot now opens `LoRaTracker-AP`
for 30 seconds so the web config is reachable without needing `wifiAP.active` or
`NOCALL-7`. If a client connects during the window, the existing 2-minute idle
timeout takes over so config sessions aren't cut off.

## 2026-04-30 — Tune Car SmartBeacon profile ([`4ec4b9f`](../../commit/4ec4b9f))

[src/smartbeacon_utils.cpp](src/smartbeacon_utils.cpp):

- `fastRate`: **60s → 10s**
- `fastSpeed`: **70 → 110 km/h**

Denser beaconing at highway speeds with a higher kick-in threshold.

## 2026-04-30 — Add LoRanger V1 board variant ([`1898fa2`](../../commit/1898fa2))

Initial fork commit. Adds the LoRanger V1 hardware variant — custom ESP32-S3
+ 1 W SX1268 + ATGM336H GPS tracker with hardwired LDO rails.

- New: [variants/LoRanger_V1/board_pinout.h](variants/LoRanger_V1/board_pinout.h),
  [variants/LoRanger_V1/platformio.ini](variants/LoRanger_V1/platformio.ini)
- Touched: [include/configuration.h](include/configuration.h),
  [src/battery_utils.cpp](src/battery_utils.cpp),
  [src/configuration.cpp](src/configuration.cpp),
  [src/lora_utils.cpp](src/lora_utils.cpp)
- Some upstream `LIGHTTRACKER_PLUS_1_0` `#ifdef` branches were broadened to also
  match `LORANGER_V1`; others were intentionally left alone.

---

## How to update this file

When you add a fork commit, prepend a new section above using:

```
## YYYY-MM-DD — Short title ([`<short-hash>`](../../commit/<short-hash>))

One- or two-paragraph description: what changed, which files, and why.
```

The `../../commit/<hash>` link resolves on GitHub from any branch view of this file.
