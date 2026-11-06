/* GNU FreeDink for AmigaOS: what configure would have found (every source
 * file includes <config.h>). No gettext (English), no fontconfig (the font
 * is the program's own LiberationSans-Regular.ttf), no zzip.
 * The AmiCradle Team. GPL 3 or later, like FreeDink. */
#define PACKAGE "freedink"
#define PACKAGE_NAME "GNU FreeDink"
#define PACKAGE_STRING "GNU FreeDink 109.6"
#define PACKAGE_TARNAME "freedink"
#define PACKAGE_VERSION "109.6"
#define PACKAGE_BUGREPORT "bug-freedink@gnu.org"
#define PACKAGE_URL "https://www.gnu.org/software/freedink/"
#define VERSION "109.6"
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_UNISTD_H 1
#define HAVE_GETOPT_H 1
#define HAVE_DECL_GETENV 1
#define HAVE_DECL_STRNCASECMP 1

/* what gnulib's configure adds, for gnulib/lib's xmalloc and hash */
#define _GL_CONFIG_H_INCLUDED 1
#define _GL_INLINE static inline
#define _GL_EXTERN_INLINE static inline
#define _GL_INLINE_HEADER_BEGIN
#define _GL_INLINE_HEADER_END
#define _GL_ATTRIBUTE_PURE __attribute__ ((__pure__))
#define _GL_ATTRIBUTE_CONST __attribute__ ((__const__))
#define _GL_ATTRIBUTE_MALLOC __attribute__ ((__malloc__))
#define _GL_ATTRIBUTE_ALLOC_SIZE(args)
#define _GL_ATTRIBUTE_FORMAT(spec)
#define _GL_ATTRIBUTE_DEPRECATED
#define _GL_ATTRIBUTE_NODISCARD
#define _GL_UNUSED __attribute__ ((__unused__))
#define _GL_ARG_NONNULL(params)
#define _GL_HAS_ATTRIBUTE(attr) 0
#ifdef __cplusplus
/* as gnulib's configure: "extern [[noreturn]] void" will not parse */
# undef _Noreturn
# define _Noreturn __attribute__ ((__noreturn__))
#endif

/* libnix has vasprintf() (src/str_util.cpp) but its <stdio.h> does not
   declare it */
#include <stdarg.h>
#ifdef __cplusplus
extern "C"
#endif
int vasprintf(char **, const char *, va_list);

/* gnulib's getopt (gnulib/lib/getopt.c, getopt1.c; amiga/gnulib/getopt.h)
   under its own names: libnix's getopt_long_only never returned */
#define __GETOPT_PREFIX rpl_
