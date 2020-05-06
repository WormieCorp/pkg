#ifndef _HAVE_PKG_CHOCO_LAUNCHER_H
#define _HAVE_PKG_CHOCO_LAUNCHER_H 1
#include "../pkg-data.h"
#include "pkg-translator_export.h"

PKG_TRANSLATOR_EXPORT char **
choco_get_launch_args(const ArgumentsData *arguments);

PKG_TRANSLATOR_EXPORT char *choco_get_program_path(void);

PKG_TRANSLATOR_EXPORT void choco_launch_program(const ArgumentsData *arguments);

#endif /* _HAVE_PKG_CHOCO_LAUNCHER_H */
