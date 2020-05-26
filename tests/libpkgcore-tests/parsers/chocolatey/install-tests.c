#include <cmocka.h>
#include <parsers/choco-parser.h>
#include <pkg-data.h>

void choco_should_support_install_with_package_option(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
  assert_true(data->confirm);

  release_arguments_data(data);
}

void choco_should_set_help_with_install_alone(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void choco_should_support_install_help_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "--help",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_help_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "-h",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_help_questionmark_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "-?",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_verbose_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "--verbose",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_verbose_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "-v",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_debug_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "--debug",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_debug_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "-d",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_instal_yes_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "--yes",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_instal_confirm_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "--confirm",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_instal_yes_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "-y",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_no_progress_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "--no-progress",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | HIDE_PROGRESS_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_ignoredependencies_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "--ignoredependencies",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | NODEP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_ignore_dependencies_long_argument(
    void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "--ignore-dependencies",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | NODEP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_ignoredependencies_short_argument(
    void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "-i",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | NODEP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_install_multiple_long_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "install", "pkg", "--yes", "--ignore-dependencies", "--no-progress",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag, REFRESH_ARG | NODEP_ARG | HIDE_PROGRESS_ARG);
  assert_false(data->confirm);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_support_install_multiple_short_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "-i",
      "pkg",
      "-dv",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->flag,
                   REFRESH_ARG | NODEP_ARG | VERBOSE_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_save_unsupported_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "install", "pkg", "--x86", "--ia", "/SOMETHING",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->unparsedArgsCount, 4);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);
  assert_string_equal(data->unparsedArgs[3], argv[4]);

  release_arguments_data(data);
}

void choco_should_allow_installing_multiple_packages(void **state)
{
  (void)state;
  char *argv[] = {
      "install",
      "pkg",
      "choco",
      "winget",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INSTALL);
  assert_int_equal(data->unparsedArgsCount, 3);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);

  release_arguments_data(data);
}
