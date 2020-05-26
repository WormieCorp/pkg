#include "choco-parser.h"
#include "../logging.h"
#include "../pkg-data.h"
#include "../utilities.h"
#include "config.h"
#include "parsers.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#if HAVE_MALLOC_H
#  include <malloc.h>
#endif

bool choco_parse_install_upgrade_arguments(ArgumentsData *data, int argc,
                                           char **argv);
bool choco_parse_uninstall_arguments(ArgumentsData *data, int argc,
                                     char **argv);
bool choco_parse_list_search_info_arguments(ArgumentsData *data, int argc,
                                            char **argv);

ArgumentsData *choco_parse_arguments(int argc, char **argv)
{
  (void)argv;
  if (argc == 0)
    return NULL;

  log_debug("Trying to parse arguments using chocolatey parser...\n");

  ArgumentsData *data = calloc(1, sizeof(ArgumentsData));
  data->unparsedArgs  = NULL;
  data->confirm       = true;
  data->flag |= REFRESH_ARG;
  bool result     = true;
  bool setHelpArg = false;

  switch (string_to_index(
      *argv, "install|uninstall|upgrade|list|search|info|--help|-h|-?")) {
    case 0:
      data->action = INSTALL;
      result = choco_parse_install_upgrade_arguments(data, argc - 1, argv + 1)
               || argc > 1;
      setHelpArg = !result && argc == 1;
      break;
    case 1:
      data->action = UNINSTALL;
      result =
          choco_parse_uninstall_arguments(data, argc - 1, argv + 1) || argc > 1;
      setHelpArg = !result && argc == 1;
      break;
    case 2:
      data->action = UPGRADE;
      result = choco_parse_install_upgrade_arguments(data, argc - 1, argv + 1)
               || argc > 1;
      setHelpArg = !result && argc == 1;
      break;
    case 3:
      data->action = LIST;
      choco_parse_list_search_info_arguments(data, argc - 1, argv + 1);
      result = true;
      break;
    case 4:
      data->action = SEARCH;
      choco_parse_list_search_info_arguments(data, argc - 1, argv + 1);
      result = true;
      break;
    case 5:
      data->action = INFO;
      result = choco_parse_list_search_info_arguments(data, argc - 1, argv + 1)
               || argc > 1;
      setHelpArg = !result && argc == 1;
      break;
    case 6:
    case 7:
    case 8:
      data->action = HELP_ARG;
      break;
    default:
      result = false;
      break;
  }

  if (setHelpArg || (data->flag & HELP_ARG)) {
    data->flag = HELP_ARG;
    result     = true;
  }

  if ((data->flag & LOCALONLY_ARG) == LOCALONLY_ARG) {
    data->flag ^= REFRESH_ARG;
  }

  if (!result) {
    release_arguments_data(data);
    return NULL;
  }

  log_info("Parsed arguments using chocolatey parser...\n");

  return data;
}

bool choco_parse_install_upgrade_arguments(ArgumentsData *data, int argc,
                                           char **argv)
{
  struct ParserData parserData[] = {
      {
          .singleArgs = "h?",
          .longArgs   = "--help",
          .type.flag  = HELP_ARG,
          .unionType  = FLAG,
          .abort      = true,
      },
      {
          .singleArgs = "v",
          .longArgs   = "--verbose",
          .unionType  = FLAG,
          .type.flag  = VERBOSE_ARG,
      },
      {
          .singleArgs = "d",
          .longArgs   = "--debug",
          .unionType  = FLAG,
          .type.flag  = DEBUG_ARG,
      },
      {
          .singleArgs   = "y",
          .longArgs     = "--yes|--confirm",
          .type.confirm = false,
          .unionType    = CONFIRM,
      },
      {
          .singleArgs = NULL,
          .longArgs   = "--no-progress",
          .type.flag  = HIDE_PROGRESS_ARG,
          .unionType  = FLAG,
      },
      {
          .singleArgs = "i",
          .longArgs   = "--ignoredependencies|--ignore-dependencies",
          .type.flag  = NODEP_ARG,
          .unionType  = FLAG,
      },
      {
          // This item is just so the package 'all' won't be set as an unparsed
          // argument
          .singleArgs = NULL,
          .longArgs   = "all",
          .unionType  = ACTION,
      },
  };
  parserData[6].type.action = data->action;

  return execute_parsing(data, parserData,
                         sizeof(parserData) / sizeof(struct ParserData), argc,
                         argv);
}

bool choco_parse_uninstall_arguments(ArgumentsData *data, int argc, char **argv)
{
  struct ParserData parserData[] = {
      {
          .singleArgs = "h?",
          .longArgs   = "--help",
          .type.flag  = HELP_ARG,
          .unionType  = FLAG,
          .abort      = true,
      },
      {
          .singleArgs = "v",
          .longArgs   = "--verbose",
          .unionType  = FLAG,
          .type.flag  = VERBOSE_ARG,
      },
      {
          .singleArgs = "d",
          .longArgs   = "--debug",
          .unionType  = FLAG,
          .type.flag  = DEBUG_ARG,
      },
      {
          .singleArgs   = "y",
          .longArgs     = "--yes|--confirm",
          .type.confirm = false,
          .unionType    = CONFIRM,
      },
      {
          .singleArgs = "x",
          .longArgs   = "--forcedependencies|--force-dependencies|"
                      "--removedependencies|--remove-dependencies",
          .type.flag = UNNEEDED_ARG,
          .unionType = FLAG,
      },
  };

  return execute_parsing(data, parserData,
                         sizeof(parserData) / sizeof(struct ParserData), argc,
                         argv);
}

bool choco_parse_list_search_info_arguments(ArgumentsData *data, int argc,
                                            char **argv)
{
  struct ParserData parserData[] = {
      {
          .singleArgs = "h?",
          .longArgs   = "--help",
          .type.flag  = HELP_ARG,
          .unionType  = FLAG,
          .abort      = true,
      },
      {
          .singleArgs = "v",
          .longArgs   = "--verbose",
          .unionType  = FLAG,
          .type.flag  = VERBOSE_ARG,
      },
      {
          .singleArgs = "d",
          .longArgs   = "--debug",
          .unionType  = FLAG,
          .type.flag  = DEBUG_ARG,
      },
      {
          .singleArgs = "l",
          .longArgs   = "--lo|--local|--localonly|--local-only",
          .unionType  = FLAG,
          .type.flag  = LOCALONLY_ARG,
      },
  };

  return execute_parsing(data, parserData,
                         sizeof(parserData) / sizeof(struct ParserData), argc,
                         argv);
}
