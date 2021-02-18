cmake_minimum_required(VERSION 3.10)
project(HaffmanArchiver)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE include/HuffmanException.h src/HuffmanException.cpp
        include/HuffmanArchiver.h src/HuffmanArchiver.cpp
        src/HuffmanTree.cpp include/HuffmanTree.h
        include/binary.h include/binary_impl.inl src/binary_bool_impl.cpp)

add_subdirectory(test EXCLUDE_FROM_ALL)
add_executable(HaffmanArchiver src/main.cpp ${SOURCE})