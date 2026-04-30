cmake_minimum_required(VERSION 3.28.3)
project(main CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rv32i_sim 
      src/main.cpp
      src/cpu.cpp
      src/memory.cpp 
      src/decode.cpp)

target_include_directories(rv32i_sim PRIVATE headers)

target_compile_options(rv32i_sim PRIVATE
    -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -g3 -O0 -std=c++20
)

target_link_options(rv32i_sim PRIVATE -fsanitize=address,undefined)