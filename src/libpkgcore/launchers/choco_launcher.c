#include "choco_launcher.h"
#include "../resolver.h"
#include "../transformers/choco-transformer.h"
#include "launcher.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

bool choco_launch_program(const ArgumentsData *data)
{
  char *program = get_program_from_path("choco.exe");
  if (!program) {
    program = get_program_from_environment("ChocolateyInstall", 2,
                                           "bin/choco.exe", "choco.exe");
  }
  if (!program)
    return false;

  char **arguments = choco_transform_arguments(data);

  if (!arguments) {
    const char *newArgs[] = {"--help", NULL};
    launch_program(program, newArgs, false);
  } else {
    bool elevate =
        compare_helper(arguments[0], 3, "install", "uninstall", "upgrade");
    int i = -1;
    while (elevate && arguments[++i]) {
      if (compare_helper(arguments[i], 2, "-h", "--help"))
        elevate = false;
    }

    launch_program(program, arguments, elevate);
    free(arguments);
  }
  free(program);

  return true;
}
