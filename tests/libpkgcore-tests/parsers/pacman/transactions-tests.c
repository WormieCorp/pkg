#include <cmocka.h>
#include <parsers/parsers.h>

void should_be_null_on_unsupported_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "spotify",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_null(data);
  release_arguments_data(data);
}

void should_set_install_action(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
  };
  int argc = 1;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  release_arguments_data(data);
}

void should_set_single_package_for_install_action(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "brave",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->unparsedArgsCount, 1);
  assert_string_equal(data->unparsedArgs[0], argv[1]);

  release_arguments_data(data);
}

void should_set_upgrade_action_and_refresh_flag(void **state)
{
  (void)state;
  char *argv[] = {"-Syu"};
  int argc     = 1;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void should_set_install_action_with_nodeps_flag(void **state)
{
  (void)state;
  char *argv[] = {
      "-Sd",
      "cmake",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, NODEP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_install_with_verbose_flag(void **state)
{
  (void)state;
  char *argv[] = {
      "-Sv",
      "pkg",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_install_with_verbose_flag_long(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "pkg",
      "--verbose",
  };
  int argc = 3;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_install_with_debug_flag_long(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "pkg",
      "--debug",
  };
  int argc = 3;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_unsupported_argument_as_unparsed_arg(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "pkg",
      "--ia=\"/DIR=C:\\Test\"",
  };
  int argc = 3;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->unparsedArgsCount, 2);

  release_arguments_data(data);
}

void should_set_install_and_no_progress_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "pkg",
      "--noprogressbar",
  };
  int argc = 3;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, HIDE_PROGRESS_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_install_and_confirm_as_false(void **state)
{
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-S",
      "pkg",
      "--noconfirm",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_install_and_nodeps_flag_long(void **state)
{
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-S",
      "pkg",
      "--nodeps",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, NODEP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}
