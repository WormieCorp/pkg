#include "choco-transformer.h"
#include "../logging.h"
#include "../parsers/parsers.h"
#include "config.h"
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

void add_common_arguments(char **buffer, size_t *bufcurlen,
                          const ArgumentsData *data)
{
  if (data->flag & VERBOSE_ARG)
    buffer[(*bufcurlen)++] = STRDUP("--verbose");
  if (data->flag & DEBUG_ARG)
    buffer[(*bufcurlen)++] = STRDUP("--debug");
}

void add_install_upgrade_arguments(char **buffer, size_t *bufcurlen,
                                   const ArgumentsData *data)
{
  if (data->action != INSTALL && data->action != UPGRADE)
    return;

  if (!data->confirm)
    buffer[(*bufcurlen)++] = STRDUP("--accept-license");
  if (data->flag & NODEP_ARG)
    buffer[(*bufcurlen)++] = STRDUP("--ignore-dependencies");
  if ((data->flag & HIDE_PROGRESS_ARG))
    buffer[(*bufcurlen)++] = STRDUP("--no-progress");
}

void add_transaction_arguments(char **buffer, size_t *bufcurlen,
                               const ArgumentsData *data)
{
  if (data->action < INSTALL && data->action > UPGRADE)
    // Do not do anything if action isn't install, upgrade or uninstall
    return;

  if (!data->confirm) {
    buffer[(*bufcurlen)++] = STRDUP("--yes");
  }
}

void add_remove_arguments(char **buffer, size_t *bufcurlen,
                          const ArgumentsData *data)
{
  if (data->action != UNINSTALL)
    return;

  if (data->flag & RECURSE_ARG) {
    log_warning(
        "Chocolatey do not store explicitly installed packages.\nSwitching to "
        "removing unneeded packages (packages not referenced by other "
        "packages,\nand is a dependency on specified packages to remove!\n");
    buffer[(*bufcurlen)++] = STRDUP("--remove-dependencies");
  }
  if (data->flag & UNNEEDED_ARG)
    buffer[(*bufcurlen)++] = STRDUP("--remove-dependencies");
}

char **choco_transform_arguments(const ArgumentsData *arguments)
{
  /*printf("Using transformer: "
         "\033[38;2;36;44;92;48;2;128;181;227mchocolatey\033[0m\n");*/
  log_info("Transforming arguments data to chocolatey arguments\n");

  if (!arguments) {
    char **bufAr = malloc(2 * sizeof(char *));
    bufAr[0]     = STRDUP("--help");
    bufAr[1]     = NULL;
    return bufAr;
  } else if ((arguments->flag & LOCALONLY_ARG)
             && (arguments->flag & REFRESH_ARG)) {
    log_error("Local Only and refresh only is used.\n");
    log_error("This is not a valid transaction. Exiting...\n");
    return NULL;
  }

  size_t len    = 10 + arguments->unparsedArgsCount;
  size_t curlen = 0;
  char **bufAr  = malloc(len * sizeof(char *));

#define TRANSFORMERS 4
  static void (*transforms[TRANSFORMERS])(char **, size_t *,
                                          const ArgumentsData *) = {
      add_common_arguments,
      add_transaction_arguments,
      add_install_upgrade_arguments,
      add_remove_arguments,
  };

  switch (arguments->action) {
    case INFO:
      bufAr[curlen++] = STRDUP("info");
      if (!has_packages(arguments->unparsedArgs,
                        arguments->unparsedArgsCount)) {
        bufAr[curlen++] = STRDUP("--help");
        goto end;
      }
      break;

    case INSTALL:
      bufAr[curlen++] = STRDUP("install");
      if (!has_packages(arguments->unparsedArgs,
                           arguments->unparsedArgsCount)) {
        bufAr[curlen++] = STRDUP("--help");
        goto end;
      }
      break;

    case UNINSTALL:
      bufAr[curlen++] = STRDUP("uninstall");
      if (!has_packages(arguments->unparsedArgs,
                           arguments->unparsedArgsCount)) {
        bufAr[curlen++] = STRDUP("--help");
        goto end;
      }
      break;

    case UPGRADE:
      bufAr[curlen++] = STRDUP("upgrade");
      if (!has_packages(arguments->unparsedArgs, arguments->unparsedArgsCount))
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

  for (int i = 0; i < TRANSFORMERS; ++i)
    transforms[i](bufAr, &curlen, arguments);

  add_non_package_arguments(bufAr, &curlen, arguments->unparsedArgs,
                            arguments->unparsedArgsCount);

end:

  bufAr[curlen++] = NULL;

  return bufAr;
}
