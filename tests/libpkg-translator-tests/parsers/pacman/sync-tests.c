#include <cmocka.h>
#include <parsers/parsers.h>

void should_set_info_action(void **state)
{
  (void)state;
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Si",
      "pkg",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_info_action_long(void **state)
{
  (void)state;
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-S",
      "pkg",
      "--info",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_list_action(void **state)
{
  (void)state;
  (void)state;
  int argc     = 1;
  char *argv[] = {"-Sl"};

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void should_set_list_action_long(void **state)
{
  (void)state;
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-S",
      "--list",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}
