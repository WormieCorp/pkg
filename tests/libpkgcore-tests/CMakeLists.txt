add_executable(pacman-parser-tests parsers/pacman-parser-tests.c)
add_executable(choco-transformer-tests transformers/choco-transformer-tests.c)

set(_all_test_targets
  pacman-parser-tests
  choco-transformer-tests
)

foreach(_test_target ${_all_test_targets})
  target_link_libraries(${_test_target} cmocka::cmocka pkgcore)
  if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${_test_target} PRIVATE -Wno-incompatible-pointer-types)
  endif()

  add_test(NAME ${_test_target} COMMAND $<TARGET_FILE:${_test_target}>)
endforeach(_test_target ${_all_test_targets})
