#include <launchers/choco-launcher.h>
#include <setjmp.h>
#include <stdlib.h>

#include "../helper.h"

void should_set_upgrade_all_when_upgrade_and_no_unparsed(void **state)
{
  (void)state;
  ArgumentsData data = {
      .action  = UPGRADE,
      .confirm = true,
      .flag    = REFRESH_ARG, // No affected on chocolatey launcher
  };
  char *expected[] = {
      "upgrade",
      "all",
      NULL,
  };

  char **actual = choco_get_launch_args(&data);

  compare_helper(expected, 2, actual);
}

void should_set_upgrade_with_package_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "upgrade",
      "spotify",
      "thunderbird",
      NULL,
  };
  ArgumentsData data = {
      .action  = UPGRADE,
      .confirm = true,
      // Not affected on chocolatey launcher, but kept just in case for futurne
      // reference
      .flag              = REFRESH_ARG,
      .unparsedArgsCount = 2,
  };
  data.unparsedArgs    = alloca(2 * sizeof(char *));
  data.unparsedArgs[0] = expected[1];
  data.unparsedArgs[1] = expected[2];

  char **actual = choco_get_launch_args(&data);

  compare_helper(expected, 3, actual);
}

void should_set_upgrade_with_all_and_non_package_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "upgrade",
      "all",
      "--ia=\"/DIR=D:\\Someplace\"",
  };
  ArgumentsData data = {
      .action            = UPGRADE,
      .confirm           = true,
      .flag              = REFRESH_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[2];

  char **actual = choco_get_launch_args(&data);

  compare_helper(expected, 3, actual);
}

void should_set_upgrade_with_package_and_non_package_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "upgrade",
      "thunderbird",
      "--ia=\"/DIR=D:\\Someplace\"",
  };
  ArgumentsData data = {
      .action            = UPGRADE,
      .confirm           = true,
      .flag              = REFRESH_ARG,
      .unparsedArgsCount = 2,
  };
  data.unparsedArgs    = alloca(2 * sizeof(char *));
  data.unparsedArgs[0] = expected[2];
  data.unparsedArgs[1] = expected[1];

  char **actual = choco_get_launch_args(&data);

  compare_helper(expected, 3, actual);
}

void should_set_upgrade_and_verbose_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "upgrade",
      "brave",
      "--verbose",
      NULL,
  };
  ArgumentsData data = {
      .action            = UPGRADE,
      .confirm           = true,
      .flag              = VERBOSE_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 3, actual);
}

void should_set_upgrade_and_debug_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "upgrade",
      "brave",
      "--debug",
      NULL,
  };
  ArgumentsData data = {
      .action            = UPGRADE,
      .confirm           = true,
      .flag              = DEBUG_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 3, actual);
}

void should_set_upgrade_verbose_and_debug_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "upgrade", "brave", "--verbose", "--debug", NULL,
  };
  ArgumentsData data = {
      .action            = UPGRADE,
      .confirm           = true,
      .flag              = DEBUG_ARG | VERBOSE_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 4, actual);
}

void should_set_upgrade_yes_and_allow_license_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "upgrade", "oh-my-posh", "--yes", "--accept-license", NULL,
  };
  ArgumentsData data = {
      .action            = UPGRADE,
      .confirm           = false,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(data.unparsedArgsCount * sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_get_launch_args(&data);
  compare_helper(expected, 4, actual);
}
