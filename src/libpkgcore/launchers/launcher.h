#ifndef _HAVE_PKG_LAUNCHERS_H
#define _HAVE_PKG_LAUNCHERS_H 1
#include "pkg-data.h"
#include "pkgcore_export.h"
#include <stdbool.h>

PKGCORE_EXPORT bool compare_helper(const char *argument, int count, ...);

PKGCORE_EXPORT void execute_package_manager(const ArgumentsData *data);

PKGCORE_EXPORT void launch_program(const char *path, const char **arguments,
                                   bool elevate);

#endif /* _HAVE_PKG_LAUNCHERS_H */
