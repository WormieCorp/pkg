#include "resolver.h"
#include "config.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if HAVE_ALLOCA_H
#  include <alloca.h>
#elif HAVE_MALLOC_H
#  include <malloc.h>
#endif
#if HAVE_SYS_STAT_H
#  include <sys/stat.h>
#endif

bool file_exists(const char *path);

PKGCORE_EXPORT char *
get_program_from_environment(const char *environmentVariable, int count, ...)
{
  char buf[1000]; // Temporary buffer
  char *envPath = getenv(environmentVariable);
  if (!envPath)
    return NULL;

  va_list ap;
  va_start(ap, count);

  for (int i = 0; i < count; ++i) {
    char *name = va_arg(ap, char *);
    if (!name)
      continue;

    snprintf(buf, sizeof(buf), "%s/%s", envPath, name);
    if (file_exists(buf))
      return STRDUP(buf);
  }

  return NULL;
}

char *get_program_from_path(const char *executable)
{
#if _WIN32
  const char *delim = ";";
#else
  const char *delim = ":";
#endif

  char buf[1000]; // Temporary buffer
  char *paths = getenv("PATH");
  // We need to create a copy of the paths environment variable
  // as strtok changes the string.
  char *pathCpy = alloca((strlen(paths) + 1) * sizeof(char));
  strcpy(pathCpy, paths);
  char *ptr   = NULL;
  char *token = STRTOK(pathCpy, delim, &ptr);

  while (token) {
    snprintf(buf, sizeof(buf), "%s/%s", token, executable);
    if (file_exists(buf))
      return STRDUP(buf);

    token = STRTOK(NULL, delim, &ptr);
  }

  return NULL;
}

bool file_exists(const char *path)
{
#if HAVE_STAT
  struct stat sb;
  return !stat(path, &sb) && (sb.st_mode & S_IFREG) == S_IFREG;
#else
  FILE *f           = fopen(buf, "r");
  if (f) {
    fclose(f);
    return true;
  }
  return false;
#endif
}
