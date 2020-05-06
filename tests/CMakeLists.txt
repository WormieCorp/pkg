include(ExternalProject)
ExternalProject_Add(cmocka_ep
    URL "https://cmocka.org/files/1.1/cmocka-1.1.5.tar.xz"
    URL_HASH "SHA512=CAD7F04757183D004F6EAAD39036FC0E24C5E0E987F80E85BC43BC66DBA22389CB02B08E25531CC28A541D0A24A86B29BE134A2D6FC339128E87D66952F502BD"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/third-party/cmocka"
    #URL https://git.cryptomilk.org/projects/cmocka.git/snapshot/cmocka-1.0.1.tar.xz
    #URL_HASH SHA256=b3831d1ced5423890fcca347b40fbeda5b0903fc0296596abf0f68013c9eafdc
    #GIT_REPOSITORY git://git.cryptomilk.org/projects/cmocka.git
    #GIT_TAG cmocka-1.0.1
    # Use git submodule to fetch source manually and in-tree, store in SOURCE_DIR
    #SOURCE_DIR ${CMAKE_SOURCE_DIR}/modules/cmocka
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}
               -DWITH_STATIC_LIB=ON
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=Debug
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=Release
               -DUNIT_TESTING=FALSE
               -DWITH_EXAMPLES=FALSE
               -DPICKY_DEVELOPER=TRUE

    # Don't build unused examples and disable install step
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG> --target cmocka-static
    INSTALL_COMMAND "")


add_library(cmocka::cmocka STATIC IMPORTED GLOBAL)
ExternalProject_Get_Property(cmocka_ep binary_dir)
if (WIN32)
  set(_cmocka_name "cmocka-static.lib")
else()
  set(_cmocka_name "libcmocka.a")
endif()

set_property(TARGET cmocka::cmocka PROPERTY IMPORTED_LOCATION
             "${binary_dir}/src/${_cmocka_name}")
set_property(TARGET cmocka::cmocka PROPERTY IMPORTED_LOCATION_DEBUG
             "${binary_dir}/src/Debug/${_cmocka_name}")
set_property(TARGET cmocka::cmocka PROPERTY IMPORTED_LOCATION_RELEASE
             "${binary_dir}/src/Release/${_cmocka_name}")
set_property(TARGET cmocka::cmocka PROPERTY IMPORTED_LOCATION_MINSIZEREL
             "${binary_dir}/src/MinSizeRel/${_cmocka_name}")
set_property(TARGET cmocka::cmocka PROPERTY IMPORTED_LOCATION_RELWITHDEBINFO
             "${binary_dir}/src/RelWithDebInfo/${_cmocka_name}")

add_dependencies(cmocka::cmocka cmocka_ep)

ExternalProject_Get_Property(cmocka_ep source_dir)
set(CMOCKA_INCLUDE_DIR ${source_dir}/include GLOBAL)

include_directories(${CMOCKA_INCLUDE_DIR})
add_subdirectory(libpkg-translator-tests)
add_subdirectory(pkg-tests)
