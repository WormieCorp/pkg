#ifndef _HAVE_TESTS_HELPER_H
#define _HAVE_TESTS_HELPER_H

#include "config.h"
#include <cmocka.h>
#include <pkg-data.h>
#if HAVE_MALLOC_H
#  include <malloc.h>
#else
// We will assume that free is in stdlib
#  include <stdlib.h>
#endif

void add_unparsed_packages(const char **expected, ArgumentsData *data)
{
  data->unparsedArgs = malloc(data->unparsedArgsCount * sizeof(char *));
  for (int i = 0; i < data->unparsedArgsCount && *(expected + i); ++i) {
    data->unparsedArgs[i] = (char *)expected[i];
  }
}

void compare_helper(const char **expected, int expectedCount, char **actual)
{
  assert_non_null(actual);

  int i      = 0;
  char **pos = actual;
  for (; i < expectedCount && *pos; i++, *pos++) {
    assert_string_equal(*pos, *(expected + i));
    free(*pos);
  }

  while (*pos) {
    i++;
    free(*pos);
    pos++;
  }

  free(actual);

  assert_int_equal(i, expectedCount);
}

#endif /* _HAVE_TESTS_HELPER_H */
