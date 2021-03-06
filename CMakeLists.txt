cmake_minimum_required(VERSION 3.10)

project(BFCC LANGUAGES C VERSION 0.0.1)

add_executable(bfcc src/main.c src/error.c src/cg-x86_64.c src/parse.c)

set(CMAKE_C_STANDARD 99)

if (MSVC)
	target_compile_options(bfcc PRIVATE /permissive- /W4)
else()
	target_compile_options(bfcc PRIVATE -Wall -Wextra -Wpedantic -g)
endif()
