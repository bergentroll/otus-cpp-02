cmake_minimum_required(VERSION 3.12.4)

if($ENV{TRAVIS_BUILD_NUMBER})
  set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
  set(VERSION 0.0.0)
endif()
project(ip_filter VERSION ${VERSION})

set_target_properties(${TARGET} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SRC_PATH "src/")
set(TEST_PATH "test/")
include_directories("inc/")

add_library(
    ip_filter_obj
    ${SRC_PATH}/ipv4_address.cpp
    ${SRC_PATH}/helpers.cpp)

add_executable(ip_filter ${SRC_PATH}/main.cpp)
target_link_libraries(ip_filter ip_filter_obj ${CONAN_LIBS_RANGE-V3})

add_executable(test_suite ${TEST_PATH}/test.cpp)
target_link_libraries(
  test_suite
  PRIVATE
  ip_filter_obj
  ${CONAN_LIBS_GTEST})
enable_testing()
add_test(test_suite bin/test_suite)

if(UNIX)
    configure_file(
      ${CMAKE_SOURCE_DIR}/${TEST_PATH}/hash.sh.in
      bin/hash.sh
      @ONLY)
    enable_testing()
    add_test(
      NAME integration_test
      COMMAND "bash" "bin/hash.sh")
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT bergentroll@insiberia.net)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=2.15)")
include(CPack)
