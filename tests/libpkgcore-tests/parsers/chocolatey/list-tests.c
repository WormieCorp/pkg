#include <cmocka.h>
#include <parsers/choco-parser.h>
#include <pkg-data.h>

void choco_should_support_list_with_package_option(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_list_without_package_option(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, REFRESH_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void choco_should_support_list_help_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
      "--help",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_list_help_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
      "-h",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_list_help_questionmark_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
      "-?",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, HELP_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_list_verbose_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
      "--verbose",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_list_verbose_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
      "-v",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, REFRESH_ARG | VERBOSE_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_list_debug_long_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
      "--debug",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_list_debug_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
      "-d",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, REFRESH_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);

  release_arguments_data(data);
}

void choco_should_support_list_local_only_long_argument(void **state)
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
        "list",
    };
    argv[1] = *(longArgs + i);

    ArgumentsData *data =
        choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

    assert_non_null(data);
    assert_int_equal(data->action, LIST);
    assert_int_equal(data->flag, LOCALONLY_ARG);
    assert_int_equal(data->unparsedArgsCount, 0);

    release_arguments_data(data);
  }
}

void choco_should_support_list_local_only_short_argument(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "-l",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, LOCALONLY_ARG);
  assert_int_equal(data->unparsedArgsCount, 0);

  release_arguments_data(data);
}

void choco_should_support_list_multiple_long_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "list", "pkg", "--verbose", "--debug", "--local-only",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, LOCALONLY_ARG | VERBOSE_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_support_list_multiple_short_arguments(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "-l",
      "pkg",
      "-dv",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->flag, LOCALONLY_ARG | VERBOSE_ARG | DEBUG_ARG);
  assert_int_equal(data->unparsedArgsCount, 1);
}

void choco_should_save_unsupported_arguments_for_list(void **state)
{
  (void)state;
  char *argv[] = {
      "list", "pkg", "--x86", "--ia", "/SOMETHING",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->unparsedArgsCount, 4);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);
  assert_string_equal(data->unparsedArgs[3], argv[4]);

  release_arguments_data(data);
}

void choco_should_allow_listing_multiple_packages(void **state)
{
  (void)state;
  char *argv[] = {
      "list",
      "pkg",
      "choco",
      "winget",
  };

  ArgumentsData *data =
      choco_parse_arguments(sizeof(argv) / sizeof(char *), argv);

  assert_non_null(data);
  assert_int_equal(data->action, LIST);
  assert_int_equal(data->unparsedArgsCount, 3);
  assert_string_equal(data->unparsedArgs[0], argv[1]);
  assert_string_equal(data->unparsedArgs[1], argv[2]);
  assert_string_equal(data->unparsedArgs[2], argv[3]);

  release_arguments_data(data);
}
