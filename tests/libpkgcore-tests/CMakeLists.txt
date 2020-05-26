set(_all_test_targets
  choco-parser-tests
  choco-transformer-tests
  launcher-tests
  pacman-parser-tests
  parsers-tests
  utilities-tests
)

foreach(_test_target ${_all_test_targets})
  if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_test_target}.c")
    add_executable(${_test_target} ${_test_target})
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/launchers/${_test_target}.c")
    add_executable(${_test_target} launchers/${_test_target}.c)
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/parsers/${_test_target}.c")
    add_executable(${_test_target} parsers/${_test_target}.c)
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/transformers/${_test_target}.c")
    add_executable(${_test_target} transformers/${_test_target}.c)
  else()
    message(FATAL_ERROR "No file found for '${_test_target}")
  endif()
  target_link_libraries(${_test_target} cmocka::cmocka pkgcore)
  if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${_test_target} PRIVATE -Wno-incompatible-pointer-types)
  endif()

  add_test(NAME ${_test_target} COMMAND $<TARGET_FILE:${_test_target}>)
endforeach(_test_target ${_all_test_targets})
