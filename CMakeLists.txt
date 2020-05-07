cmake_minimum_required(VERSION 3.5.0)

set(_description "Simple program that translates/transforms arguments between different package managers.")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules;${CMAKE_MODULE_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if (CMAKE_VERSION VERSION_LESS "3.11.0")
  project(pkg-manager-translator VERSION 0.1.0 LANGUAGES C CXX) # We must have CXX enabled on older cmake versions
else()
  project(pkg-manager-translator VERSION 0.1.0 LANGUAGES C) # We must have CXX enabled on older cmake versions
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
option(BUILD_SHARED_LIBS "Build shared libraries instead of static ones" ON)

# Checks
include(CheckIncludeFile)
check_include_file(string.h HAVE_STRING_H)
include(CheckSymbolExists)
check_symbol_exists(_strdup "string.h" HAVE__STRDUP)
if (NOT HAVE__STRDUP)
  check_symbol_exists(strdup "string.h" HAVE_STRDUP)
endif()

# Definitions for all sub projects
add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# Include directories fol all sub projects
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Subdirectories
add_subdirectory(src)
if (BUILD_TESTING)
  add_subdirectory(tests)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
