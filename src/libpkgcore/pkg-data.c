#include "pkg-data.h"
#include "logging.h"
#include <stdlib.h>

void release_arguments_data(ArgumentsData *arguments)
{
  if (!arguments)
    return;

  log_debug("Releasing heap allocated ArgumentsData...\n");

  if (arguments->unparsedArgsCount > 0) {
    for (int i = 0; i < arguments->unparsedArgsCount; ++i) {
      free(arguments->unparsedArgs[i]);
    }
  }

  if (arguments->unparsedArgs)
    free(arguments->unparsedArgs);
  free(arguments);
}
