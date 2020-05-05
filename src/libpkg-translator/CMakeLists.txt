set(C_SOURCES
  dummy.c
)

include(generate_product_version)
generate_product_version(
  C_SOURCES
  NAME pkg-translator
  COMPANY_NAME "Kim J. Nordmo"
  FILE_DESCRIPTION "Library responsible for handling the core logic of the pkg-translator program."
)

add_library(pkg-translator ${C_SOURCES})
include(GenerateExportHeader)
generate_export_header(pkg-translator)
