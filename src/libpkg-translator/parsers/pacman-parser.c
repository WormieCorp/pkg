#include "pacman-parser.h"
#include "../logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCR_UNPARSED 10

bool parse_long_arguments(ArgumentsData *data, const char *argument,
                          int *availableUnparsedSize);
bool parse_short_arguments(ArgumentsData *data, const char *argument,
                           int *availableUnparsedSize);

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
    if (data->action == NO_ACTION && *argv[i] == '-') {
      *argv[i]++;
      switch (*(argv[i])) {
        case 'h':
          if (data->action == NO_ACTION)
            data->flag |= HELP_ARG;
          break;
        case 'S':
          data->action = INSTALL;
          break;

        default:
          if (strcmp(argv[i], "-help") == 0) {
            data->flag |= HELP_ARG;
            return data;
          }
          release_arguments_data(data);
          return NULL;
      }
      *argv[i]++;
    } else if (data->action == NO_ACTION) {
      release_arguments_data(data);
      return NULL;
    } else if (*argv[i] != '-') {
      if (!add_unparsed_argument(argv[i], data, &availableUnparsedSize)) {
        release_arguments_data(data);
        return NULL;
      }
      continue;
    } else {
      *argv[i]++;
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

bool parse_long_arguments(ArgumentsData *data, const char *argument,
                          int *availableUnparsedSize)
{
  if (strcmp(argument, "help") == 0) {
    data->flag |= HELP_ARG;
    return true;
  } else if (strcmp(argument, "verbose") == 0) {
    data->flag |= VERBOSE_ARG;
    return true;
  } else if (strcmp(argument, "debug") == 0) {
    data->flag |= DEBUG_ARG;
    return true;
  } else if (strcmp(argument, "noprogressbar") == 0) {
    data->flag |= HIDE_PROGRESS_ARG;
    return true;
  }

  return add_unparsed_long_argument(argument, data, availableUnparsedSize);
}

bool parse_short_arguments(ArgumentsData *data, const char *argument,
                           int *availableUnparsedSize)
{
  while (*argument) {
    char c = *argument;
    switch (c) {
      case 'h':
        data->flag |= HELP_ARG;
        break;
      case 'v':
        data->flag |= VERBOSE_ARG;
        break;

      default:
        switch (data->action) {
          case INSTALL:
          case UPGRADE:
            if (!parse_transaction_arguments(c, data)
                && !add_unparsed_char(c, data, availableUnparsedSize))
              return false;
            break;
          default:
            if (!add_unparsed_char(c, data, availableUnparsedSize))
              return false;
            break;
        }
        break;
    }

    *argument++;
  }

  return true;
}

bool parse_transaction_arguments(const char arg, ArgumentsData *arguments)
{
  if (!arg)
    return true;
  switch (arg) {
    case 'u':
      arguments->action = UPGRADE;
      break;
    case 'y':
      arguments->flag |= REFRESH_ARG;
      break;
    case 'd':
      arguments->flag |= NODEP_ARG;
      break;
    default:
      return false;
  }

  return true;
}

bool reallocate_data(ArgumentsData *arguments, int *availableSize)
{
  if (arguments->unparsedArgsCount == *availableSize) {
    char **newUnparsedArgs =
        realloc(arguments->unparsedArgs,
                (*availableSize * INCR_UNPARSED) * sizeof(char *));
    if (!newUnparsedArgs) {
      log_error("Unable to re-allocate memory. Unable to continue...\n");
      return false;
    }
    *availableSize += INCR_UNPARSED;
  }

  return true;
}

bool add_unparsed_char(const char arg, ArgumentsData *arguments,
                       int *availableSize)
{
  char *buf = malloc(3 * sizeof(char));
  snprintf(buf, 3, "-%c", arg);

  bool result = add_unparsed_argument(buf, arguments, availableSize);
  free(buf);
  return result;
}

bool add_unparsed_long_argument(const char *arg, ArgumentsData *arguments,
                                int *availableSize)
{
  size_t len = 3 + strlen(arg);
  char *buf  = malloc(len * sizeof(char));
  snprintf(buf, len, "--%s", arg);

  bool result = add_unparsed_argument(buf, arguments, availableSize);
  free(buf);
  return result;
}

bool add_unparsed_argument(const char *arg, ArgumentsData *arguments,
                           int *availableSize)
{
  if (!reallocate_data(arguments, availableSize))
    return false;

  log_verbose("Added unparsed argument '%s'!\n", arg);

  arguments->unparsedArgs[arguments->unparsedArgsCount++] = _strdup(arg);
  return arguments->unparsedArgs[arguments->unparsedArgsCount - 1] != NULL;
}
