# Development log

## 2026-11-20 — HOST build portability

Initial macOS test run failed at GNU map-linker syntax. After fixing that, the full suite exposed a real rapid COURSE1-switch stale-object failure on older make. Fixed both with platform-specific linker/no-PIE flags and a successful-build configuration marker plus forced compilation/linking on changes. No course algorithm, warning requirement or sanitizer was removed. Full HOST suite passed locally: eight supplied assessments, 82,225 memory-overlap comparisons, conversion/edge oracles and ASan/UBSan, plus rebuild switches without cleaning. Added read-only pinned-action Linux/macOS HOST CI and ignored the generated configuration marker. Hardware and ARM execution are not claimed.

Hosted validation follow-up: Linux passed, but the initial macOS job was cancelled before acquiring a runner because macos-14 is retired. Verified the official GitHub retirement notice (https://github.blog/changelog/2026-10-01-github-actions-macos-14-runner-image-retirement/), switched the standard runner to macos-15, updated the policy assertion and reran the full local suite before pushing the correction. No test or warning gate was removed.
