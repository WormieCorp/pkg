#ifndef _HAVE_PKG_PARSERS_H
#define _HAVE_PKG_PARSERS_H 1
#include "pkg-data.h"
#include "pkgcore_export.h"

enum ParseUnionFlag {
  ACTION,
  FLAG,
  CONFIRM,
};

union ParseType {
  enum ActionType action;
  enum ArgumentFlag flag;
  bool confirm;
};

struct ParserData {
  const char *singleArgs;
  const char *longArgs;
  union ParseType type;
  enum ParseUnionFlag unionType;
  bool isRequired;
  bool abort;
};

PKGCORE_EXPORT bool execute_parsing(ArgumentsData *data,
                                    const struct ParserData parserData[],
                                    int parserDataSize, int argc,
                                    const char **argv);

PKGCORE_EXPORT ArgumentsData *parse_arguments(int argc, char **argv);

#endif /* _HAVE_PKG_PARSERS_H */
