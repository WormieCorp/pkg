#include "parsers.h"
#include "pacman-parser.h"
#include <stddef.h>

#define PARSERS_COUNT 1

ArgumentsData *parse_arguments(int argc, char **argv)
{
  ArgumentsData *(*parsers[PARSERS_COUNT])(int, char **) = {
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
