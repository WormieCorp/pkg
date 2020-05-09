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

  char **transformed_args = choco_transform_arguments(arguments);

  char *program = get_program_from_path("choco.exe");
  if (!program) {
    program = get_program_from_environment("ChocolateyInstall", 2,
                                           "bin/choco.exe", "choco.exe");
  }

  if (program) {
    if (strcmp(transformed_args[0], "install") == 0
        || strcmp(transformed_args[0], "uninstall") == 0
        || strcmp(transformed_args[0], "upgrade") == 0)
      launch_program(program, transformed_args, true);
    else
      launch_program(program, transformed_args, false);
    free(program);
  } else
    log_error("Unable to get location of choco.exe\n");

  char **pos = transformed_args;
  while (*pos) {
    free(*pos);
    pos++;
  }

  puts("\n");

  free(transformed_args);

  release_arguments_data(arguments);

  return 0;
}
