# CMakeLists.txt

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(foobar
	VERSION 0.0.1
	LANGUAGES CXX
	)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED
	sdl2
	SDL2_image
	)

add_executable(foobar
	collidercomponent.hpp
	collision.hpp
	components.hpp
	ecs.hpp
	exception.hpp
	game.hpp
	keyboardcontroller.hpp
	main.cpp
	map.hpp
	matrix.hpp
	point.hpp
	sdl.hpp
	spritecomponent.hpp
	texturemanager.hpp
	transformcomponent.hpp
	vector2d.hpp
	)

target_include_directories(foobar
	PUBLIC
		${SDL2_INCLUDE_DIRS}
	)

target_link_libraries(foobar
	PUBLIC
		${SDL2_LINK_LIBRARIES}
	)

# vim:set sw=4 ts=4 noet:
