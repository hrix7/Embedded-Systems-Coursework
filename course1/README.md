# Course 1 Final Assessment: Expanded Build System and Memory

Prepared for Hritika Adhikary, 8 October 2026.

## Build and run

From this `course1` directory on a Linux course VM with GCC and GNU Make:

```sh
make build PLATFORM=HOST COURSE1=1 VERBOSE=1
./src/course1.out
```

Expected result: `PASSED: 8 / 8`, `FAILED: 0 / 8`, exit status 0.

```sh
make build PLATFORM=HOST COURSE1=1 VERBOSE=0
./src/course1.out
make test
```

`VERBOSE=0` suppresses array/debug printing; test names and the summary remain.
`COURSE1=0` makes main do nothing and return success. Defaults: HOST, COURSE1=1,
VERBOSE=0. Configuration changes trigger recompilation without requiring clean.
`make test` requires Python 3 and GCC with AddressSanitizer/UBSan. LeakSanitizer
is disabled because this execution environment does not permit its process scan.

For the target, put the GNU Arm Embedded toolchain on PATH, then:

```sh
make clean
make build PLATFORM=MSP432 COURSE1=1 VERBOSE=1
```

This creates an ARM executable, not a program runnable on the host. The target
uses the supplied Cortex-M4 startup files, CMSIS headers, linker script and
`nosys.specs`. Target hardware execution is outside this assignment's HOST test
workflow and has not been verified. `nosys.specs` provides bare-metal syscall
stubs; hardware heap/runtime behavior needs separate validation before deployment.

Additional inherited build targets: `compile-all`, `main.i`, `main.asm`, `main.o`,
`course1.asm`, and `clean`. Output executable and map: `src/course1.out` and
`src/course1.map`. `make clean` removes generated build files.

## Files and requirements

| File | Purpose |
| --- | --- |
| src/main.c | Calls course1 only under COURSE1; propagates failure to host exit status. |
| src/stats.c | Descending sort, median, mean, minimum, maximum, PRINTF output; VERBOSE array printing. |
| src/memory.c | Seven required memory/allocation functions; prior Module 2 helpers retained. |
| src/data.c | Signed integer/ASCII conversion for bases 2–16 without string libraries. |
| src/course1.c | Supplied eight tests, each invoked once. |
| include/common | Public prototypes, platform printing macro and conversion constants. |
| src/Makefile, src/sources.mk | Extended recovered Module 2 build system. |
| tests | Independent edge-case and build-switch verification. |

## Implementation choices

- All new memory and conversion operations use pointer arithmetic, not indexing.
- memmove scans for a destination within the source span using pointer equality,
  avoiding relational comparison between pointers to separate allocations.
- memcopy copies forward; overlapping arguments are outside its contract.
- memset and memzero independently fill memory; neither reuses set_all/clear_all.
- reserve_words checks multiplication overflow and returns NULL for zero length.
- itoa writes uppercase A–F, a minus sign for negatives in every base, and a NUL.
  Its return value includes the sign and NUL. Allocate 34 bytes for the worst case.
- atoi accepts a byte bound that includes the sign and optionally the NUL. It
  stops at NUL and accepts both letter cases. Invalid digits/bases and overflow
  return 0. Both functions safely handle INT32_MIN.
- Statistics use integer truncation; median sorts its input in place.

## Starter differences and provenance

The recovered `C1M2-Adhikary.zip` supplied the build system, complete upstream Git
history, target support files and official final tests. Its statistics source was
an unimplemented starter; the implementation in course1 was completed here.
Module 2 materials are available under ../assessments/m2.

The supplied course1.c tests were retained with two integration corrections:
`free_words` casts now use int32_t*, matching the required prototype, and
course1 returns int8_t, matching the written assignment, instead of the starter's
void return. The unmodified starter is available in the official upstream repository.

Official starter: https://github.com/afosdick/ese-coursera-course1
Original copyright notices are retained. No third-party solution repository was
used. New implementations, tests and integration were produced with ChatGPT/Codex
assistance. The original submission archive retains its Git history; this repository is a curated export.

The assignment requires your own work. Review the code and course rules on AI
assistance before using it as a submission; do not represent generated work as
independently authored. This package has not been uploaded to Coursera.

## Verification

See [VERIFICATION.md](VERIFICATION.md) for the original checks. The HOST test suite was rerun successfully on 9 October 2026 when this repository was prepared.
