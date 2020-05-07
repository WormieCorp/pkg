#ifndef _HAVE_PKG_PACMAN_PARSER_H
#define _HAVE_PKG_PACMAN_PARSER_H 1
#include "../pkg-data.h"
#include "pkg-translator_export.h"

PKG_TRANSLATOR_EXPORT ArgumentsData *pacman_parse_arguments(int argc,
                                                            char **argv);

PKG_TRANSLATOR_NO_EXPORT bool add_unparsed_argument(ArgumentsData *arguments,
                                                    const char *arg,
                                                    int *availableSize);

PKG_TRANSLATOR_NO_EXPORT bool
add_unparsed_char(ArgumentsData *arguments, const char arg, int *availableSize);

PKG_TRANSLATOR_NO_EXPORT bool
add_unparsed_long_argument(ArgumentsData *arguments, const char *arg,
                           int *availableSize);

PKG_TRANSLATOR_NO_EXPORT bool parse_long_arguments(ArgumentsData *data,
                                                   const char *argument,
                                                   int *availableUnparsedSize);

PKG_TRANSLATOR_NO_EXPORT bool parse_short_arguments(ArgumentsData *data,
                                                    const char *argument,
                                                    int *availableUnparsedSize);

#endif /* _HAVE_PKG_PACMAN_PARSER_H */
