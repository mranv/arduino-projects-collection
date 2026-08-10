# Security Policy

Curated by **Anubhav Gain** — *Security Engineer | Rust Developer | Cloud Infrastructure | Open Source Contributor* ([@mranv](https://github.com/mranv), [mranv.github.io](https://mranv.github.io)).

This repository is an educational reference collection of Arduino/IoT sketches contributed over many years. Security is taken seriously — see how to report issues and what we've already audited.

---

## 🛡️ Reporting a vulnerability in this collection

- **Do not open a public GitHub Issue for security-sensitive reports.**
- Open a **private** [GitHub Security Advisory](https://github.com/mranv/arduino-projects-collection/security/advisories) (preferred), **or** email `iamanubhavgain@gmail.com` with the word **SECURITY** in the subject.
- Include, where possible: the affected file/project path, a short description, the expected vs. actual behaviour, and steps to reproduce.
- You will receive an acknowledgement within **48 hours** and, for verified issues with real impact, a fix or mitigation within a best-effort window.

## Scope

In scope: anything in this repository that could compromise a builder's device, network, or credentials — e.g. a sketch that ships a live Wi-Fi password, a hard-coded API token, or a circuit that creates an unsafe condition. Out of scope: purely cosmetic issues and bugs in the upstream Arduino tooling.

## Safe‑handling commitment

No real, non‑demo credentials belonging to third parties are intentionally stored here. If one is found, it will be listed below and treated as compromised.

---

## 🔍 Credential audit (performed during curation)

While reorganising the bundle, a static keyword scan was run over every sketch
and document (results were **redacted** — only file paths and keywords, never
secret values, were inspected). Summary:

| Keyword      | Files mentioning it |
|--------------|--------------------:|
| `wifi`       | 50                  |
| `password`   | 45                  |
| `ssid`       | 29                  |
| `token`      | 6                   |
| `api_key`    | 4                   |
| `apikey`     | 2                   |
| `secret`     | 2                   |

**Finding:** **23 sketches** reference **both** Wi-Fi and a credential keyword
(`ssid`/`password`/`token`/...) — i.e. they are very likely to embed a
hard-coded Wi-Fi **SSID + password** pair. A further handful embed IoT
service **tokens / API keys** (Blynk, Firebase, Philips Hue demos).

### What this means for you

1. These values come from the original educational bundle and are almost
   always **placeholder or demo** credentials — but treat **any** of them as
   **compromised** if you copy the code into a shared or templated project.
2. **Never** leave a real password or API key in a sketch. Move credentials
   out of source control:
   - Arduino: `#include "secrets.h"` (and add `secrets.h` to `.gitignore`).
   - ESP-IDF: environment variables / `menuconfig`.
3. If you recognise your own key here, **rotate it immediately** and open a
   private report so the offending line can be scrubbed.

### For contributors

When adding or fixing a sketch, remove any live credentials and replace them
with placeholders (`"YOUR_SSID"`, `"YOUR_PASSWORD"`) plus a short note pointing
to the secrets-management approach above.

---

## Responsible disclosure

We follow **Coordinated/Responsible Disclosure**: report privately first, await a
fix, then disclose publicly only once a remediation is available (or after
reasonable good‑faith effort is made to acknowledge and address the report).
