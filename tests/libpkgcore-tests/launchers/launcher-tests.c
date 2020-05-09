#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>
#include <launchers/launcher.h>

#if _WIN32
#  include <tchar.h>
#endif

extern size_t get_total_length(const char **arguments);

void should_return_length_of_single_item(void **state)
{
  (void)state;
  const char *t[] = {"This is a test array", NULL};
  size_t expected = strlen(t[0]) + 1;

  size_t actual = get_total_length(t);

  assert_int_equal(actual, expected);
}

void should_return_length_of_multiple_items(void **state)
{
  (void)state;
  const char *t[] = {
      "This is test item #1",
      "THis is test item #2",
      "And what is this?",
      NULL,
  };
  size_t expected = strlen(t[0]) + strlen(t[1]) + strlen(t[2]) + 3;

  size_t actual = get_total_length(t);

  assert_int_equal(actual, expected);
}

#if _WIN32
extern void combine_to_string(TCHAR *buffer, const char **arguments);

void should_concat_string_array(void **state)
{
  (void)state;
  const char *t[] = {
      "This is",
      "a string",
      NULL,
  };
  const TCHAR *expected = _T("This is a string");
  TCHAR actual[1000]    = _T("");

  combine_to_string(actual, t);

  assert_string_equal(actual, expected);
}
#endif

int main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(should_return_length_of_single_item),
    cmocka_unit_test(should_return_length_of_multiple_items),
#if _WIN32
    cmocka_unit_test(should_concat_string_array),
#endif
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
