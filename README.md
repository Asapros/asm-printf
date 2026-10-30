asm-printf
==========

Simple partial implementation of cstdio's printf in assembly without dependencies.

String and memory manipulation helpers mimicking behaviour of standard C library functions (memcpy, strcpy, memchr, strchr, rawmemchr, strlen, fwrite, fputs) are also implemented in assembly as a part of the project.

Usage
-----

This printf implementation supports 4 format patterns: `%s` (null terminated string), `%%` ('%' escaping), `%lld` (signed 64-bit integer), `%llu` (unsigned 64-bit integer).

First argument (passed in the register `rdi`) is a pointer to the null-terminated template string and next arguments passed in the registers (`rsi`, `rdx`, `rcx`, `r8`, `r9`) fill % format patterns in that order.

Compilation
-----------

To run the project compile `main.asm` with `fasm`:

```bash
fasm main.asm
```

It produces an executable `main` with the example usage of the `printf` implementation from `string.inc`.
