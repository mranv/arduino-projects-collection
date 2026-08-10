---
name: Bug report
about: Something is broken or incorrect in a project
title: 'bug/<project>:'
labels: bug
body:
  - type: input
    attributes:
      label: Project folder
      description: Folder name (no catalog number), e.g. `HC-SR04 Ultrasonic`
      placeholder: `<Project Name>`
    validations:
      required: true
  - type: textarea
    attributes:
      label: What is wrong?
      description: The incorrect behaviour / wiring mismatch / compile error.
    validations:
      required: true
  - type: textarea
    attributes:
      label: Expected behaviour
    validations:
      required: false
  - type: textarea
    id: repro
    attributes:
      label: Steps to reproduce
    validations:
      required: false
  - type: textarea
    attributes:
      label: Suggested fix
      description: Pin correction, file relocation, typo fix, etc.
    validations:
      required: false
  - type: checkboxes
    id: leak
    attributes:
      label: Does this involve credentials?
      options:
        - label: "Yes — this file likely exposes a secret (report privately per SECURITY.md instead)"
          required: false
  - type: input
    attributes:
      label: Your environment
      description: Board / IDE / OS, e.g. `ESP32 @ Arduino IDE 2 / Windows`
      placeholder: e.g. ESP32 @ Arduino IDE 2 / Windows
    validations:
      required: false
---
