# Embedded C Build & Memory System

**Hritika Adhikary · C · GCC · GNU Make · MSP432**

I built a configurable C project that runs on a Linux host and cross-compiles for the MSP432. It combines a reusable build system with memory utilities, integer conversion functions and statistical operations.

[Source code](course1/src/) · [Tests](course1/tests/) · [Verification](course1/VERIFICATION.md) · [Biomedical portfolio](https://github.com/hrix7/Biomedical-Engineering-Portfolio#certifications)

## Features

- **Dual-platform builds:** select HOST or MSP432 with GNU Make.
- **Build automation:** dependency tracking, preprocessing, assembly, compilation and linking.
- **Memory utilities:** overlap-safe movement, copy, fill, zero, reverse and checked allocation.
- **Data conversion:** signed integer/ASCII conversion across bases 2–16.
- **Statistics:** descending sort, minimum, maximum, mean and median.
- **Configurable output:** switch verbose output and application execution without manually cleaning the build.

## Completed work

I integrated the C application with the build system, implemented the memory and conversion functions, and added independent edge-case tests with Codex assistance.

The HOST test suite passed on **9 October 2026**: eight supplied tests, **82,225 memory-overlap cases**, signed conversion limits, allocation and statistics checks, plus AddressSanitizer/UndefinedBehaviorSanitizer checks. The earlier MSP432 compile-and-link result is recorded in [VERIFICATION.md](course1/VERIFICATION.md). Physical hardware execution remains pending.

## Build and run

Requires GCC, GNU Make and Python 3.

```sh
cd course1
make build PLATFORM=HOST COURSE1=1 VERBOSE=1
./src/course1.out
make test
```

For an MSP432 build, install the GNU Arm Embedded toolchain, then run:

```sh
make clean
make build PLATFORM=MSP432 COURSE1=1
```

## Project structure

| Location | Contents |
| :--- | :--- |
| [course1/src](course1/src/) | C implementation and Makefiles |
| [course1/include/common](course1/include/common/) | Public interfaces and platform definitions |
| [course1/tests](course1/tests/) | Edge-case tests and repeatable verification |
| [assessments/m2](assessments/m2/) | Earlier build-system implementation |

## Related certification

**Introduction to Embedded Systems Software and Development Environments**  
University of Colorado Boulder · Coursera  
**Credential:** certificate verification pending.

## Author & attribution

**Hritika Adhikary** · Project developed through University of Colorado Boulder / Coursera training.

Original starter: Alex Fosdick / University of Colorado. Implementation, tests and integration include ChatGPT/Codex assistance. Original source and platform-support notices are retained; see [ATTRIBUTION.md](ATTRIBUTION.md).
