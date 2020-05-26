#include "parsers.h"
#include "../utilities.h"
#include "choco-parser.h"
#include "config.h"
#include "pacman-parser.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#if HAVE_MALLOC_H
#  include <malloc.h>
#else
#  include <stdlib.h>
#endif

#define PARSERS_COUNT 2

void update_arguments_data(ArgumentsData *data,
                           const struct ParserData *parserData)
{
  switch (parserData->unionType) {
    case ACTION:
      data->action = parserData->type.action;
      break;
    case FLAG:
      data->flag |= parserData->type.flag;
      break;
    case CONFIRM:
      data->confirm = parserData->type.confirm;
      break;
    default:
      break; // Let us just ignore it.
  }
}

bool execute_short_parsing(char *arg, ArgumentsData *data,
                           const struct ParserData *parserData)
{
  if (!parserData->singleArgs)
    return true;

  char *pos     = arg;
  bool unparsed = false;

  while (*(++pos)) {
    if (*pos == ' ')
      continue;
    const char *argPos = parserData->singleArgs;
    bool found         = false;
    while (*argPos) {
      if (*pos == *argPos) {
        found = true;
        update_arguments_data(data, parserData);
        if (parserData->abort) {
          return false;
        }
        break;
      }

      argPos++;
    }

    if (!found)
      unparsed = true;
    else {
      *pos = ' ';
    }
  }

  return unparsed;
}

void add_unparsed_arguments(ArgumentsData *data, const char *arg)
{
  if (*arg == '-' && *(arg + 1) != '-') {
    const char *pos = arg;
    while (*(++pos)) {
      if (*pos == ' ')
        continue;
      char buf[3];
      snprintf(buf, sizeof(buf), "-%c", *pos);
      data->unparsedArgs[data->unparsedArgsCount++] = STRDUP(buf);
    }
  } else {
    data->unparsedArgs[data->unparsedArgsCount++] = STRDUP(arg);
  }
}

bool execute_parsing(ArgumentsData *data, const struct ParserData parserData[],
                     int parserDataSize, int argc, const char **argv)
{
  if (data->unparsedArgs == NULL)
    data->unparsedArgs = malloc(argc * sizeof(char *));
  bool argumentsFound = false;

  for (int i = 0; i < argc; ++i) {
    char *argument = STRDUP(argv[i]);
    bool unparsed  = true;

    for (int j = 0; j < parserDataSize; ++j) {
      if (string_to_index(argument, parserData[j].longArgs) >= 0) {
        update_arguments_data(data, &parserData[j]);
        unparsed       = false;
        argumentsFound = true;
      } else if (*argument != '-' || *(argument + 1) == '-') {
        continue;
      } else if (*argument == '-' && *(argument + 1) != '-') {
        // We need to set unparsed to false
        unparsed = execute_short_parsing(argument, data, &parserData[j]);
        if (!argumentsFound && strcmp(argument, argv[i]))
          argumentsFound = true;
      }

      if (!unparsed) {
        if (parserData[j].abort) {
          free(argument);
          return argumentsFound;
        }
        break;
      }
    }

    if (unparsed)
      add_unparsed_arguments(data, argument);

    free(argument);
  }

  return argumentsFound;
}

ArgumentsData *parse_arguments(int argc, char **argv)
{
  ArgumentsData *(*parsers[PARSERS_COUNT])(int, char **) = {
      choco_parse_arguments,
      pacman_parse_arguments,
  };

  ArgumentsData *data = NULL;

  for (int i = 0; i < PARSERS_COUNT; i++) {
    data = parsers[i](argc, argv);
    if (data)
      break;
  }

  return data;
}
