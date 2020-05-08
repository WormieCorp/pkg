#ifndef _HAVE_PKG_RESOLVER_H
#define _HAVE_PKG_RESOLVER_H
#include "pkgcore_export.h"

PKGCORE_EXPORT char *
get_program_from_environment(const char *environmentVariable, int count, ...);

PKGCORE_EXPORT char *get_program_from_path(const char *executable);

#endif /* _HAVE_PKG_RESOLVER_H */
