#include <cmocka.h>
#include <parsers/choco-parser.h>
#include <pkg-data.h>

void choco_should_support_info_with_package_option(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_set_info_help_on_no_package(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void choco_should_support_info_help_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
      "--help",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_info_help_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
      "-h",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_info_help_questionmark_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
      "-?",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_info_verbose_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
      "--verbose",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_info_verbose_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
      "-v",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_info_debug_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
      "--debug",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_info_debug_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
      "-d",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_info_local_only_long_argument(void **state)
{
  (void)state;
  char *longArgs[] = {
      "--lo",
      "--local",
      "--localonly",
      "--local-only",
  };
  size_t lCount = sizeof(longArgs) / sizeof(char *);
  for (size_t i = 0; i < lCount; ++i) {
    char *argv[2] = {
        "info",
    };
    argv[1] = *(longArgs + i);

    ArgumentsData *data =
        choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

    assert_non_null(data);
    assert_int_equal(data->action, INFO);
    assert_int_equal(data->flag, LOCALONLY_ARG);
    assert_int_equal(data->unparsedArgsCount, 0);

    release_arguments_data(data);
  }
}

void choco_should_support_info_local_only_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "-l",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void choco_should_support_info_multiple_long_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "info", "pkg", "--verbose", "--debug", "--local-only",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, LOCALONLY_ARG | VERBOSE_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_support_info_multiple_short_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "-l",
      "pkg",
      "-dv",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->flag, LOCALONLY_ARG | VERBOSE_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_save_unsupported_arguments_for_info(void **state)
{
  (void)state;
  char *argv[] = {
      "info", "pkg", "--x86", "--ia", "/SOMETHING",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->unparsedArgsCount, 4);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);
  assert_string_equal(data->unparsedArgs[3], argv[4]);

  release_arguments_data(data);
}

void choco_should_allow_infoing_multiple_packages(void **state)
{
  (void)state;
  char *argv[] = {
      "info",
      "pkg",
      "choco",
      "winget",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, INFO);
  assert_int_equal(data->unparsedArgsCount, 3);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);

  release_arguments_data(data);
}
