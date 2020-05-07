set(C_SOURCES
  logging.c
  pkg-data.c
  launchers/launchers.c
  parsers/pacman-parser.c
  parsers/parsers.c
  transformers/choco-transformer.c
)

include(generate_product_version)
generate_product_version(
  C_SOURCES
  NAME pkgcore
  COMPANY_NAME "Kim J. Nordmo"
  FILE_DESCRIPTION "Library responsible for handling the core logic of the pkg program."
)

add_library(pkgcore ${C_SOURCES})
include(GenerateExportHeader)
generate_export_header(pkgcore)
target_include_directories(pkgcore PUBLIC "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(pkgcore PRIVATE -Wno-incompatible-pointer-types)
endif()
