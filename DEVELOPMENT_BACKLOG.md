# Embedded teaching-method development

## Completed — 2026-11-20

- Reproduced and corrected macOS map-linker/sanitizer flag incompatibility.
- Fixed same-second configuration switching on older make without weakening warnings/tests.
- Added Linux/macOS HOST CI; kept ARM and hardware claims separate.

## Next

1. Preserve trace parity with the actual HOST my_memmove implementation and independent snapshot-copy oracle.
2. Test configuration-specific intermediate .i/.asm caching beyond full-build flag switches.
3. Run MSP432 compile/link only when the documented toolchain is available; hardware checks remain separate.
