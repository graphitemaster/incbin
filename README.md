# incbin

Include binary files in your C/C++ applications with ease

## Example

    #include "incbin.h"

    INCBIN(Icon, "icon.png");

    // This translation unit now has two symbols
    // gIconData (unsigned char[])
    // gIconSize (unsigned int)

    // Reference in other translation units like this
    INCBIN_EXTERN(Icon);

    // This translation unit now has two extern symbols
    // gIconData (extern unsigned char[])
    // gIconSize (unsigned int)

## Portability

This will work for any architecture, on all compilers that support GCC inline
assembler (which is almost all compilers with a few notable exceptions.)

## Alignment

The data included by this tool will be aligned on the architectures word boundary
unless `__SSE__` or `__neon__` is defined, then it's aligned on a 16-byte boundary,
so that it can effectively be used by SIMD code safely.

## Explanation

`INCBIN` is a macro which uses the inline assembler provided by almost all
compilers to include binary files. It achieves this by utilizing the `.incbin`
directive of the inline assembler. It then uses the assembler to calculate the
size of the included binary and exports two global symbols that can be externally
referenced in other translation units which contain the data and size of the
included binary data respectively.

## Miscellaneous

Documentation for the API is provided by the header. For licensing information
see UNLICENSE.
