#ifndef _HAVE_PKG_LOGGING_H
#define _HAVE_PKG_LOGGING_H
#include "pkgcore_export.h"

enum VerbosityLevel {
  Debug,
  Verbose,
  Info,
  Warning,
  Error,
  Fatal,
};

PKGCORE_EXPORT void log_debug(const char *format, ...);

PKGCORE_EXPORT void log_verbose(const char *format, ...);

PKGCORE_EXPORT void log_info(const char *format, ...);

PKGCORE_EXPORT void log_warning(const char *format, ...);

PKGCORE_EXPORT void log_error(const char *format, ...);

#endif
