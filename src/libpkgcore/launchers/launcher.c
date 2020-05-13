#include "launcher.h"
#include "../logging.h"
#include "../resolver.h"
#include "choco_launcher.h"
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

bool compare_helper(const char *argument, int count, ...)
{
  if (argument == NULL)
    return false;

  va_list ap;
  va_start(ap, count);

  for (int i = 0; i < count; i++) {
    if (strcmp(argument, va_arg(ap, char *)) == 0)
      return true;
  }

  return false;
}

PKGCORE_EXPORT void execute_package_manager(const ArgumentsData *data)
{
#define LAUNCHERS_COUNT 2
  bool (*launchers[LAUNCHERS_COUNT])(const ArgumentsData *) = {
      choco_launch_program,
  };

  bool success = false;

  for (int i = 0; i < LAUNCHERS_COUNT; ++i) {
    if (launchers[i](data)) {
      success = true;
      break;
    }
  }

  if (!success) {
    log_error("No supported package manager was found to be installed.\n");
  }
}

PKGCORE_EXPORT size_t get_total_length(const char **arguments)
{
  int i        = 0;
  size_t count = 0;

  while (*(arguments + i)) {
    count += strlen(*(arguments + i)) + 1;
    i++;
  }

  count++; // Just to make sure we at least have a null terminator

  count += (i * 2); // To make room if we need to quote strings

  return count;
}
