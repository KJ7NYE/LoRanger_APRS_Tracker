# LoRanger APRS Tracker — KJ7NYE Fork

> **Fork notice.** This is a fork of [richonguzman/LoRa_APRS_Tracker](https://github.com/richonguzman/LoRa_APRS_Tracker),
> maintained at [KJ7NYE/LoRanger_APRS_Tracker](https://github.com/KJ7NYE/LoRanger_APRS_Tracker). The upstream
> project is the canonical CA2RXU LoRa APRS Tracker firmware — full credit to Ricardo Guzman (CA2RXU) and the
> upstream contributors. Relevant excerpts from the upstream README are preserved below.
>
> This fork is tuned for **tactical event support** — search and rescue, ultra-marathon timing, jetboat racing,
> and other coordinated multi-tracker deployments where dense, fast-cadence position reporting matters — and
> adds firmware support for the [KJ7NYE LoRanger hardware](https://github.com/KJ7NYE/LoRanger).
>
> **Upstreaming is the goal.** Where changes here are useful beyond event-support contexts, the intent is to
> submit them back to CA2RXU. If you adopt something from this fork that belongs in the base project, please
> help push it upstream.

## What's different in this fork

This fork exists for two reasons: to support the [KJ7NYE LoRanger hardware](https://github.com/KJ7NYE/LoRanger),
and to make the firmware better suited for licensed-amateur tactical event support in the US.

- **LoRanger hardware support.** Firmware variant for an open-source ESP32-S3 + 1 W SX1268 + GPS tracker built
  for canyon and beyond-cellular field deployments. CC-BY-SA-4.0.

- **Defaults tuned for US compliance.** LoRa modulation defaults are set to comply with US licensed-amateur
  regulations on 70 cm. Operators outside the US should verify settings against their local rules before
  transmitting.

- **Tuned for dense multi-tracker channels.** Beacon cadence, comment-ID interval, SmartBeacon profile, and
  APRS path defaults are retuned for coordinated deployments where 15–20 trackers share a channel during an
  event window — search and rescue, ultra-marathon timing, jetboat racing, and similar.

- **Configuration ergonomics for field deployment.** USB serial setup CLI for scripted/tethered
  configuration, persistent digipeater state across reboots, and a short boot-time AP window that makes the
  web UI reachable without relying on display. Initial provisioning of a fresh device still routes through
  the web UI.

> Network compatibility note: every device on a LoRa APRS network must run identical SF/BW/CR. If you flash
> this fork onto a tracker that needs to talk to a fleet running stock CA2RXU defaults, you must either
> change the receivers or change this tracker's settings to match.

For per-commit specifics — file paths, exact values, divergence point from upstream — see
[CHANGELOG.md](https://github.com/KJ7NYE/LoRanger_APRS_Tracker/blob/main/CHANGELOG.md).

---

# Upstream Project — CA2RXU LoRa APRS Tracker/Station

This firmware is for using ESP32-based boards with LoRa modules and GPS to live in the APRS world.

> **NOTE:** To use Tx/Rx capabilities of this tracker you should also have a Tx/Rx
> [LoRa iGate](https://github.com/richonguzman/LoRa_APRS_iGate) nearby.

## Support the upstream project

If this fork is useful to you, please also consider supporting Ricardo (CA2RXU), whose work this is built on:

[<img src="https://github.com/richonguzman/LoRa_APRS_Tracker/blob/main/images/github-sponsors.png">](https://github.com/sponsors/richonguzman) [<img src="https://github.com/richonguzman/LoRa_APRS_Tracker/blob/main/images/paypalme.png">](http://paypal.me/richonguzman)

## Upstream feature highlights

- Tracker with on-device menu (read/write/delete messages with I2C keyboard or phone, weather report, recent stations, eco/brightness controls)
- Bluetooth TNC (Android + APRSDroid, iPhone + APRS.fi) — BLE or BT Classic, KISS or TNC2
- Three configurable LoRa APRS region presets (EU/PL/UK)
- LED + buzzer notifications for Tx, message Rx, and boot events
- BME280 / BMP280 / BME680 weather telemetry
- Winlink mail through APRSLink
- Encoded GPS beacons for shorter on-air time
- Battery monitor with low-voltage sleep protection

## Upstream documentation (Wiki — English / Español)

- [FAQ — GPS, Bluetooth, Winlink, BME280, etc.](https://github.com/richonguzman/LoRa_APRS_Tracker/wiki/00.-FAQ-(frequently-asked-questions))
- [Supported boards and buying links](https://github.com/richonguzman/LoRa_APRS_Tracker/wiki/1000.-Supported-Boards-and-Buying-Links)
- [Installation guide](https://github.com/richonguzman/LoRa_APRS_Tracker/wiki/01.-Installation-Guide-%23-Guia-de-Instalacion)
- [Tracker configuration reference](https://github.com/richonguzman/LoRa_APRS_Tracker/wiki/02.-Tracker-Configuration--%23--Configuracion-del-Tracker)
- [Upload firmware and filesystem](https://github.com/richonguzman/LoRa_APRS_Tracker/wiki/03.-Upload-Firmware-and-Filesystem-%23-Subir-Firmware-y-sistema-de-archivos)
- [On-device menu guide](https://github.com/richonguzman/LoRa_APRS_Tracker/wiki/04.-Menu-Guide-%23-Guía-del-menú)

For upstream version history, see the [upstream repository](https://github.com/richonguzman/LoRa_APRS_Tracker).

## License

GPL-3.0, inherited from the upstream project. All modifications in this fork are released under the same
license. See [LICENSE](https://github.com/KJ7NYE/LoRanger_APRS_Tracker/blob/main/LICENSE) for the full terms.

## This code was based on the work of:

- [Ricardo CA2RXU — LoRa APRS Tracker (direct upstream of this fork)](https://github.com/richonguzman/LoRa_APRS_Tracker)
- [Serge ON4AA — base91 byte-saving / encoding](https://github.com/aprs434/lora.tracker)
- [Peter OE5BPA — LoRa APRS Tracker](https://github.com/lora-aprs/LoRa_APRS_Tracker)
- [Manfred DC2MH (Mane76) — multiple-callsigns and processor-speed mods](https://github.com/Mane76/LoRa_APRS_Tracker)
- [Thomas DL9SAU — KISS / TNC2 lib](https://github.com/dl9sau/TTGO-T-Beam-LoRa-APRS)

---

*Original work: 73! — CA2RXU, Valparaíso, Chile*
*Fork maintained by: KJ7NYE, Idaho, US*
