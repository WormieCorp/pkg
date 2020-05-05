set(C_SOURCES
  main.c
)

include(generate_product_version)
generate_product_version(
  C_SOURCES
  NAME pkg
  COMPANY_NAME "Kim J. Nordmo"
)

add_executable(pkg ${C_SOURCES})
target_link_libraries(pkg PUBLIC pkg-translator)
