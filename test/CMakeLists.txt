cmake_minimum_required(VERSION 3.10)
project(HaffmanArchiver_test)

add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)
set(CMAKE_CXX_STANDARD 14)

set(TEST_SOURCE ../include/HuffmanException.h ../src/HuffmanException.cpp
        ../include/HuffmanArchiver.h ../src/HuffmanArchiver.cpp
        ../src/HuffmanTree.cpp ../include/HuffmanTree.h
        ../include/binary.h ../include/binary_impl.inl ../src/binary_bool_impl.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
add_executable(HaffmanArchiver_test
        EXCLUDE_FROM_ALL ${TEST_SOURCE}
        test.cpp huffman_test.h huffman_test.cpp)

target_include_directories(HaffmanArchiver_test PUBLIC lib/googletest/googletest/include)
target_include_directories(HaffmanArchiver_test PUBLIC lib/googletest/googlemock/include)
target_include_directories(HaffmanArchiver_test PUBLIC ../include)
target_link_libraries(HaffmanArchiver_test gtest gtest_main)

add_custom_target(test DEPENDS HaffmanArchiver_test)

