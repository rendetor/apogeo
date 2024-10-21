cmake_minimum_required(VERSION 3.30.5)

project(apogeo)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_C_COMPILER musl-gcc)

add_executable(apogeo ${SRC_DIR}/apogeo.c)

set_target_properties(apogeo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Corregir la llamada a target_compile_options
target_compile_options(apogeo PRIVATE -Wall -Wextra -Wshadow -s -fvisibility=hidden)

# Establecer opciones del enlazador para que sea estático
set_target_properties(apogeo PROPERTIES LINK_FLAGS "-static")

add_custom_command(TARGET apogeo POST_BUILD 
  COMMAND strip -R .comment $<TARGET_FILE:apogeo>
  COMMENT "Stripping the executable")
