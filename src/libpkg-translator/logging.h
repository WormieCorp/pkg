#ifndef _HAVE_PKG_LOGGING_H
#define _HAVE_PKG_LOGGING_H
#include "pkg-translator_export.h"

enum VerbosityLevel {
  Debug,
  Verbose,
  Info,
  Warning,
  Error,
  Fatal,
};

PKG_TRANSLATOR_EXPORT void log_debug(const char *format, ...);

PKG_TRANSLATOR_EXPORT void log_verbose(const char *format, ...);

PKG_TRANSLATOR_EXPORT void log_info(const char *format, ...);

PKG_TRANSLATOR_EXPORT void log_warning(const char *format, ...);

PKG_TRANSLATOR_EXPORT void log_error(const char *format, ...);

#endif
