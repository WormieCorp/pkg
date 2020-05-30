cmake_minimum_required(VERSION 3.5.0)

set(_description "Simple program that translates/transforms arguments between different package managers.")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules;${CMAKE_MODULE_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/version.info")
  file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.info" _VERSION_ARR)
  list(GET _VERSION_ARR 0 _VERSION)
  list(GET _VERSION_ARR 1 _VERSION_SEMVER)
  list(GET _VERSION_ARR 2 _VERSION_FULLSEMVER)
  list(GET _VERSION_ARR 3 _VERSION_BUILD)
else()
  set(_VERSION 0.1.0)
  set(_VERSION_SEMVER ${_VERSION})
  set(_VERSION_FULLSEMVER ${_VERSION})
  set(_VERSION_BUILD 0)
endif()

if (CMAKE_VERSION VERSION_LESS "3.11.0")
  project(pkg VERSION ${_VERSION} LANGUAGES C CXX) # We must have CXX enabled on older cmake versions
else()
  project(pkg VERSION ${_VERSION} LANGUAGES C)
endif()
set(CMAKE_PROJECT_DESCRIPTION "${_description}")
set(PROJECT_DESCRIPTION "${_description}")
set(CMAKE_HOMEPAGE_URL "https://github.com/WormieCorp/pkg")
set(PROJECT_HOMEPAGE_URL "${CMAKE_HOMEPAGE_URL}")
set(PROJECT_AUTHOR "Kim J. Nordmo")
set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
message("Building ${PROJECT_NAME} v${_VERSION_SEMVER}...")

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
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/platforms/windows/pkg.iss ${CMAKE_CURRENT_BINARY_DIR}/pkg.iss @ONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/platforms/windows/modpath.iss ${CMAKE_CURRENT_BINARY_DIR}/modpath.iss COPYONLY)

  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/files.iss" "Source: \"${CMAKE_CURRENT_BINARY_DIR}/{#Configuration}/pkg.exe\"; DestDir: \"{app}\"\n")
  if (BUILD_SHARED_LIBS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/files.iss" "Source: \"${CMAKE_CURRENT_BINARY_DIR}/{#Configuration}/pkgcore.dll\"; DestDir: \"{app}\"\n")
  endif()

  foreach(_lib ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/files.iss" "Source: \"${_lib}\"; DestDir: \"{app}\"\n")
  endforeach()
  find_program(ISCC_EXEC "iscc")
  add_custom_target(create-installer ${ISCC_EXEC} "/DConfiguration=$<CONFIG>" ${CMAKE_CURRENT_BINARY_DIR}/pkg.iss
    DEPENDS pkgcore pkg)

  set(CPACK_BINARY_NSIS OFF)
endif()

set(CPACK_PACKAGE_VERSION ${_VERSION_SEMVER})
include(CPack)
