cmake_minimum_required(VERSION 3.1.0)

project(fn_aa_lab_06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g3 -fsanitize=address,undefined -fno-omit-frame-pointer")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/Utility.h

    include/Salesman.h
    include/BruteSalesman.h
    include/AntColony.h
)

set(TSRC
)

set(SRC
    source/main.cc

    source/Salesman.cc
    source/BruteSalesman.cc
    source/AntColony.cc
)

add_executable(fn_aa_lab_06
    ${INC}
    ${TSRC}
    ${SRC}
)

target_include_directories(fn_aa_lab_06
    PUBLIC
        "include"
)

