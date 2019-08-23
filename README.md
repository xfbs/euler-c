# Project Euler in C

These are my solutions to [Project Euler](https://projecteuler.net/) problems
in C. All of these are written by me in an attempt to fool around with
mathematics and sharpen my programming skills.

## Rules

- The simpler, the better.
- Keep thinks DRY.
- Hard limit of 100ms for each solution.

## Building

This should build fine on both macOS and Linux. Not tested on other platforms.
It requires `meson`, `ninja`, `pkg-config`, `libjansson` and `zlib`.

To build, use `meson` and `ninja`.

    meson build
    cd build
    ninja

This will generate a binary, `euler-c`, in the build directory. You can run
this to see what options are available.

## Progress

Run

    ./build/euler-c check

To see the current progress and check the solutions.

## See Also

All utility functions are located at [libeuler.c](https://github.com/xfbs/libeuler.c).

## License

MIT, see [`LICENSE.md`](LICENSE.md) for more information. 
