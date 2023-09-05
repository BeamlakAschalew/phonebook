cmake_minimum_required(VERSION 3.23)
project(phonebook)

set(CMAKE_CXX_STANDARD 14)

add_executable(phonebook main.cpp)
add_executable(gpt gpt.cpp)
add_executable(ed clear.cpp)
