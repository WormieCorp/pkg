#include <setjmp.h>
#include <stdlib.h>
#include <transformers/choco-transformer.h>

#include "../helper.h"

void should_set_uninstall_and_help_arguments(void **state)
{
  (void)state;
  ArgumentsData data = {
      .action  = UNINSTALL,
      .confirm = true,
  };
  char *expected[] = {
      "uninstall",
      "--help",
      NULL,
  };

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 2, actual);
}

void should_set_uninstall_and_package_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall", "googlechrome", "brave", "pkg", NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .confirm           = true,
      .unparsedArgsCount = 3,
  };
  add_unparsed_packages((expected + 1), &data);

  char **actual = choco_transform_arguments(&data);
  free(data.unparsedArgs);
  compare_helper(expected, 4, actual);
}

void should_set_uninstall_and_non_package_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall",
      "brave",
      "--skipautouninstaller",
      NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .confirm           = true,
      .unparsedArgsCount = 2,
  };
  data.unparsedArgs    = alloca(2 * sizeof(char *));
  data.unparsedArgs[0] = expected[2];
  data.unparsedArgs[1] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 3, actual);
}

void should_set_uninstall_without_nodependencies_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall",
      "brave",
      NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .confirm           = true,
      .flag              = NODEP_ARG,
      .unparsedArgsCount = 1,
  };
  add_unparsed_packages(expected + 1, &data);

  char **actual = choco_transform_arguments(&data);
  free(data.unparsedArgs);
  compare_helper(expected, 2, actual);
}

void should_set_uninstall_and_verbose_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall",
      "brave",
      "--verbose",
      NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .confirm           = true,
      .flag              = VERBOSE_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 3, actual);
}

void should_set_uninstall_and_debug_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall",
      "brave",
      "--debug",
      NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .confirm           = true,
      .flag              = DEBUG_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 3, actual);
}

void should_set_uninstall_verbose_and_debug_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall", "brave", "--verbose", "--debug", NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .confirm           = true,
      .flag              = DEBUG_ARG | VERBOSE_ARG,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 4, actual);
}

void should_set_uninstall_yes_and_without_allow_license_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall",
      "oh-my-posh",
      "--yes",
      NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .confirm           = false,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(data.unparsedArgsCount * sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 3, actual);
}

void should_set_uninstall_and_without_no_progress_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall",
      "pkg",
      NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .flag              = HIDE_PROGRESS_ARG,
      .confirm           = true,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(data.unparsedArgsCount * sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 2, actual);
}

void should_set_uninstall_and_remove_dependencies_on_recurse(void **state)
{
  (void)state;
  char *expected[] = {
      "uninstall",
      "pkg",
      "--remove-dependencies",
      NULL,
  };
  ArgumentsData data = {
      .action            = UNINSTALL,
      .flag              = RECURSE_ARG,
      .confirm           = true,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 3, actual);
}
