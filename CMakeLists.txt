


cmake_minimum_required(VERSION 3.20)

project(Item-manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(item-manager main.cpp)

if(MSVC)
	target_compile_options(item-manager PRIVATE
		/W4
		/utf-8
	)
else()
	target_compile_options(item-manager PRIVATE
	  -Wall
	  -Wextra
	  -pedantic
	  )
endif()
