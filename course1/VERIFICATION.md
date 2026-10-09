# Verification — 8 October 2026

| Check | Observed result |
| --- | --- |
| HOST GCC build, -Wall -Werror, C99 | PASS |
| Eight supplied assessment tests | 8 passed, 0 failed; exit 0 |
| VERBOSE on/off without cleaning | PASS; array output correctly gated |
| COURSE1 off/on without cleaning | PASS; disabled main prints nothing |
| Memory movement | 82,225 source/destination/length combinations matched libc memmove |
| Independent conversion oracle | Correct strings and round trips for all bases 2–16, INT32_MIN, INT32_MAX, negative values, zero and positive values |
| Copy, reverse, fill, zero, allocation, stats | PASS; zero/odd/even lengths, allocation overflow, return pointers included |
| AddressSanitizer and UndefinedBehaviorSanitizer | PASS |
| LeakSanitizer | Not run successfully; environment blocks process scanning. Disabled in repeatable test runner. |
| MSP432 compile and link | PASS with Arm GNU Toolchain 13.2.Rel1 (GCC 13.2.1) |
| Target ELF | ELF32, ARM, EABI5, hard-float ABI |
| Hardware execution | Not performed; assessment tests ran on HOST |

ARM linked size: text 10,444 bytes; data 1,356 bytes; BSS 840 bytes.
The modern ARM linker emits expected nosys warnings for unavailable file I/O
syscalls (_close, _lseek, _read, _write). These are not compile failures; target
PRINTF is disabled. Target runtime/heap must be validated separately on hardware.
The exception-handler translation unit uses -mgeneral-regs-only to address a
modern-GCC floating-point register warning without disabling warnings.

Raw HOST, ARM build, and ARM ELF-header output is under verification/.
Generated executable/object files were cleaned before packaging. The toolchain
is not bundled; use GCC/Make for HOST and arm-none-eabi-gcc for MSP432.
