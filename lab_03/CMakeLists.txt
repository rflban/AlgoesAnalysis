cmake_minimum_required(VERSION 3.1.0)

project(fn_aa_lab_03)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g3 -fsanitize=address,undefined -fno-omit-frame-pointer")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
)

set(TSRC
)

set(SRC
    source/main.cc
)

add_executable(fn_aa_lab_03
    ${INC}
    ${TSRC}
    ${SRC}
)

target_include_directories(fn_aa_lab_03
    PUBLIC
        "include"
)

