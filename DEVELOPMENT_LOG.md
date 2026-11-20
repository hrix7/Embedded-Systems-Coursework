# Development log

## 2026-11-20 — HOST build portability

Initial macOS test run failed at GNU map-linker syntax. After fixing that, the full suite exposed a real rapid COURSE1-switch stale-object failure on older make. Fixed both with platform-specific linker/no-PIE flags and a successful-build configuration marker plus forced compilation/linking on changes. No course algorithm, warning requirement or sanitizer was removed. Full HOST suite passed locally: eight supplied assessments, 82,225 memory-overlap comparisons, conversion/edge oracles and ASan/UBSan, plus rebuild switches without cleaning. Added read-only pinned-action Linux/macOS HOST CI and ignored the generated configuration marker. Hardware and ARM execution are not claimed.
