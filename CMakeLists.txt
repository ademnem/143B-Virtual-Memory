cmake_minimum_required(VERSION 3.20)
project(FileSystemProject CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)


set(SRC_FILES  
    ${SRC_DIR}/vm.cpp
    ${SRC_DIR}/main.cpp
)
add_executable(main ${SRC_FILES})
target_include_directories(main PRIVATE ${INCLUDE_DIR})

set(TEST_FILES
    ${SRC_DIR}/vm.cpp
    ${TEST_DIR}/vm_tests.cpp
)
add_executable(test ${TEST_FILES})
target_include_directories(test PRIVATE ${INCLUDE_DIR})
