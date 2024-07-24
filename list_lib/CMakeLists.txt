cmake_minimum_required(VERSION 3.11)

project(ListStaticLib CXX)
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES "double_linked_list.h")
set(SOURCE_FILES "double_linked_list.cpp")

add_library(ListStaticLib STATIC ${HEADER_FILES} ${SOURCE_FILES})
