# Implementation log

## 2026-06-10 — Baseline preservation

Restored project state was preserved before Linux-native build work.

Tags involved:

```text
v1-baseline-restored
baseline-commit-before-linux-build
v1-maintenance-import
````

`v1-baseline-restored` is the source tag used for the initial baseline artifact release.

## 2026-06-10 — Atmel Studio baseline builds

Built both original Atmel Studio configurations:

* Debug
* Release

Production configuration is currently unknown, so both outputs were preserved.

Baseline size results:

```text
Debug:
  text 6636
  data 538
  bss  231

Release:
  text 6068
  data 538
  bss  231
```

Static RAM use:

```text
data + bss = 769 bytes
```

This leaves limited stack margin on ATmega168, so RAM usage remains a maintenance concern.

## 2026-06-10 — Artifact handling

Baseline binaries were kept out of normal git history.

Release artifacts were uploaded to GitHub Release:

```text
v1-baseline-restored
```

Committed records include:

```text
firmware-candidates/v1-baseline-restored/MANIFEST.txt
firmware-candidates/v1-baseline-restored/checksums.sha256
firmware-candidates/v1-baseline-restored/size-debug.txt
firmware-candidates/v1-baseline-restored/size-release.txt
```

Local binary staging is ignored under:

```text
artifacts/
```

## 2026-06-10 — WSL/Linux build

Added a root `Makefile` for WSL/Linux `avr-gcc` builds.

The Linux build currently compiles the same source files as the Atmel Studio project:

```text
main.c
gsm.c
usart.c
```

Important preserved build options:

```text
-mmcu=atmega168
-funsigned-char
-funsigned-bitfields
-ffunction-sections
-fdata-sections
-fpack-struct
-fshort-enums
-Wall
-lm
```

Added compatibility option:

```text
-fcommon
```

Reason: newer GCC rejected legacy globals defined in `usart.h`. `-fcommon` preserves older GCC behavior for now without changing source.

## 2026-06-10 — WSL build comparison

Debug size matches the Atmel Studio baseline:

```text
Debug Atmel Studio:
  text 6636
  data 538
  bss  231

Debug WSL:
  text 6636
  data 538
  bss  231
```

Release size differs slightly:

```text
Release Atmel Studio:
  text 6068
  data 538
  bss  231

Release WSL:
  text 6048
  data 538
  bss  231
```

The 20-byte Release difference is probably toolchain/version related, but WSL Release output should be treated as a new candidate until reviewed.

## Known findings

### Header-defined globals

`usart.h` appears to define globals that are included by multiple `.c` files:

```text
receiveBuffer
receiveBufferPos
```

This is a likely cleanup candidate.

Do not fix it inside build-system commits. A possible later source cleanup is:

* define the storage once in `usart.c`
* declare the symbols as `extern` in `usart.h`
