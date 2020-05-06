add_executable(pacman-parser-tests parsers/pacman-parser-tests.c)
add_executable(choco-launcher-tests launchers/choco-launcher-tests.c)

set(_all_test_targets
  pacman-parser-tests
  choco-launcher-tests
)

foreach(_test_target ${_all_test_targets})
  target_link_libraries(${_test_target} cmocka::cmocka pkg-translator)

  add_test(NAME ${_test_target} COMMAND $<TARGET_FILE:${_test_target}>)
endforeach(_test_target ${_all_test_targets})
