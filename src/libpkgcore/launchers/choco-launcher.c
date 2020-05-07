#include "choco-launcher.h"
#include "../logging.h"
#include "../parsers/parsers.h"
#include "config.h"
#include "launchers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCR_LENGTH 100

bool has_packages(const char **arguments, int count)
{
  for (int i = 0; i < count; i++) {
    if (*(arguments[i]) != '-')
      return true;
  }

  return false;
}

void add_packages(char **buffer, size_t *bufcurlen, const char **arguments,
                  int argumentsCount)
{
  for (int i = 0; i < argumentsCount; i++) {
    if (*(arguments[i]) != '-')
      buffer[(*bufcurlen)++] = STRDUP(arguments[i]);
  }
}

void add_non_package_arguments(char **buffer, size_t *bufcurlen,
                               const char **arguments, int argumentsCount)
{
  for (int i = 0; i < argumentsCount; i++) {
    if (*(arguments[i]) == '-') {
      buffer[(*bufcurlen)++] = STRDUP(arguments[i]);
    }
  }
}

char **choco_get_launch_args(const ArgumentsData *arguments)
{
  /*printf("Using transformer: "
         "\033[38;2;36;44;92;48;2;128;181;227mchocolatey\033[0m\n");*/
  log_info("Transforming arguments data to chocolatey arguments\n");

  if (!arguments) {
    char **bufAr = malloc(2 * sizeof(char *));
    bufAr[0]     = STRDUP("--help");
    bufAr[1]     = NULL;
    return bufAr;
  }

  size_t len    = 10 + arguments->unparsedArgsCount;
  size_t curlen = 0;
  char **bufAr  = malloc(len * sizeof(char *));

  switch (arguments->action) {
    case INSTALL:
      bufAr[curlen++] = STRDUP("install");
      if (!(arguments->flag & HELP_ARG)
          && !has_packages(arguments->unparsedArgs,
                           arguments->unparsedArgsCount)) {
        bufAr[curlen++] = STRDUP("--help");
        goto end;
      }
      break;

    case UPGRADE:
      bufAr[curlen++] = STRDUP("upgrade");
      if (!(arguments->flag & HELP_ARG)
          && !has_packages(arguments->unparsedArgs,
                           arguments->unparsedArgsCount))
        bufAr[curlen++] = STRDUP("all");
      break;

    default:
      if (!(arguments->flag & HELP_ARG)) {
        bufAr[curlen++] = STRDUP("--help");
        goto end;
      }
      break;
  }

  if (arguments->flag & HELP_ARG) {
    bufAr[curlen++] = STRDUP("--help");
    goto end;
  }

  add_packages(bufAr, &curlen, arguments->unparsedArgs,
               arguments->unparsedArgsCount);

  if (!arguments->confirm) { // The chocolatey argument confirm is opposite to
                             // other pkg managers
    bufAr[curlen++] = STRDUP("--yes");
    // Not needed really, as --yes implies --accept-license as well. But used in
    // case something changes in the future
    bufAr[curlen++] = STRDUP("--accept-license");
  }

  if (arguments->flag & NODEP_ARG)
    bufAr[curlen++] = STRDUP("--ignore-dependencies");

  if (arguments->flag & HIDE_PROGRESS_ARG)
    bufAr[curlen++] = STRDUP("--no-progress");

  if (arguments->flag & VERBOSE_ARG)
    bufAr[curlen++] = STRDUP("--verbose");

  if (arguments->flag & DEBUG_ARG)
    bufAr[curlen++] = STRDUP("--debug");

  add_non_package_arguments(bufAr, &curlen, arguments->unparsedArgs,
                            arguments->unparsedArgsCount);

end:

  bufAr[curlen++] = NULL;

  return bufAr;
}
