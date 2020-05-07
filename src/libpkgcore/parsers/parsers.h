#ifndef _HAVE_PKG_PARSERS_H
#define _HAVE_PKG_PARSERS_H 1
#include "pacman-parser.h"
#include "pkgcore_export.h"

PKGCORE_EXPORT ArgumentsData *parse_arguments(int argc, char **argv);

#endif /* _HAVE_PKG_PARSERS_H */
