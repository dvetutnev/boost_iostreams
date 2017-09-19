project(boost_iostreams CXX C)

find_package(Boost REQUIRED COMPONENTS iostreams)

set(GoogleTest_DIR "vendor/googletest")
add_subdirectory(${GoogleTest_DIR})

include_directories(
    ${BOOST_INCLUDEDIR}
    "${GoogleTest_DIR}/googletest/include"
)

set(Test_SOURCES
    simple.cpp
)
add_executable(test ${Test_SOURCES})
target_link_libraries(test gtest_main ${BOOST_LIBRARIES})
enable_testing()
add_test(
    NAME test
    COMMAND test
)
