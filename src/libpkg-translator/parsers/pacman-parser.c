#include "pacman-parser.h"
#include "../logging.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCR_UNPARSED 10

ArgumentsData *pacman_parse_arguments(int argc, char **argv)
{
  if (argc == 0)
    return NULL;

  log_debug("Trying to parse arguments using pacman parser...\n");

  int availableUnparsedSize = INCR_UNPARSED;
  ArgumentsData *data       = calloc(1, sizeof(ArgumentsData));
  data->unparsedArgs        = malloc(availableUnparsedSize * sizeof(char *));
  data->confirm             = true;

  for (int i = 0; i < argc; ++i) {
    if (*argv[i] == '-')
      argv[i]++;
    else if (data->flag & HELP_ARG)
      return data;
    else if (data->action == NO_ACTION) {
      release_arguments_data(data);
      return NULL;
    } else {
      if (!add_unparsed_argument(data, argv[i], &availableUnparsedSize)) {
        release_arguments_data(data);
        return NULL;
      }
      continue;
    }

    if (*argv[i] == '-') {
      if (!parse_long_arguments(data, argv[i] + 1, &availableUnparsedSize)) {
        release_arguments_data(data);
        return NULL;
      }
    } else if (!parse_short_arguments(data, argv[i], &availableUnparsedSize)) {
      release_arguments_data(data);
      return NULL;
    }
  }

  log_info("Parsed arguments using pacman parser.\n");

  return data;
}

bool parse_long_common_arguments(ArgumentsData *data, const char *argument,
                                 int *availableUnparsedSize)
{
  (void)availableUnparsedSize;
  if (strcmp(argument, "help") == 0) {
    data->flag |= HELP_ARG;
    return true;
  }

  if (data->action == NO_ACTION)
    return false;

  if (strcmp(argument, "verbose") == 0) {
    data->flag |= VERBOSE_ARG;
    return true;
  }

  if (strcmp(argument, "debug") == 0) {
    data->flag |= DEBUG_ARG;
    return true;
  }

  if (strcmp(argument, "noconfirm") == 0) {
    data->confirm = false;
    return true;
  }

  return false;
}

bool parse_long_transaction_arguments(ArgumentsData *data, const char *argument,
                                      int *availableUnparsedSize)
{
  (void)availableUnparsedSize;
  if (data->action != INSTALL && data->action != UPGRADE
      && data->action != UNINSTALL)
    return false;

  if (strcmp(argument, "noprogressbar") == 0) {
    data->flag |= HIDE_PROGRESS_ARG;
    return true;
  }
  if (strcmp(argument, "nodeps") == 0) {
    data->flag |= NODEP_ARG;
    return true;
  }

  return false;
}

bool parse_long_arguments(ArgumentsData *data, const char *argument,
                          int *availableUnparsedSize)
{
#define LONG_PARSERS 3
  static bool (*long_parsers[LONG_PARSERS])(ArgumentsData *, const char *,
                                            int *) = {
      parse_long_common_arguments,
      parse_long_transaction_arguments,
      add_unparsed_long_argument,
  };

  for (int i = 0; i < LONG_PARSERS; ++i) {
    if (long_parsers[i](data, argument, availableUnparsedSize))
      return true;
  }

  return false;
}

bool parse_short_operator_arguments(ArgumentsData *data, const char arg,
                                    int *availableUnparsedSize)
{
  (void)availableUnparsedSize;
  if (data->action != NO_ACTION)
    return false;

  switch (arg) {
    case 'S':
      data->action = INSTALL;
      break;

    default:
      return false;
  }

  return true;
}

bool parse_short_common_arguments(ArgumentsData *data, const char arg,
                                  int *availableUnparsedSize)
{
  (void)availableUnparsedSize;
  switch (arg) {
    case 'h':
      data->flag |= HELP_ARG;
      break;
    case 'v':
      data->flag |= VERBOSE_ARG;
      break;
    default:
      return false;
  }

  return true;
}

bool parse_short_transaction_arguments(ArgumentsData *arguments, const char arg,
                                       int *availableUnparsedSize)
{
  (void)availableUnparsedSize;
  if (arguments->action != INSTALL && arguments->action != UPGRADE
      && arguments->action != UNINSTALL)
    return false;

  switch (arg) {
    case 'd':
      arguments->flag |= NODEP_ARG;
      break;
    default:
      return false;
  }

  return true;
}

bool parse_short_sync_arguments(ArgumentsData *data, const char arg,
                                int *availableUnparsedSize)
{
  (void)availableUnparsedSize;
  if (data->action != INSTALL && data->action != UPGRADE && data->action != INFO
      && data->action != LIST && data->action != SEARCH)
    return false;

  switch (arg) {
    // These are not yet implemented
    case 'i':
    case 'l':
    case 'q': // Not sure about this one
    case 's':
      break;
    case 'u':
      data->action = UPGRADE;
      break;
    case 'y':
      data->flag |= REFRESH_ARG;
      break;

    default:
      return false;
  }

  return true;
}

bool parse_short_arguments(ArgumentsData *data, const char *argument,
                           int *availableUnparsedSize)
{
#define SHORT_PARSERS 5
  static bool (*short_parsers[SHORT_PARSERS])(struct ArgumentsData *,
                                              const char, int *) = {
      parse_short_operator_arguments,
      parse_short_common_arguments,
      parse_short_transaction_arguments,
      parse_short_sync_arguments,
      add_unparsed_char,
  };

  while (*argument) {
    bool result = false;
    char c      = *argument;
    for (int i = 0; i < SHORT_PARSERS; ++i) {
      if (short_parsers[i](data, c, availableUnparsedSize)) {
        result = true;
        break;
      }
    }
    if (!result)
      return result;
    argument++;
  }

  return true;
}

bool reallocate_data(ArgumentsData *arguments, int *availableSize)
{
  if (arguments->unparsedArgsCount == *availableSize) {
    char **newUnparsedArgs =
        realloc(arguments->unparsedArgs,
                (*availableSize + INCR_UNPARSED) * sizeof(char *));
    if (!newUnparsedArgs) {
      log_error("Unable to re-allocate memory. Unable to continue...\n");
      return false;
    }
    *availableSize += INCR_UNPARSED;
  }

  return true;
}

bool add_unparsed_char(ArgumentsData *arguments, const char arg,
                       int *availableSize)
{
  char *buf = malloc(3 * sizeof(char));
  snprintf(buf, 3, "-%c", arg);

  bool result = add_unparsed_argument(arguments, buf, availableSize);
  free(buf);
  return result;
}

bool add_unparsed_long_argument(ArgumentsData *arguments, const char *arg,
                                int *availableSize)
{
  size_t len = 3 + strlen(arg);
  char *buf  = malloc(len * sizeof(char));
  snprintf(buf, len, "--%s", arg);

  bool result = add_unparsed_argument(arguments, buf, availableSize);
  free(buf);
  return result;
}

bool add_unparsed_argument(ArgumentsData *arguments, const char *arg,
                           int *availableSize)
{
  if (!reallocate_data(arguments, availableSize))
    return false;

  log_verbose("Added unparsed argument '%s'!\n", arg);

  arguments->unparsedArgs[arguments->unparsedArgsCount++] = STRDUP(arg);
  return arguments->unparsedArgs[arguments->unparsedArgsCount - 1] != NULL;
}
