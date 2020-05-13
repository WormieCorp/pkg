#include <stdbool.h>
#include <stdio.h>

void launch_program(const char *path, const char **arguments, bool elevate)
{
  if (elevate)
    printf("Would call elevated '", path);
  else
    printf("Would call '%s", path);

  while (*arguments) {
    printf(" %s", *arguments);
    arguments++;
  }

  puts("'");
}
