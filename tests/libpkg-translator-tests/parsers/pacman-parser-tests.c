#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>
#include <parsers/parsers.h>

#include "pacman/help-tests.c"
#include "pacman/sync-tests.c"
#include "pacman/transactions-tests.c"

int main(void)
{
  const struct CMUnitTest parser_tests[] = {
      cmocka_unit_test(should_set_help_flag_on_no_action),
      cmocka_unit_test(should_set_help_flag_on_no_action_long),
      cmocka_unit_test(should_set_help_flag_on_install_action),
      cmocka_unit_test(should_set_help_flag_on_install_action_long),
      cmocka_unit_test(should_set_help_flag_on_upgrade_action),
      cmocka_unit_test(should_set_help_flag_on_upgrade_action_long),
      cmocka_unit_test(should_be_null_on_unsupported_arguments),
      cmocka_unit_test(should_set_unsupported_argument_as_unparsed_arg),
      cmocka_unit_test(should_set_install_action),
      cmocka_unit_test(should_set_single_package_for_install_action),
      cmocka_unit_test(should_set_upgrade_action),
      cmocka_unit_test(should_set_refresh_flag),
      cmocka_unit_test(should_set_upgrade_action_and_refresh_flag),
      cmocka_unit_test(should_set_install_action_with_nodeps_flag),
      cmocka_unit_test(should_set_install_with_verbose_flag),
      cmocka_unit_test(should_set_install_with_verbose_flag_long),
      cmocka_unit_test(should_set_install_with_debug_flag_long),
      cmocka_unit_test(should_set_install_and_no_progress_arguments),
      cmocka_unit_test(should_set_install_and_confirm_as_false),
      cmocka_unit_test(should_set_install_and_nodeps_flag_long),
      cmocka_unit_test(should_set_info_action),
      cmocka_unit_test(should_set_info_action_long),
  };

  return cmocka_run_group_tests(parser_tests, NULL, NULL);
}
