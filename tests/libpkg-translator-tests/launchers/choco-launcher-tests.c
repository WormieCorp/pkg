#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>

#include "choco/installation-tests.c"
#include "choco/upgrade-tests.c"

void should_set_help_argument_on_no_action(void **state)
{
  (void)state;
  ArgumentsData data = {
      .action = NO_ACTION,
  };
  char *expected[] = {
      "--help",
      NULL,
  };

  char **actual = choco_get_launch_args(&data);

  compare_helper(expected, 1, actual);
}

int main(void)
{
  const struct CMUnitTest parser_tests[] = {
      cmocka_unit_test(should_set_help_argument_on_no_action),
      cmocka_unit_test(should_set_install_and_help_arguments),
      cmocka_unit_test(should_set_install_and_package_arguments),
      cmocka_unit_test(should_set_install_and_non_package_arguments),
      cmocka_unit_test(should_set_install_and_nodependencies_arguments),
      cmocka_unit_test(should_set_install_and_verbose_arguments),
      cmocka_unit_test(should_set_install_and_debug_arguments),
      cmocka_unit_test(should_set_install_verbose_and_debug_arguments),
      cmocka_unit_test(should_set_install_yes_and_allow_license_arguments),
      cmocka_unit_test(should_set_install_and_no_progress_arguments),
      cmocka_unit_test(should_set_upgrade_all_when_upgrade_and_no_unparsed),
      cmocka_unit_test(should_set_upgrade_with_package_arguments),
      cmocka_unit_test(should_set_upgrade_all_when_upgrade_and_no_unparsed),
      cmocka_unit_test(
          should_set_upgrade_with_package_and_non_package_arguments),
      cmocka_unit_test(should_set_upgrade_and_verbose_arguments),
      cmocka_unit_test(should_set_upgrade_and_debug_arguments),
      cmocka_unit_test(should_set_upgrade_verbose_and_debug_arguments),
      cmocka_unit_test(should_set_upgrade_yes_and_allow_license_arguments),
      cmocka_unit_test(should_set_upgrade_and_no_progress_arguments),
  };

  return cmocka_run_group_tests(parser_tests, NULL, NULL);
}
