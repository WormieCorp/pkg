#include "resolver.h"
#include "config.h"
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

char *get_program_from_path(const char *executable)
{
  char buf[1000]; // Temporary buffer
  char *paths = getenv("PATH");
  // We need to create a copy of the paths environment variable
  // as strtok changes the string.
  char *pathCpy = alloca((strlen(paths) + 1) * sizeof(char));
  strcpy(pathCpy, paths);
  char *ptr = NULL;
#if _WIN32
  const char *delim    = ";";
  const char pathDelim = '\\';
#else
  const char *delim    = ":";
  const char pathDelim = '/';
#endif
  char *token = STRTOK(pathCpy, delim, &ptr);

  while (token) {
    snprintf(buf, sizeof(buf), "%s%c%s", token, pathDelim, executable);
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
  FILE *f              = fopen(buf, "r");
  if (f) {
    fclose(f);
    return true;
  }
  return false;
#endif
}
