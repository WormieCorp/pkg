#include "logging.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef NDEBUG
enum VerbosityLevel logLevel = Info;
#else
enum VerbosityLevel logLevel = Debug;
#endif

void log_debug(const char *format, ...)
{
  if (logLevel > Debug)
    return;
  va_list ap;
  va_start(ap, format);
  printf("[\033[38;5;240;1mDBG\033[0m]: \033[38;5;240m");
  vprintf(format, ap);
  printf("\033[0m");
  va_end(ap);
}

void log_verbose(const char *format, ...)
{
  if (logLevel > Verbose)
    return;
  va_list ap;
  va_start(ap, format);
  printf("[\033[38;5;136;1mVRB\033[0m]: \033[38;5;245;2m");
  vprintf(format, ap);
  printf("\033[0m");
  va_end(ap);
}

void log_info(const char *format, ...)
{
  if (logLevel > Info)
    return;
  va_list ap;
  va_start(ap, format);
  vprintf(format, ap);
  va_end(ap);
}

void log_warning(const char *format, ...)
{
  if (logLevel > Warning)
    return;
  va_list ap;
  va_start(ap, format);
  fprintf(stderr, "[\033[38;5;220;1mWRN\033[0m]: \033[38;5;214m");
  vfprintf(stderr, format, ap);
  fprintf(stderr, "\033[0m");
  va_end(ap);
}

void log_error(const char *format, ...)
{
  if (logLevel > Error)
    return;
  va_list ap;
  va_start(ap, format);
  fprintf(stderr, "[\033[38;5;196;1mERR\033[0m]: \033[38;5;196m");
  vfprintf(stderr, format, ap);
  fprintf(stderr, "\033[0m");

  va_end(ap);
}
