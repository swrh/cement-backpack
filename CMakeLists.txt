# CMakeLists.txt

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(foobar
	VERSION 0.0.1
	LANGUAGES CXX
	)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

include_directories(
	${SDL2_INCLUDE_DIR}
	)

add_executable(foobar
	exception.hpp
	game.hpp
	gameobject.hpp
	main.cpp
	map.hpp
	sdl.hpp
	texturemanager.hpp
	)

target_link_libraries(foobar
	${SDL2_LIBRARIES}
	SDL2_image
	)

# vim:set sw=4 ts=4 noet:
