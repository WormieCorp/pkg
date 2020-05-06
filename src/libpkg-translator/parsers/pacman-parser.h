#ifndef _HAVE_PKG_PACMAN_PARSER_H
#define _HAVE_PKG_PACMAN_PARSER_H 1
#include "../pkg-data.h"
#include "pkg-translator_export.h"

PKG_TRANSLATOR_EXPORT ArgumentsData *pacman_parse_arguments(int argc,
                                                            char **argv);

PKG_TRANSLATOR_NO_EXPORT bool
parse_transaction_arguments(const char arg, ArgumentsData *arguments);

PKG_TRANSLATOR_NO_EXPORT bool add_unparsed_argument(const char *arg,
                                                    ArgumentsData *arguments,
                                                    int *availableSize);
PKG_TRANSLATOR_NO_EXPORT bool
add_unparsed_char(const char arg, ArgumentsData *arguments, int *availableSize);
PKG_TRANSLATOR_NO_EXPORT bool
add_unparsed_long_argument(const char *arg, ArgumentsData *arguments,
                           int *availableSize);
PKG_TRANSLATOR_NO_EXPORT bool
parse_transaction_arguments(const char arg, ArgumentsData *arguments);

#endif /* _HAVE_PKG_PACMAN_PARSER_H */
