# Concurrency Litmus Tests
Litmus tests for demonstrating weak memory behaviours.

## Build

This can be built with most modern compilers. There is a shim in place to add
C11 style thread support for systems which don't have `threads.h`. The default
compiler is set to `clang` (`$CC` in the Makefile), feel free to modify to a
compiler of choice. I've tested with `gcc`, `clang`, and `musl`. Just run `make`
to build.

Should work just fine on Linux systems.

## Supported tests:
 - SB
 - "CoWW" (I think this is an example of CoWW, but I stand to be corrected.)


## `mfence` impact

With fences
```
0 instances of weak behaviour observed.

real    0m35.343s
user    0m6.564s
sys     0m22.984s
```

Without fences:
```
$ time ./c_litmus -I 1000000 -q
1987 instances of weak behaviour observed.

real    0m33.722s
user    0m5.280s
sys     0m24.148s
```
