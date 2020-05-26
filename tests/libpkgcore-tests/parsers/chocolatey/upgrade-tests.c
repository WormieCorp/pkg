#include <cmocka.h>
#include <parsers/choco-parser.h>
#include <pkg-data.h>

void choco_should_support_upgrade_with_package_option(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
  assert_true(data->confirm);

  release_arguments_data(data);
}

void choco_should_set_help_with_upgrade_alone(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void choco_should_not_set_all_as_packagename_during_upgrade(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "all",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void choco_should_support_upgrade_help_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "--help",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_help_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "-h",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_help_questionmark_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "-?",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_verbose_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "--verbose",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_verbose_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "-v",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_debug_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "--debug",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_debug_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "-d",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_yes_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "--yes",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_confirm_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "--confirm",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_yes_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "-y",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_no_progress_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "--no-progress",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | HIDE_PROGRESS_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_ignoredependencies_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "--ignoredependencies",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | NODEP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_ignore_dependencies_long_argument(
    void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "--ignore-dependencies",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | NODEP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_ignoredependencies_short_argument(
    void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "-i",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | NODEP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_upgrade_multiple_long_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade", "pkg", "--yes", "--ignore-dependencies", "--no-progress",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag, REFRESH_ARG | NODEP_ARG | HIDE_PROGRESS_ARG);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_support_upgrade_multiple_short_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "-i",
      "pkg",
      "-dv",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->flag,
                   REFRESH_ARG | NODEP_ARG | VERBOSE_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_save_unsupported_arguments_for_upgrade(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade", "pkg", "--x86", "--ia", "/SOMETHING",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->unparsedArgsCount, 4);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);
  assert_string_equal(data->unparsedArgs[3], argv[4]);

  release_arguments_data(data);
}

void choco_should_allow_upgrading_multiple_packages(void **state)
{
  (void)state;
  char *argv[] = {
      "upgrade",
      "pkg",
      "choco",
      "winget",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UPGRADE);
  assert_int_equal(data->unparsedArgsCount, 3);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);

  release_arguments_data(data);
}
