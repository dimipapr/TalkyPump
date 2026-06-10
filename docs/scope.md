# TalkyPump v1 maintenance scope

## Purpose

This repository is being maintained for the existing TalkyPump v1 field firmware and same-hardware replacement devices.

This is a maintenance rescue project, not a rewrite.

## Current hardware target

- MCU: ATmega168
- modem: SIM800L
- hardware: existing deployed TalkyPump v1 board design

Existing deployed hardware remains the target.

## Goals

- Preserve the original firmware source and historical build artifacts.
- Provide a Linux/WSL-native `avr-gcc` build path.
- Document the current firmware behavior from source code.
- Identify EEPROM layout and persistent state.
- Identify SMS commands, call/ring behavior, timers, watchdog behavior, power-loss behavior, and GSM recovery behavior.
- Fix only clear bugs using small, reviewable, bisectable commits.
- Reduce flash/RAM pressure where safe.
- Treat recovered flash/RAM as safety margin, not feature budget.

## Maintenance rules

- Do not redesign the firmware.
- Do not add features as part of cleanup.
- Preserve field-proven behavior unless a bug is clear and reviewed.
- Keep one logical change per commit.
- Avoid broad cleanup commits.
- Avoid clever abstractions.
- Keep changes small enough to bisect.
- Mark unknowns instead of guessing.
- Treat regressions as dangerous.
- Keep generated field-candidate artifacts traceable.

## EEPROM policy for maintenance reflashes

Maintenance reflashes are allowed to erase EEPROM.

After flashing, devices are expected to be reprovisioned.

EEPROM backward compatibility is not a current requirement for this rescue branch.

EEPROM layout may still be documented for diagnostics, but preserving existing EEPROM contents is not a release goal.

## Out of scope unless explicitly started later

- hardware redesign
- new product behavior
- pressure sensor support
- major firmware rewrite
- new user-facing features
- broad architecture refactor