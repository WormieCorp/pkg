#include <cmocka.h>
#include <parsers/parsers.h>

void should_set_localonly_as_true(void **state)
{
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Q",
      "pkg",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, NO_ACTION);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  release_arguments_data(data);
}
