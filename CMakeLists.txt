cmake_minimum_required(VERSION 3.12.4)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION 0.0.0)
endif()
project(ip_filter VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SRC_PATH "src/")
set(TEST_PATH "test/")
include_directories("inc/")

add_library(
    ip_filter_obj
    ${SRC_PATH}/ipv4_address.cpp
    ${SRC_PATH}/helpers.cpp)
target_link_libraries(ip_filter_obj ${CONAN_LIBS_RANGE-V3})

add_executable(ip_filter ${SRC_PATH}/main.cpp)
target_link_libraries(ip_filter ip_filter_obj)

add_executable(ip_filter_rng ${SRC_PATH}/main_rng.cpp)
target_link_libraries(ip_filter_rng ip_filter_obj)

add_executable(profiling ${SRC_PATH}/profiling.cpp)
target_link_libraries(profiling ip_filter_obj ${CONAN_LIBS_RANGE-V3})

add_executable(test_suite ${TEST_PATH}/test.cpp)
target_link_libraries(
    test_suite
    PRIVATE
    ip_filter_obj
    ${CONAN_LIBS_GTEST})
enable_testing()
add_test(test_suite bin/test_suite)

if(UNIX)
    set(TESTING_BINARY ip_filter)
    configure_file(
        ${CMAKE_SOURCE_DIR}/${TEST_PATH}/hash.sh.in
        bin/hash.sh
        @ONLY)
    set(TESTING_BINARY ip_filter_rng)
    configure_file(
        ${CMAKE_SOURCE_DIR}/${TEST_PATH}/hash.sh.in
        bin/hash_rng.sh
        @ONLY)
    enable_testing()
    add_test(
        NAME integration_test
        COMMAND "bash" "bin/hash.sh")
    add_test(
        NAME integration_test_rng
        COMMAND "bash" "bin/hash_rng.sh")
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT bergentroll@insiberia.net)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=2.15)")
include(CPack)
