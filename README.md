# Ryte

A library for programatically generating code for retro systems,
such as the MOS 6502 and the Motorola 68K. Ryte exposes a uniform
API for generating code, but will allow you to dip into lower level
APIs for generating system-specific code.

Effectively, ryte takes generic code written in the form
```
procedure add_8_9:
push 8
push 9
iadd
ret
```
and generates the correct bytecode for each individual system;

## Usage
`ryte <file> [-s system]`

### `-s system`
One of the following:
- `mos6502`
- `m68k`
