cmake_minimum_required(VERSION 3.24)
project(CanBeTakenTogether)

set(CMAKE_CXX_STANDARD 20)

add_executable(prerequisite.x main_phase2.cpp
        Parser/Token.cpp
        Parser/Token.hpp
        Parser/Tokenizer.cpp
        Parser/Tokenizer.hpp
        Parser/Parser.hpp
        Parser/Parser.cpp
        Parser/Tokenizer.cpp
        Graph/CourseNode.cpp
        Graph/CourseNode.h
        Graph/Graph.cpp
        Graph/Graph.h
)
