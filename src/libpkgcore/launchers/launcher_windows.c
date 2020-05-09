#include "../logging.h"
#include "config.h"
#include "launcher.h"
#include <conio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

size_t get_total_length(const char **arguments);
void combine_to_string(TCHAR *buffer, const char **arguments);
bool is_elevated(void);
void create_as_process(TCHAR *path, TCHAR *arguments);
void launch_elevated(TCHAR *path, TCHAR *arguments);

void launch_program(const char *path, const char **arguments, bool elevate)
{
  (void)elevate;

  TCHAR *bufArgs = _malloca(get_total_length(arguments) * sizeof(TCHAR));
  size_t pathlen = strlen(path) + 1;
  TCHAR *pathBuf = _malloca(pathlen * sizeof(TCHAR));
#if _UNICODE
  mbstowcs(pathBuf, path, pathlen);
#else
  strncpy(pathBuf, path, pathlen);
#endif
  combine_to_string(bufArgs, arguments);

  if (!elevate || is_elevated())
    create_as_process(pathBuf, bufArgs);
  else
    launch_elevated(pathBuf, bufArgs);

  _freea(bufArgs);
  _freea(pathBuf);
}

void create_as_process(TCHAR *path, TCHAR *arguments)
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  _tcprintf(_T("Calling '%s%s'\n\n"), path, arguments);

  if (!CreateProcess(path, arguments, NULL, NULL, FALSE, 0, NULL, NULL, &si,
                     &pi)) {
    log_error("Unable to launch the program '%s'\n", path);
    return;
  }

  WaitForSingleObject(pi.hProcess, INFINITE);

  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}

void launch_elevated(TCHAR *path, TCHAR *arguments)
{
  _tcprintf("Launching '%s%s' in elevated prompt.\n", path, arguments);

  SHELLEXECUTEINFO ShExecInfo = {0};
  ShExecInfo.cbSize           = sizeof(SHELLEXECUTEINFO);
  ShExecInfo.fMask            = SEE_MASK_NOCLOSEPROCESS;
  ShExecInfo.hwnd             = NULL;
  log_warning(
      "Elevating application. No output will be shown in this window.\n");
  ShExecInfo.lpVerb       = "runas";
  ShExecInfo.lpFile       = path;
  ShExecInfo.lpParameters = arguments;
  ShExecInfo.lpDirectory  = NULL;
  ShExecInfo.nShow        = SW_SHOWNORMAL;
  ShExecInfo.hInstApp     = NULL;
  if (!ShellExecuteEx(&ShExecInfo)) {
    log_error("Unable to launch the program '%s\n", path);
    return;
  }

  WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
  CloseHandle(ShExecInfo.hProcess);
}

bool is_elevated(void)
{
  bool ret      = false;
  HANDLE hToken = NULL;
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
    TOKEN_ELEVATION elevation;
    DWORD cbSize = sizeof(TOKEN_ELEVATION);
    if (GetTokenInformation(hToken, TokenElevation, &elevation,
                            sizeof(elevation), &cbSize))
      ret = elevation.TokenIsElevated;

    if (hToken)
      CloseHandle(hToken);
  }

  return ret;
}

void combine_to_string(TCHAR *buffer, const char **arguments)
{
  int i = -1;
  _tcscpy(buffer, _T("")); // Ensure that the string is NUL terminated
  while (*(arguments + ++i)) {
    const char *arg = *(arguments + i);
    _tcscat(buffer, _T(" "));
#if _UNICODE
    size_t len = strlen(*(arguments + i)) + 1;
    TCHAR *buf = alloca(len * sizeof(TCHAR));
    mbstowcs(buf, arg, len);
    _tcscat(buffer, buf);
#else
    _tcscat(buffer, arg);
#endif
  }
}
