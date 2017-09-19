project(boost_iostreams CXX C)
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    message(STATUS "Using Conan")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup()
    
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_NO_SYSTEM_PATHS ON)
    set(BOOST_ROOT ${CONAN_BOOST_HEADERS_ROOT})
    set(BOOST_INCLUDEDIR ${CONAN_INCLUDE_DIRS_BOOST_HEADERS})
    set(BOOST_LIBRARYDIR ${CONAN_LIB_DIRS_BOOST_LIBRARIES})
endif()

find_package(Boost REQUIRED COMPONENTS iostreams)

set(GoogleTest_DIR "vendor/googletest")
if(MSVC)
    set(gtest_force_shared_crt ON)
endif()
add_subdirectory(${GoogleTest_DIR})

include_directories(
    ${BOOST_INCLUDEDIR}
    "${GoogleTest_DIR}/googletest/include"
)

set(Test_SOURCES
    simple.cpp
)
add_executable(${PROJECT_NAME} ${Test_SOURCES})
target_link_libraries(${PROJECT_NAME} gtest_main ${BOOST_LIBRARIES})
enable_testing()
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
