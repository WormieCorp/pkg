#ifndef _HAVE_PKG_LAUNCHERS_H
#define _HAVE_PKG_LAUNCHERS_H 1
#include "pkgcore_export.h"
#include <stdbool.h>

PKGCORE_EXPORT void launch_program(const char *path, const char **arguments,
                                   bool elevate);

#endif /* _HAVE_PKG_LAUNCHERS_H */
