# Contributing

First off, thank you for helping this catalogue stay accurate and useful! 🎉

Curated by **Anubhav Gain** — *Security Engineer | Rust Developer | Cloud
Infrastructure | Open Source Contributor* ([@mranv](https://github.com/mranv),
[mranv.github.io](https://mranv.github.io)).

---

## How to add / fix a project

1. **Fork** the repository and clone your fork:
   ```bash
   git clone https://github.com/<your-username>/arduino-projects-collection.git
   cd arduino-projects-collection
   ```
2. Create a branch:
   ```bash
   git clone https://github.com/<your-username>/arduino-projects-collection.git
   cd arduino-projects-collection
   git checkout -b fix/<brief-description>
   ```
3. Make your change inside the relevant project folder — fixing a schematic
   path, correcting a pin mapping, or adding a working sketch for a different
   board variant.
4. Commit with a clear, focused message (see *Commit style* below).
5. Push and open a Pull Request against `master`.

## Commit style

- Keep commits **micro** and focused on a single project or concern.
- Prefer the imperative mood:
  - `1.8TFT Display sketch`
  - `Fix pin mapping in HC-SR04 ultrasonic sketch`
  - `Add ESP32 variant for Bluetooth Car`
- Reference the project by name, e.g. `Add <Project Name>`.

## Project layout

See the [repository structure](README.md#repository-structure). Each project is
self-contained under its own folder. Add new projects as a new folder, or
improve an existing one in place.

## Folder naming

- Folder names match each project's title — **no leading catalog numbers**.
- Each folder name must be unique. If two genuinely-different projects share a
  title, disambiguate *descriptively* (e.g. `Flame Sensor (LCD Display)` vs
  `Flame Sensor (Sprinkler Relay)`).
- Build artifacts, dependency checkouts, OS caches and `secrets.h` files are
  ignored — see `.gitignore`.

## Credentials & security

**Never commit credentials.** Move Wi‑Fi passwords, API keys and tokens into a
`secrets.h` file (or env) that is listed in `.gitignore`. See
[`SECURITY.md`](.github/SECURITY.md) for the full policy and the results of the
existing credential audit on this collection.

## Code of conduct

Be respectful and constructive. These are educational reference projects; keep
changes beginner-friendly and well-commented.

## License

By contributing, you agree that your contributions are licensed under the
repository's MIT License (see [LICENSE](./LICENSE)).

---

> Curated by **Anubhav Gain** — [GitHub @mranv](https://github.com/mranv) ·
> [mranv.github.io](https://mranv.github.io) ·
> [Sponsor on GitHub Sponsors](https://github.com/sponsors/mranv)
