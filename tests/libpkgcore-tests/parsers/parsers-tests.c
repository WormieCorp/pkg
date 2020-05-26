#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>
#include <parsers/parsers.h>

void parsers_can_parse_single_action_argument(void **state)
{
  (void)state;
  ArgumentsData *actual = calloc(1, sizeof(ArgumentsData));

  struct ParserData parserData[1] = {
      {
          .type      = {.action = INSTALL},
          .longArgs  = "install",
          .unionType = ACTION,
      },
  };

  const char *argv[] = {
      "install",
  };

  bool result = execute_parsing(actual, parserData, 1, 1, argv);

  assert_true(result);
  assert_int_equal(actual->action, INSTALL);

  release_arguments_data(actual);
}

void parsers_can_parse_single_action_with_packages(void **state)
{
  (void)state;
  ArgumentsData *actual = calloc(1, sizeof(ArgumentsData));

  struct ParserData parserData[1] = {
      {
          .type      = {.action = INSTALL},
          .longArgs  = "install",
          .unionType = ACTION,
      },
  };

  const char *argv[] = {
      "install",
      "pkg",
  };

  bool result = execute_parsing(actual, parserData, 1, 2, argv);

  assert_true(result);
  assert_int_equal(actual->action, INSTALL);
  assert_int_equal(actual->unparsedArgsCount, 1);
  assert_string_equal(*(actual->unparsedArgs), argv[1]);

  release_arguments_data(actual);
}

void parsers_can_parse_multiple_long_arguments(void **state)
{
  (void)state;
  ArgumentsData *actual = calloc(1, sizeof(ArgumentsData));

  struct ParserData parserData[] = {
      {
          .type      = {.action = UPGRADE},
          .longArgs  = "upgrade",
          .unionType = ACTION,
      },
      {
          .type      = {.flag = NODEP_ARG},
          .longArgs  = "--ignore-dependencies",
          .unionType = FLAG,
      },
      {
          .type      = {.confirm = false},
          .longArgs  = "--yes",
          .unionType = CONFIRM,
      },
  };

  const char *argv[] = {
      "upgrade",
      "pkg",
      "--ignore-dependencies",
      "--yes",
  };

  bool result = execute_parsing(actual, parserData, 3, 4, argv);

  assert_true(result);
  assert_int_equal(actual->action, UPGRADE);
  assert_int_equal(actual->flag, NODEP_ARG);
  assert_false(actual->confirm);
  assert_int_equal(actual->unparsedArgsCount, 1);

  release_arguments_data(actual);
}

void parsers_can_parse_single_short_action_argument(void **state)
{
  (void)state;
  ArgumentsData *actual = calloc(1, sizeof(ArgumentsData));

  struct ParserData parserData[1] = {
      {
          .type       = {.action = INSTALL},
          .singleArgs = "S",
          .unionType  = ACTION,
      },
  };

  const char *argv[] = {
      "-S",
  };

  bool result = execute_parsing(actual, parserData, 1, 1, argv);

  assert_true(result);
  assert_int_equal(actual->action, INSTALL);

  release_arguments_data(actual);
}

void parsers_can_parse_single_short_action_with_packages(void **state)
{
  (void)state;
  ArgumentsData *actual = calloc(1, sizeof(ArgumentsData));

  struct ParserData parserData[1] = {
      {
          .type       = {.action = INSTALL},
          .singleArgs = "S",
          .unionType  = ACTION,
      },
  };

  const char *argv[] = {
      "-S",
      "pkg",
  };

  bool result = execute_parsing(actual, parserData, 1, 2, argv);

  assert_true(result);
  assert_int_equal(actual->action, INSTALL);
  assert_int_equal(actual->unparsedArgsCount, 1);
  assert_string_equal(*(actual->unparsedArgs), argv[1]);

  release_arguments_data(actual);
}

void parsers_can_parse_muliple_short_action_with_flags(void **state)
{
  (void)state;
  ArgumentsData *actual = calloc(1, sizeof(ArgumentsData));

  struct ParserData parserData[] = {
      {
          .type       = {.action = INSTALL},
          .singleArgs = "S",
          .unionType  = ACTION,
      },
      {
          .type       = {.action = UPGRADE},
          .singleArgs = "u",
          .unionType  = ACTION,
      },
      {
          .type       = {.flag = REFRESH_ARG},
          .singleArgs = "y",
          .unionType  = FLAG,
      },
  };

  const char *argv[] = {
      "-Syu",
  };

  bool result = execute_parsing(actual, parserData, 3, 1, argv);

  assert_true(result);
  assert_int_equal(actual->action, UPGRADE);
  assert_int_equal(actual->flag, REFRESH_ARG);

  release_arguments_data(actual);
}

void parsers_can_parse_with_multi_single_args(void **state)
{
  (void)state;

  ArgumentsData *actual1 = calloc(1, sizeof(ArgumentsData));
  ArgumentsData *actual2 = calloc(1, sizeof(ArgumentsData));

  struct ParserData parserData[] = {
      {
          .type       = {.flag = HELP_ARG},
          .singleArgs = "h?",
          .unionType  = FLAG,
      },
  };

  const char *argv1[] = {
      "-h",
  };
  const char *argv2[] = {
      "-?",
  };

  assert_true(execute_parsing(actual1, parserData, 1, 1, argv1));
  assert_int_equal(actual1->flag, HELP_ARG);

  assert_true(execute_parsing(actual2, parserData, 1, 1, argv2));
  assert_int_equal(actual2->flag, HELP_ARG);
}

void parsers_can_parse_with_multi_long_args(void **state)
{
  (void)state;

  ArgumentsData *actual1 = calloc(1, sizeof(ArgumentsData));
  ArgumentsData *actual2 = calloc(1, sizeof(ArgumentsData));

  struct ParserData parserData[] = {
      {
          .type      = {.flag = NODEP_ARG},
          .longArgs  = "--ignoredependencies|--ignore-dependencies",
          .unionType = FLAG,
      },
  };

  const char *argv1[] = {
      "--ignoredependencies",
  };
  const char *argv2[] = {
      "--ignore-dependencies",
  };

  assert_true(execute_parsing(actual1, parserData, 1, 1, argv1));
  assert_int_equal(actual1->flag, NODEP_ARG);

  assert_true(execute_parsing(actual2, parserData, 1, 1, argv2));
  assert_int_equal(actual2->flag, NODEP_ARG);
}

int main(void)
{
  const struct CMUnitTest parser_tests[] = {
      cmocka_unit_test(parsers_can_parse_single_action_argument),
      cmocka_unit_test(parsers_can_parse_single_action_with_packages),
      cmocka_unit_test(parsers_can_parse_single_short_action_argument),
      cmocka_unit_test(parsers_can_parse_single_short_action_with_packages),
      cmocka_unit_test(parsers_can_parse_multiple_long_arguments),
      cmocka_unit_test(parsers_can_parse_muliple_short_action_with_flags),
      cmocka_unit_test(parsers_can_parse_with_multi_single_args),
      cmocka_unit_test(parsers_can_parse_with_multi_long_args),
  };

  return cmocka_run_group_tests(parser_tests, NULL, NULL);
}
