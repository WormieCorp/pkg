cmake_minimum_required(VERSION 3.5.0)

set(_description "Simple program that translates/transforms arguments between different package managers.")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules;${CMAKE_MODULE_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/version.info")
  file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.info" _VERSION)
else()
  set(_VERSION 0.1.0)
endif()

if (CMAKE_VERSION VERSION_LESS "3.11.0")
  project(pkg VERSION 0.1.0 LANGUAGES C CXX) # We must have CXX enabled on older cmake versions
else()
  project(pkg VERSION 0.1.0 LANGUAGES C) # We must have CXX enabled on older cmake versions
endif()
set(CMAKE_PROJECT_DESCRIPTION "${_description}")
set(PROJECT_DESCRIPTION "${_description}")
set(CMAKE_HOMEPAGE_URL "https://github.com/WormieCorp/pkg")
set(PROJECT_HOMEPAGE_URL "${CMAKE_HOMEPAGE_URL}")

# Custom include
set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT Deps)
include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)
include(CTest)

# Cached Configurations
option(BUILD_SHARED_LIBS "Build shared libraries instead of static ones" OFF)

# Definitions for all sub projects and checks
if (WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
endif(WIN32)

# Checks
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckFunctionExists)
check_include_file(alloca.h HAVE_ALLOCA_H)
check_include_file(malloc.h HAVE_MALLOC_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(sys/stat.h HAVE_SYS_STAT_H)
check_symbol_exists(_strdup "string.h" HAVE__STRDUP)
check_symbol_exists(strtok_r "string.h" HAVE_STRTOK_R)
check_symbol_exists(strtok_s "string.h" HAVE_STRTOK_S)

if (HAVE_ALLOCA_H)
  check_symbol_exists(alloca "alloca.h" HAVE_ALLOCA)
elseif(HAVE_MALLOC_H)
  check_symbol_exists(alloca "malloc.h" HAVE_ALLOCA)
else()
  check_symbol_exists(alloca "stdlib.h" HAVE_ALLOCA)
endif()
if (NOT HAVE__STRDUP)
  check_symbol_exists(strdup "string.h" HAVE_STRDUP)
endif()
if (HAVE_SYS_STAT_H)
  check_symbol_exists(stat "sys/stat.h" HAVE_STAT)
  check_symbol_exists(S_IFREG "sys/stat.h" HAVE_S_IFREG)
endif()

# Include directories fol all sub projects
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Subdirectories
add_subdirectory(src)
if (BUILD_TESTING)
  add_subdirectory(tests)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

if (WIN32)
  set(CPACK_BINARY_NSIS OFF)
  set(CPACK_BINARY_7Z ON)
endif()

include(CPack)
