# ush — a tiny Unix shell (C11)

This project implements a small educational Unix shell called `ush`, written in C (C11). It reads commands from standard input, parses them, and executes built‑ins and external programs. A lightweight support library, `libmx`, is included in the repository and built automatically by the Makefile.

## Prerequisites
- POSIX‑compatible environment (macOS or Linux)
- `clang`
- `make`

## Build
The Makefile builds the `ush` binary and the bundled `libmx` library.

```bash
# Build (default)
make

# Rebuild from scratch
make reinstall

# Remove build artifacts for this project
make clean

# Remove the binary and clean libmx
make uninstall
```

The resulting binary will be placed at:

```
./ush
```

## Run
After building, start the shell with:

```bash
./ush
```

Then type commands at the prompt and press Enter. Use `Ctrl+D` (EOF) to exit, or the built‑in `exit` if implemented for your current version.

## Project structure
Key directories and files in this repository:

- `libmx/` — utility/support library used by `ush` (built automatically by the Makefile).
- `inc/` — public headers for `ush`.
- `src/` — source code for parsing, execution, models, and utilities.
- `Makefile` — build script with common targets (`make`, `make clean`, `make uninstall`, `make reinstall`).

## Development notes
- C standard: C11
- Default compiler flags (from Makefile): `-std=c11 -Wall -Wextra -Werror -Wpedantic`
- Include paths: `-I./inc -I./libmx/inc`

## Troubleshooting
- If you change headers or `libmx`, prefer `make reinstall` to ensure a clean rebuild.
- On systems where `clang` is not default, install it or adjust `CC` in the Makefile (use at your own risk).

## License
Not specified. If you intend to distribute this project, please add a license file appropriate for your use case.
