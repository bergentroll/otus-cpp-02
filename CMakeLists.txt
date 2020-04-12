cmake_minimum_required(VERSION 3.12.4)

if($ENV{TRAVIS_BUILD_NUMBER})
  set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
  set(VERSION 0.0.0)
endif()
project(otus-cpp-03 VERSION ${VERSION})

set_target_properties(${TARGET} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

set(GTEST_SRCDIR "/usr/src/gtest/")

set(SRC_PATH "src/")
set(TEST_PATH "test/")
include_directories("inc/")

#add_library(helloworld ${SRC_PATH}/helloworld.cpp)
add_executable(
    ip_filter
    ${SRC_PATH}/main.cpp
    ${SRC_PATH}/ipv4_address.cpp
    ${SRC_PATH}/helpers.cpp)
set_target_properties(ip_filter PROPERTIES ENABLE_EXPORTS 1)

if(EXISTS "${GTEST_SRCDIR}/CMakeLists.txt")
  add_subdirectory(${GTEST_SRCDIR}/ ${CMAKE_BINARY_DIR}/gtest/ EXCLUDE_FROM_ALL)

  add_executable(test_suite ${TEST_PATH}/test.cpp)
  target_link_libraries(
    test_suite
    PRIVATE
    ip_filter
    gtest)
  enable_testing()
  add_test(test_suite test_suite)
else()
  message(
    WARNING
    "GTest test suite will not be launched because GTest sources is not found"
    " at ${GTEST_SRCDIR}.")
endif()

if(UNIX)
    configure_file(${CMAKE_SOURCE_DIR}/${TEST_PATH}/hash.sh.in hash.sh)
    enable_testing()
    add_test(
        NAME integration-test
        COMMAND "bash" "hash.sh")
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT bergentroll@insiberia.net)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=2.15)")
include(CPack)
