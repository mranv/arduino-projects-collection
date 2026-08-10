---
name: Pull Request
about: Suggest a change to the collection
title: 'feat/<project>: '
labels: ""
body:
  - type: textarea
    attributes:
      label: Summary
      description: What does this PR change and why? Keep it short.
    validations:
      required: true
  - type: input
    id: project
    attributes:
      label: Project affected
      description: Folder name (no catalog number), e.g. `1.8TFT Display`
      placeholder: `<Project Name>`
    validations:
      required: false
  - type: textarea
    id: testing
    attributes:
      label: Testing
      description: How did you verify this? (flashed the sketch, checked the wiring, etc.)
    validations:
      required: false
  - type: checkboxes
    id: checklist
    attributes:
      label: Checklist
      options:
        - label: "No committed credentials (see SECURITY.md)"
          required: true
        - label: "Folder name has no leading catalog number and is unique"
          required: true
        - label: "Commits are focused / one project per commit"
          required: false
---
