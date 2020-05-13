#include <launchers/choco_launcher.h>
#include <launchers/launcher.h>
#include <logging.h>
#include <malloc.h>
#include <parsers/parsers.h>
#include <resolver.h>
#include <stdio.h>
#include <string.h>
#include <transformers/choco-transformer.h>

int main(int argc, char **argv)
{
  ArgumentsData *arguments = parse_arguments(argc - 1, argv + 1);

  if (!choco_launch_program(arguments)) {
    log_error("Unable to launch or parse to choco.exe\n");
  }

  puts("\n");

  release_arguments_data(arguments);

  return 0;
}
