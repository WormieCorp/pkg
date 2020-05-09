#include <string.h>

size_t get_total_length(const char **arguments)
{
  int i        = 0;
  size_t count = 0;

  while (*(arguments + i)) {
    count += strlen(*(arguments + i)) + 1;
    i++;
  }

  count++; // Just to make sure we at least have a null terminator

  return count;
}
