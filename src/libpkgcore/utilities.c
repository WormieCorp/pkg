#include "utilities.h"
#include "config.h"
#include <string.h>
#if HAVE_ALLOCA_H
#  include <alloca.h>
#elif HAVE_MALLOC_H
#  include <malloc.h>
#else
#  include <stdlib.h>
#endif

int string_to_index(const char *value, const char *tokenCompares)
{
  if (value == NULL && tokenCompares == NULL)
    return 0;
  if (value == NULL || tokenCompares == NULL)
    return -1;

  char *tokensCpy = alloca((strlen(tokenCompares) + 1) * sizeof(char));
  strcpy(tokensCpy, tokenCompares);
  char *ptr;
  char *token = STRTOK(tokensCpy, "|", &ptr);
  int index   = 0;
  while (token) {
    if (strcmp(value, token) == 0)
      return index;
    token = STRTOK(NULL, "|", &ptr);
    index++;
  }

  return -1;
}
