#ifndef _HAVE_PKG_PARSERS_H
#define _HAVE_PKG_PARSERS_H 1
#include "pacman-parser.h"
#include "pkg-translator_export.h"

PKG_TRANSLATOR_EXPORT ArgumentsData *parse_arguments(int argc, char **argv);

#endif /* _HAVE_PKG_PARSERS_H */
