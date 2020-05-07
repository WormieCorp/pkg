#include <cmocka.h>
#include <parsers/parsers.h>

void should_set_remove_operation(void **state)
{
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-R",
      "pkg",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  release_arguments_data(data);
}
