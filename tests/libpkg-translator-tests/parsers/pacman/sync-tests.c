#include <cmocka.h>
#include <parsers/parsers.h>

void should_set_upgrade_action(void **state)
{
  (void)state;
  char *argv[] = {"-Su"};
  int argc     = 1;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, NO_ACTION);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void should_set_upgrade_action_long(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "--sysupgrade",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, NO_ACTION);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void should_set_refresh_flag(void **state)
{
  (void)state;
  char *argv[] = {"-Sy"};
  int argc     = 1;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void should_set_refresh_flag_long(void **state)
{
  (void)state;
  char *argv[] = {
      "-S",
      "--refresh",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

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
  assert_int_equal(data->flag, NO_ACTION);
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
  assert_int_equal(data->flag, NO_ACTION);
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
  assert_int_equal(data->flag, NO_ACTION);
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
  assert_int_equal(data->flag, NO_ACTION);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void should_set_search_action(void **state)
{
  (void)state;
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Ss",
      "what",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, SEARCH);
  assert_int_equal(data->flag, NO_ACTION);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_search_action_long(void **state)
{
  (void)state;
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-S",
      "what",
      "--search",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, SEARCH);
  assert_int_equal(data->flag, NO_ACTION);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}
