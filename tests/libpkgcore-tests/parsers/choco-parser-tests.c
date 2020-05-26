#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>

#include "chocolatey/install-tests.c"
#include "chocolatey/upgrade-tests.c"

int main(void)
{
  const struct CMUnitTest parser_tests[] = {
      cmocka_unit_test(choco_should_support_install_with_package_option),
      cmocka_unit_test(choco_should_set_help_with_install_alone),
      cmocka_unit_test(choco_should_support_install_help_long_argument),
      cmocka_unit_test(choco_should_support_install_help_short_argument),
      cmocka_unit_test(choco_should_support_install_help_questionmark_argument),
      cmocka_unit_test(choco_should_support_install_verbose_long_argument),
      cmocka_unit_test(choco_should_support_install_verbose_short_argument),
      cmocka_unit_test(choco_should_support_install_verbose_long_argument),
      cmocka_unit_test(choco_should_support_install_verbose_short_argument),
      cmocka_unit_test(choco_should_support_instal_yes_long_argument),
      cmocka_unit_test(choco_should_support_instal_confirm_long_argument),
      cmocka_unit_test(choco_should_support_instal_yes_short_argument),
      cmocka_unit_test(choco_should_support_install_no_progress_long_argument),
      cmocka_unit_test(
          choco_should_support_install_ignoredependencies_long_argument),
      cmocka_unit_test(
          choco_should_support_install_ignore_dependencies_long_argument),
      cmocka_unit_test(
          choco_should_support_install_ignoredependencies_short_argument),
      cmocka_unit_test(choco_should_support_install_multiple_long_arguments),
      cmocka_unit_test(choco_should_support_install_multiple_short_arguments),
      cmocka_unit_test(choco_should_save_unsupported_arguments),
      cmocka_unit_test(choco_should_allow_installing_multiple_packages),

      cmocka_unit_test(choco_should_support_upgrade_with_package_option),
      cmocka_unit_test(choco_should_set_help_with_upgrade_alone),
      cmocka_unit_test(choco_should_not_set_all_as_packagename_during_upgrade),
      cmocka_unit_test(choco_should_support_upgrade_help_long_argument),
      cmocka_unit_test(choco_should_support_upgrade_help_short_argument),
      cmocka_unit_test(choco_should_support_upgrade_help_questionmark_argument),
      cmocka_unit_test(choco_should_support_upgrade_verbose_long_argument),
      cmocka_unit_test(choco_should_support_upgrade_verbose_short_argument),
      cmocka_unit_test(choco_should_support_upgrade_verbose_long_argument),
      cmocka_unit_test(choco_should_support_upgrade_verbose_short_argument),
      cmocka_unit_test(choco_should_support_upgrade_yes_long_argument),
      cmocka_unit_test(choco_should_support_upgrade_confirm_long_argument),
      cmocka_unit_test(choco_should_support_upgrade_yes_short_argument),
      cmocka_unit_test(choco_should_support_upgrade_no_progress_long_argument),
      cmocka_unit_test(
          choco_should_support_upgrade_ignoredependencies_long_argument),
      cmocka_unit_test(
          choco_should_support_upgrade_ignore_dependencies_long_argument),
      cmocka_unit_test(
          choco_should_support_upgrade_ignoredependencies_short_argument),
      cmocka_unit_test(choco_should_support_upgrade_multiple_long_arguments),
      cmocka_unit_test(choco_should_support_upgrade_multiple_short_arguments),
      cmocka_unit_test(choco_should_save_unsupported_arguments_for_upgrade),
      cmocka_unit_test(choco_should_allow_upgrading_multiple_packages),
  };

  return cmocka_run_group_tests(parser_tests, NULL, NULL);
}
