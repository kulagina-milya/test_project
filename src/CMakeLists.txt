cmake_minimum_required(VERSION 3.11)

project(TestProject CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(TestProject
	main.cpp
	shapes.cpp
	shapes_factory.cpp)

include_directories("../list_lib")

target_link_libraries(TestProject PRIVATE ListStaticLib 
#PRIVATE ws2_32 wsock32
)