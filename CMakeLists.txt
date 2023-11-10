cmake_minimum_required(VERSION 3.24)
project(CanBeTakenTogether)

set(CMAKE_CXX_STANDARD 20)

add_executable(prerequisite.x main_phase2.cpp
        Token.cpp
        Token.hpp
        Tokenizer.cpp
        Tokenizer.hpp
        Parser.hpp
        Parser.cpp
        Tokenizer.cpp
        CourseNode.cpp
        CourseNode.h
        Graph.cpp
        Graph.h
)
