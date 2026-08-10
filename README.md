# Arduino, IoT & Robotics Projects Collection

A curated catalogue of **494 Arduino, IoT and robotics projects** — each with
ready-to-flash source code (`.ino` / `.pde` sketches) and circuit schematics /
wiring diagrams.

This is a reference portfolio: every project is self-contained and browsable by
name. Open a sketch in the Arduino IDE, wire the schematic, and build along.
🛠️

> The original *"500+ Arduino Projects"* bundle was de-duplicated (39
> byte-identical duplicate folders were merged) and renumbered cleanly, so every
> project name is unique.

---

## Table of contents

- [Repository structure](#repository-structure)
- [Project index](#project-index)
- [Getting started](#getting-started)
- [Project layout (per project)](#project-layout-per-project)
- [Notes & conventions](#notes--conventions)
- [Security](#security)
- [Contributing](#contributing)
- [License](#license)

---

## Repository structure

```
├─ README.md                # this file
├─ LICENSE                  # MIT
├─ .gitignore
├─ .gitattributes
├─ CONTRIBUTING.md
├─ CODEOWNERS
├─ CODE_OF_CONDUCT.md
├─ PROJECTS.md             # full 494-project index / catalog
├─ .github/
│  ├─ FUNDING.yml          # GitHub Sponsors (Anubhav Gain / mranv)
│  ├─ SECURITY.md          # vulnerability policy + credential audit
│  ├─ FUNDING.md
│  ├─ ISSUE_TEMPLATE/
│  │  ├─ bug_report.md
│  │  └─ feature_request.md
│  └─ PULL_REQUEST_TEMPLATE.md
└─ <Project Name>/          # one folder per project
   ├─ Code/              # Arduino sketches (*.ino / *.pde)
   ├─ Schematics/        # circuit diagrams (images / PDFs)
   └─ ...other assets/
```

Projects are kept in flat, name-based folders. Each folder is independent and
self-contained.

## Project index

Full catalog 👉 **[PROJECTS.md](./PROJECTS.md)**

Here is a small sample of what is inside:

| Project | Sketches | Schematic |
|---------|---------:|:---------:|
| 1.8TFT Display | 2 | — |
| 3 LED | 1 | ✅ |
| 17Channel_LED_Chaser | 1 | ✅ |
| Arduino Alter car | 1 | — |
| Automatic_Fire_Fighting_Robot | 1 | ✅ |
| Counter_4Digit_TM1637_Eeprom | 1 | ✅ |
| Intruder Alert using PIR Sensor | 0 | ✅ |
| PIR Motion | 1 | ✅ |
| Stopwatch_LCD_Display | 1 | ✅ |
| YL-69_HL-69 Soil Moisture | 1 | ✅ |

> The complete, up-to-date list of all **494** projects lives in
> [PROJECTS.md](./PROJECTS.md).

## Getting started

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) (or [PlatformIO](https://platformio.org/))
- The appropriate board package for your hardware (e.g. *ESP32*, *ESP8266*, *Arduino SAMD*).
- Jumper wires, a breadboard, and the components listed in each project's schematic.

### Flashing a sketch

1. Open the `.ino` / `.pde` file in the Arduino IDE.
2. Select your board and COM port (`Tools` → `Board` / `Port`).
3. Click **Upload**.
4. Refer to the image under `Schematics/` / `Diagrams/` for wiring.

### Browsing offline

The whole repository fits in a few hundred MB and can be cloned as a single
bundle for offline reference:

```bash
git clone https://github.com/mranv/arduino-projects-collection.git
```

## Project layout (per project)

A typical project folder looks like:

```
<Project Name>/
├─ Code/
│  └─ <SketchName>/
│     └─ <SketchName>.ino
├─ Schematics/
│  └─ <Project>.png
└─ <optional assets>
```

Some projects additionally ship `Diagrams/`, `.pdf` wiring notes, `.hex`
firmware dumps, library `.zip` archives, or App Inventor `.aia` files — all
preserved as-is.

## Notes & conventions

- Folder names match each project's title (no leading numbers); duplicates from
  the source bundle were de-duplicated (see *Project index* above).
- Build artifacts, dependency checkouts and OS caches are ignored (see
  `.gitignore`). Pull board packages and libraries from their originals.
- Firmware `.hex` dumps, `.aia` App Inventor projects and `.apk` binaries are
  treated as **source assets** for these reference projects and are committed.

## Security

Curated by **Anubhav Gain** — *Security Engineer | Rust Developer | Cloud
Infrastructure | Open Source Contributor* ([@mranv](https://github.com/mranv),
[mranv.github.io](https://mranv.github.io)).

**Report vulnerabilities privately** — open a [private GitHub Security
Advisory](https://github.com/mranv/arduino-projects-collection/security/advisories)
or email `iamanubhavgain@gmail.com` (subject: **SECURITY**).

A static scan during curation found **23 sketches that likely embed Wi-Fi
credentials** (SSID + password) and several more embedding IoT service tokens
(Blynk / Firebase / Hue). These are usually **demo/placeholder** values — but
treat any key found here as **compromised** if you reuse the code. Move real
credentials out of source via a `secrets.h` file (gitignored) or environment
variables. See [`.github/SECURITY.md`](./.github/SECURITY.md) for the full
credential policy and audit breakdown.

## Contributing

See [CONTRIBUTING.md](./CONTRIBUTING.md). In short: file-level fixes, wiring
corrections and additional board variants are very welcome.

## License

The repository as a whole is released under the **MIT License** (see
[LICENSE](./LICENSE)). Individual projects may carry their own license in a
`LICENSE` file at their folder root — when present, that file governs the
contents of that folder; otherwise the top-level MIT license applies.

---

> Curated and maintained by **Anubhav Gain** — *Security Engineer | Rust Developer | Cloud Infrastructure | Open Source Contributor* ·
> [GitHub @mranv](https://github.com/mranv) · [mranv.github.io](https://mranv.github.io) · [@AnubhavGain](https://twitter.com/AnubhavGain) ·
> [☕ Sponsor on GitHub Sponsors](https://github.com/sponsors/mranv)
