#include <cmocka.h>
#include <parsers/pacman-parser.h>

void should_set_list_action_and_localonly_flag(void **state)
{
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Q",
      "pkg",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  release_arguments_data(data);
}

void should_set_upgrade_action_and_localonly_flag(void **state)
{
  (void)state;
  char *argv[] = {"-Qu"};
  int argc     = 1;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void should_set_upgrade_action_and_localonly_flag_long(void **state)
{
  (void)state;
  char *argv[] = {
      "-Q",
      "--upgrades",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void should_not_set_upgrade_action_with_sync_long_option(void **state)
{
  (void)*state;
  char *argv[] = {
      "-Q",
      "--sysupgrade",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  release_arguments_data(data);
}

void should_not_set_refresh_flag_when_local_only(void **state)
{
  (void)*state;
  char *argv[] = {"-Qy"};
  int argc     = 1;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  release_arguments_data(data);
}

void should_not_set_refresh_flag_when_local_only_long(void **state)
{
  (void)*state;
  char *argv[] = {
      "-Q",
      "--refresh",
  };
  int argc = 2;

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  release_arguments_data(data);
}

void should_set_info_action_with_localonly_flag(void **state)
{
  (void)state;
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Qi",
      "pkg",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_info_action_with_localonly_flag_long(void **state)
{
  (void)state;
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-Q",
      "pkg",
      "--info",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_search_action_with_localonly_flag(void **state)
{
  (void)state;
  (void)state;
  int argc     = 2;
  char *argv[] = {
      "-Qs",
      "what",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, SEARCH);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void should_set_search_action_with_localonly_flag_long(void **state)
{
  (void)state;
  (void)state;
  int argc     = 3;
  char *argv[] = {
      "-Q",
      "what",
      "--search",
  };

  ArgumentsData *data = pacman_parse_arguments(argc, argv);

  assert_non_null(data);
  assert_int_equal(data->action, SEARCH);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}
