#ifndef _HAVE_PKG_DATA_H
#define _HAVE_PKG_DATA_H 1
#include "pkg-translator_export.h"
#include <stdbool.h>

enum ActionType {
  NO_ACTION = 0,
  INSTALL,
  UNINSTALL,
  UPGRADE,
  LIST,
  SEARCH,
  INFO,
};

enum ArgumentFlag {
  NO_FLAG           = 0,
  LOCALONLY_ARG     = 1 << 0,
  NODEP_ARG         = 1 << 1,
  REFRESH_ARG       = 1 << 2,
  RECURSE_ARG       = 1 << 3,
  UNNEEDED_ARG      = 1 << 4,
  NO_SAVE_ARG       = 1 << 5,
  HELP_ARG          = 1 << 6,
  VERBOSE_ARG       = 1 << 7,
  DEBUG_ARG         = 1 << 8,
  HIDE_PROGRESS_ARG = 1 << 9,
};

typedef struct ArgumentsData {
  enum ActionType action;
  enum ArgumentFlag flag;
  bool confirm;
  char **unparsedArgs;
  int unparsedArgsCount;
} ArgumentsData;

PKG_TRANSLATOR_EXPORT void release_arguments_data(ArgumentsData *arguments);

#endif /* _HAVE_PKG_DATA_H */
