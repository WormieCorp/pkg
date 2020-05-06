#include <launchers/choco-launcher.h>
#include <setjmp.h>
#include <stdlib.h>

#include "../helper.h"

void should_set_install_and_help_arguments(void **state)
{
  (void)state;
  ArgumentsData data = {
      .action  = INSTALL,
      .confirm = true,
  };
  char *expected[] = {
      "install",
      "--help",
      NULL,
  };

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 2, actual);
}

void should_set_install_and_package_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "install",
      "googlechrome",
      "brave",
      NULL,
  };
  ArgumentsData data = {
      .action            = INSTALL,
      .confirm           = true,
      .unparsedArgsCount = 2,
  };
  data.unparsedArgs    = alloca(2 * sizeof(char *));
  data.unparsedArgs[0] = expected[1];
  data.unparsedArgs[1] = expected[2];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 3, actual);
}

void should_set_install_and_non_package_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "install",
      "brave",
      "--ia=\"/DIR=D:\\Someplace\"",
      NULL,
  };
  ArgumentsData data = {
      .action            = INSTALL,
      .confirm           = true,
      .unparsedArgsCount = 2,
  };
  data.unparsedArgs    = alloca(2 * sizeof(char *));
  data.unparsedArgs[0] = expected[2];
  data.unparsedArgs[1] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 3, actual);
}

void should_set_install_and_nodependencies_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "install",
      "brave",
      "--ignore-dependencies",
      NULL,
  };
  ArgumentsData data = {
      .action            = INSTALL,
      .confirm           = true,
      .flag              = NODEP_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 3, actual);
}

void should_set_install_and_verbose_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "install",
      "brave",
      "--verbose",
      NULL,
  };
  ArgumentsData data = {
      .action            = INSTALL,
      .confirm           = true,
      .flag              = VERBOSE_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 3, actual);
}

void should_set_install_and_debug_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "install",
      "brave",
      "--debug",
      NULL,
  };
  ArgumentsData data = {
      .action            = INSTALL,
      .confirm           = true,
      .flag              = DEBUG_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 3, actual);
}

void should_set_install_verbose_and_debug_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "install", "brave", "--verbose", "--debug", NULL,
  };
  ArgumentsData data = {
      .action            = INSTALL,
      .confirm           = true,
      .flag              = DEBUG_ARG | VERBOSE_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 4, actual);
}

void should_set_install_yes_and_allow_license_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "install", "oh-my-posh", "--yes", "--accept-license", NULL,
  };
  ArgumentsData data = {
      .action            = INSTALL,
      .confirm           = false,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(data.unparsedArgsCount * sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 4, actual);
}
