#include <cmocka.h>
#include <parsers/pacman-parser.h>

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

void should_set_recursive_flag(void **state)
{
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Rs",
      "pkg",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, RECURSE_ARG);
  release_arguments_data(data);
}

void should_set_recursive_flag_long(void **state)
{
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-R",
      "pkg",
      "--recursive",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, RECURSE_ARG);
  release_arguments_data(data);
}

void should_set_unneeded_flag(void **state)
{
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Ru",
      "pkg",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, UNNEEDED_ARG);
  release_arguments_data(data);
}

void should_set_unneeded_flag_long(void **state)
{
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-R",
      "pkg",
      "--unneeded",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, UNNEEDED_ARG);
  release_arguments_data(data);
}

void should_set_no_save_flag(void **state)
{
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Rn",
      "pkg",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, NO_SAVE_ARG);
  release_arguments_data(data);
}

void should_set_no_save_flag_long(void **state)
{
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-R",
      "pkg",
      "--nosave",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, NO_SAVE_ARG);
  release_arguments_data(data);
}
