# Embedded Systems Coursework

**Hritika Adhikary · C · GCC · GNU Make · MSP432**

I am developing my embedded-software foundations through **Introduction to Embedded Systems Software and Development Environments**, University of Colorado Boulder on Coursera. This repository brings together my build-system coursework and the Course 1 final assessment, with source code, reproducible HOST tests and documented target-build results.

[Profile](https://github.com/hrix7) · [Biomedical portfolio](https://github.com/hrix7/Biomedical-Engineering-Portfolio) · [Official course starter](https://github.com/afosdick/ese-coursera-course1)

## Course work

| Coursework | Implementation and learning focus | Evidence |
| :--- | :--- | :--- |
| [Module 2 — Build system](assessments/m2/) | Platform-selectable Makefiles, source lists, dependency generation, preprocessing, assembly and linking | [Build notes](assessments/m2/README-assignment.md) · [Prior verification](assessments/m2/VERIFICATION.txt) |
| [Course 1 — Expanded build system and memory](course1/) | Pointer-based memory operations, allocation, statistics, signed integer/ASCII conversion in bases 2–16, configurable builds | [Source and commands](course1/README.md) · [Tests](course1/tests/) · [Verification](course1/VERIFICATION.md) |

**Status:** final-assessment implementation prepared; course completion, grading and certificate issuance are not yet recorded here.

## Run the final assessment

Requires GCC, GNU Make and Python 3 on a Linux development environment.

```sh
cd course1
make build PLATFORM=HOST COURSE1=1 VERBOSE=1
./src/course1.out
make test
```

The HOST suite was rerun on **9 October 2026**: all eight supplied tests passed, together with 82,225 memory-overlap cases, integer-conversion edge cases and AddressSanitizer/UndefinedBehaviorSanitizer checks. The runner also checks configuration changes without cleaning.

MSP432 cross-compilation requires `arm-none-eabi-gcc`. The [8 October verification record](course1/VERIFICATION.md) documents the earlier ARM build. Physical-device execution has not been performed.

## What this work covers

- **Build tooling:** HOST/MSP432 selection, dependency tracking and build configuration changes.
- **Memory:** overlap-safe movement, copy, fill, zero, reverse and checked allocation.
- **Data representation:** signed conversions across bases 2–16, including integer limits.
- **Verification:** supplied assessment tests plus independent edge-case tests and sanitizers.

## Authorship and attribution

Coursework portfolio: **Hritika Adhikary**. Course context: **University of Colorado Boulder / Coursera**. Instructor and original starter author: **Alex Fosdick**.

New implementations, tests and integration were developed with **ChatGPT/Codex assistance**. Supplied tests and platform support remain attributed to their original authors. See [ATTRIBUTION.md](ATTRIBUTION.md) for scope and licensing. The code is presented as a learning portfolio; it is not independently authored third-party course material or a medical-device product.
