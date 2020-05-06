#include <cmocka.h>
#include <parsers/parsers.h>

void should_set_help_flag_on_no_action(void **state)
{
  (void)state;
  char *argv[] = {
      "-h",
  };
  int argc = 1;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, NO_ACTION);
  assert_int_equal(data->flag, HELP_ARG);
  release_arguments_data(data);
}

void should_set_help_flag_on_no_action_long(void **state)
{
  (void)state;
  char *argv[] = {
      "--help",
  };
  int argc = 1;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, NO_ACTION);
  assert_int_equal(data->flag, HELP_ARG);
  release_arguments_data(data);
}

void should_set_help_flag_on_install_action(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "-h",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  release_arguments_data(data);
}

void should_set_help_flag_on_install_action_long(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "--help",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  release_arguments_data(data);
}

void should_set_help_flag_on_upgrade_action(void **state)
{
  (void)state;
  char *argv[] = {
      "-Su",
      "-h",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, HELP_ARG);
  release_arguments_data(data);
}

void should_set_help_flag_on_upgrade_action_long(void **state)
{
  (void)state;
  char *argv[] = {
      "-Su",
      "--help",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, HELP_ARG);
  release_arguments_data(data);
}
