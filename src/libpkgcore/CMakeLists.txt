set(C_SOURCES
  logging.c
  pkg-data.c
  resolver.c
  utilities.c
  launchers/choco_launcher.c
  launchers/launcher.c
  parsers/choco-parser.c
  parsers/pacman-parser.c
  parsers/parsers.c
  transformers/choco-transformer.c
)

if (WIN32)
  set(C_SOURCES ${C_SOURCES} launchers/launcher_windows.c)
else()
  set(C_SOURCES ${C_SOURCES} launchers/launcher_dummy.c)
endif()
if (BUILD_SHARED_LIBS)
  set(_TARGET_BUILD_TYPE "VFT_DLL")
else()
  set(_TARGET_BUILD_TYPE "VFT_STATIC_LIB")
endif()

include(generate_product_version)
generate_product_version(
  C_SOURCES
  NAME pkgcore
  COMPANY_NAME ${PROJECT_AUTHOR}
  FILE_DESCRIPTION "Library responsible for handling the core logic of the pkg program."
  VERSION_REVISION ${_VERSION_BUILD}
  FILE_TYPE ${_TARGET_BUILD_TYPE}
)

add_library(pkgcore ${C_SOURCES})
include(GenerateExportHeader)
generate_export_header(pkgcore)
target_include_directories(pkgcore PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(pkgcore PRIVATE -Wno-incompatible-pointer-types)
endif()

if (BUILD_SHARED_LIBS)
  install(TARGETS pkgcore
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
