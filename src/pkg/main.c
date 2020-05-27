#include "config.h"
#include <launchers/choco_launcher.h>
#include <logging.h>
#include <parsers/parsers.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  log_info("\033[1;92m" PROJECT_NAME " v" PROJECT_VERSION "...\033[0m\n\n");

  ArgumentsData *arguments = parse_arguments(argc - 1, argv + 1);

  if (!choco_launch_program(arguments)) {
    log_error("Unable to launch or parse to choco.exe\n");
  }

  puts("\n");

  release_arguments_data(arguments);

  return 0;
}
