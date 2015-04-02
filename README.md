# incbin

Include binary files in your C/C++ applications with ease

## Example

    #include "incbin.h"

    INCBIN(Icon, "icon.png");

    // This translation unit now has three symbols
    // const unsigned char gIconData[];
    // const unsigned char *gIconEnd;
    // const unsigned int gIconSize;

    // Reference in other translation units like this
    INCBIN_EXTERN(Icon);

    // This translation unit now has two extern symbols
    // extern const unsigned char gIconData[];
    // extern const unsigned char *gIconEnd;
    // extern const unsigned int gIconSize;

## Portability

Known to work on the following compilers

* GCC
* Clang
* PathScale
* Intel
* Solaris
* Green Hills
* XCode
* ArmCC

If your compiler is not listed, as long as it supports GCC inline assembler, this
should work.

MSVC is not supported.

## Alignment

The data included by this tool will be aligned on the architectures word boundary
unless `__SSE__`, `__AVX__` or `__neon__` is defined, then it's aligned on a byte
boundary that respects SIMD convention. The table of the alignments for SIMD
alignment is as follows

| SIMD | Alignment |
|------|-----------|
| SSE  | 16        |
| Neon | 16        |
| AVX  | 32        |

## Explanation

`INCBIN` is a macro which uses the inline assembler provided by almost all
compilers to include binary files. It achieves this by utilizing the `.incbin`
directive of the inline assembler. It then uses the assembler to calculate the
size of the included binary and exports two global symbols that can be externally
referenced in other translation units which contain the data and size of the
included binary data respectively.

## Miscellaneous

Documentation for the API is provided by the header using Doxygen notation.
For licensing information see UNLICENSE.
