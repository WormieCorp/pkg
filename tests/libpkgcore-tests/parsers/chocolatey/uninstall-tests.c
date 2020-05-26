#include <cmocka.h>
#include <parsers/choco-parser.h>
#include <pkg-data.h>

void choco_should_support_uninstall_with_package_option(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
  assert_true(data->confirm);

  release_arguments_data(data);
}

void choco_should_set_help_with_uninstall_alone(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void choco_should_support_uninstall_help_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "--help",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_help_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "-h",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_help_questionmark_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "-?",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_verbose_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "--verbose",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_verbose_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "-v",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_debug_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "--debug",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_debug_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "-d",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_yes_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "--yes",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_confirm_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "--confirm",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_yes_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "-y",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_remove_dependencies_long_arguments(
    void **state)
{
  (void)state;
  char *longArgs[] = {
      "--forcedependencies",
      "--force-dependencies",
      "--removedependencies",
      "--remove-dependencies",
  };
  size_t argLen = sizeof(longArgs) / sizeof(char *);

  for (size_t i = 0; i < argLen; ++i) {
    char *argv[3] = {
        "uninstall",
        "pkg",
    };
    argv[2] = *(longArgs + i);

    ArgumentsData *data =
        choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

    assert_non_null(data);
    assert_int_equal(data->action, UNINSTALL);
    assert_int_equal(data->flag, REFRESH_ARG | UNNEEDED_ARG);
    assert_int_equal(data->unparsedArgsCount, 1);

    release_arguments_data(data);
  }
}

void choco_should_support_uninstall_remove_dependencies_short_argument(
    void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "-x",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | UNNEEDED_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_uninstall_multiple_short_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "-x",
      "pkg",
      "-dv",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->flag,
                   REFRESH_ARG | UNNEEDED_ARG | VERBOSE_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_save_unsupported_arguments_for_uninstall(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall", "pkg", "--x86", "--ia", "/SOMETHING",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->unparsedArgsCount, 4);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);
  assert_string_equal(data->unparsedArgs[3], argv[4]);

  release_arguments_data(data);
}

void choco_should_allow_uninstalling_multiple_packages(void **state)
{
  (void)state;
  char *argv[] = {
      "uninstall",
      "pkg",
      "choco",
      "winget",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, UNINSTALL);
  assert_int_equal(data->unparsedArgsCount, 3);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);

  release_arguments_data(data);
}
