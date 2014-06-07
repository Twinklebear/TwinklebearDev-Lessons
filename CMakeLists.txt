cmake_minimum_required(VERSION 2.6)
project(TwinklebearDevLessons)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TwinklebearDevLessons_SOURCE_DIR}/cmake")
set(BIN_DIR ${TwinklebearDevLessons_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -ggdb -std=c++11")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(include)

add_subdirectory(Lesson0)
add_subdirectory(Lesson1)
add_subdirectory(Lesson2)
add_subdirectory(Lesson3)
add_subdirectory(Lesson4)
add_subdirectory(Lesson5)
add_subdirectory(Lesson6)

