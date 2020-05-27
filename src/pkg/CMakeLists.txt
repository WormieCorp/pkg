set(C_SOURCES
  main.c
)

include(generate_product_version)
generate_product_version(
  C_SOURCES
  NAME pkg
  COMPANY_NAME "Kim J. Nordmo"
  VERSION_REVISION ${_VERSION_BUILD}
)

add_executable(pkg ${C_SOURCES})
target_link_libraries(pkg PUBLIC pkgcore)
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(pkg PRIVATE -Wno-incompatible-pointer-types)
endif()

install(TARGETS pkg
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
