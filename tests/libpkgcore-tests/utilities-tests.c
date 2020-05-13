#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>

#include "utilities.h"

void should_compare_single_value(void **state)
{
  (void)state;
  int index = string_to_index("install", "install");

  assert_int_equal(index, 0);
}

void should_not_compare_single_value(void **state)
{
  (void)state;
  int index = string_to_index("uninstall", "install");

  assert_int_equal(index, -1);
}

void should_not_compare_null_value(void **state)
{
  (void)state;
  int index = string_to_index(NULL, "install");

  assert_int_equal(index, -1);
}

void should_not_compare_null_token_value(void **state)
{
  (void)state;
  int index = string_to_index("install", NULL);

  assert_int_equal(index, -1);
}

void should_compare_on_null_value_and_null_token_value(void **state)
{
  (void)state;
  int index = string_to_index(NULL, NULL);

  assert_int_equal(index, 0);
}

void should_compare_on_multi_values(void **state)
{
  (void)state;
  int index = string_to_index("uninstall", "install|upgrade|uninstall");

  assert_int_equal(index, 2);
}

int main(void)
{
  const struct CMUnitTest parser_tests[] = {
      cmocka_unit_test(should_compare_single_value),
      cmocka_unit_test(should_not_compare_single_value),
      cmocka_unit_test(should_not_compare_null_value),
      cmocka_unit_test(should_not_compare_null_token_value),
      cmocka_unit_test(should_compare_on_null_value_and_null_token_value),
      cmocka_unit_test(should_compare_on_multi_values),
  };

  return cmocka_run_group_tests(parser_tests, NULL, NULL);
}
