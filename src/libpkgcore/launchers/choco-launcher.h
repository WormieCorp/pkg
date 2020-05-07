#ifndef _HAVE_PKG_CHOCO_LAUNCHER_H
#define _HAVE_PKG_CHOCO_LAUNCHER_H 1
#include "../pkg-data.h"
#include "pkgcore_export.h"

PKGCORE_EXPORT char **choco_get_launch_args(const ArgumentsData *arguments);

PKGCORE_EXPORT char *choco_get_program_path(void);

PKGCORE_EXPORT void choco_launch_program(const ArgumentsData *arguments);

#endif /* _HAVE_PKG_CHOCO_LAUNCHER_H */
