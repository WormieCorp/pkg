#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>

#include "chocolatey/install-tests.c"

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
  };

  return cmocka_run_group_tests(parser_tests, NULL, NULL);
}
