/**
 * @file incbin.h
 * @author Dale Weiler
 * @brief Utility for including binary files
 *
 * Facilities for including binary files into the current translation unit and
 * making use from them externally in other translation units.
 */
#ifndef INCBIN_HDR
#define INCBIN_HDR
#include <limits.h>

#if defined(__SSE__) || defined(__neon__)
# define INCBIN_ALIGNMENT 16
#else
# if ULONG_MAX == 0xffffffffu
#  define INCBIN_ALIGNMENT 4
# else
#  define INCBIN_ALIGNMENT 8
# endif
#endif

#define INCBIN_ALIGN __attribute__((aligned(INCBIN_ALIGNMENT)))

#ifdef __cplusplus
#  define INCBIN_EXTERNAL extern "C"
#else
#  define INCBIN_EXTERNAL extern
#endif

#define INCBIN_STR(X) #X
#define INCBIN_STRINGIZE(X) INCBIN_STR(X)

/**
 * @brief Externally reference binary data included in another translation unit.
 *
 * Produces two external symbols that reference the binary data included in
 * another translation unit.
 *
 * The symbol names are a concatenation of "g" before *NAME*; with "Data", as well
 * as "Size" after. An example is provided below.
 *
 * @param NAME The name given for the binary data
 *
 * @code
 * INCBIN_EXTERN(Foo);
 *
 * // Now you have the following symbols:
 * // extern unsigned char gFooData[];
 * // extern unsigned int gFooSize;
 * @endcode
 */
#define INCBIN_EXTERN(NAME) \
    INCBIN_EXTERNAL INCBIN_ALIGN unsigned char g ## NAME ## Data[]; \
    INCBIN_EXTERNAL unsigned int g ## NAME ## Size

/**
 * @brief Include a binary file into the current translation unit.
 *
 * Includes a binary file into the current translation unit, producing two symbols
 * for objects that encode the data and size respectively.
 *
 * The symbol names are a concatenation of "g" before *NAME*; with "Data", as well
 * as "Size" after. An example is provided below.
 *
 * @param NAME The name to associate with this binary data (as an identifier.)
 * @param FILENAME The file to include (as a string literal.)
 *
 * @code
 * INCBIN(Icon, "icon.png");
 *
 * // Now you have the following symbols:
 * // unsigned char gIconData[];
 * // unsigned int gIconSize;
 * @endcode
 *
 * @warning This must be used in global scope
 *
 * To externally reference the data included by this in another translation unit
 * please @see INCBIN_EXTERN.
 */
#define INCBIN(NAME, FILENAME) \
    __asm__(".section .rodata\n" \
            ".global g" #NAME "\n" \
            ".type g" #NAME ", @object\n" \
            ".align " INCBIN_STRINGIZE(INCBIN_ALIGNMENT) " \n" \
            "g" #NAME ":\n" \
            "  .incbin \"" FILENAME "\"\n" \
            ".global g" #NAME "Size\n" \
            ".type g" #NAME "Size, @object\n" \
            ".align " INCBIN_STRINGIZE(INCBIN_ALIGNMENT) " \n" \
            "g" #NAME "Size:\n" \
            "  .int g" #NAME "Size - g" #NAME "\n"); \
    INCBIN_EXTERN(NAME)

#undef INCBIN_STRINGIZE
#undef INCBIN_STR
#undef INCBIN_EXTERNAL
#undef INCBIN_ALIGN
#undef INCBIN_ALIGNMENT

#endif
