cmake_minimum_required(VERSION 3.29)
project(ECE51216_Project)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(ECE51216_Project
    Clause.cpp
    Clause.h
    main.cpp
        Parser.h
        Parser.cpp
        DPLL.h
        DPLL.cpp
        Heuristics.h
        Heuristics.cpp)
