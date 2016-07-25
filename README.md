# Concurrency Litmus Tests
Litmus tests for demonstrating weak memory behaviours.

This should be compiled with [musl](http://www.musl-libc.org/), which supports
C11 thread definitions.

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
