#include <launchers/launchers.h>
#include <logging.h>
#include <malloc.h>
#include <parsers/parsers.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  ArgumentsData *arguments = parse_arguments(argc - 1, argv + 1);

  char **transformed_args = choco_get_launch_args(arguments);

  printf("Would call 'choco.exe");

  char **pos = transformed_args;
  while (*pos) {
    printf(" %s", *pos);
    free(*pos);
    *pos++;
  }

  puts("'\n");

  free(transformed_args);

  release_arguments_data(arguments);

  return 0;
}
