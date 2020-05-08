#include <setjmp.h>
#include <stdlib.h>
#include <transformers/choco-transformer.h>

#include "../helper.h"

void should_set_info_and_help_arguments(void **state)
{
  (void)state;
  ArgumentsData data = {
      .action  = INFO,
      .confirm = true,
  };
  char *expected[] = {
      "info",
      "--help",
      NULL,
  };

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 2, actual);
}

void should_set_info_and_package_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "info",
      "brave",
      NULL,
  };
  ArgumentsData data = {
      .action            = INFO,
      .confirm           = true,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 2, actual);
}

void should_set_info_and_local_only_arguments(void **state)
{
  (void)state;
  char *expected[] = {
      "info",
      "brave",
      "--local-only",
      NULL,
  };
  ArgumentsData data = {
      .action            = INFO,
      .flag              = LOCALONLY_ARG,
      .confirm           = true,
      .unparsedArgsCount = 1,
  };
  data.unparsedArgs    = alloca(sizeof(char *));
  data.unparsedArgs[0] = expected[1];

  char **actual = choco_transform_arguments(&data);
  compare_helper(expected, 3, actual);
}
