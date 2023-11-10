//
// Created by Ethan Edwards on 11/1/2023
//

#include <iostream>
#include <fstream>

#include "constants.hpp"
#include "Parser.hpp"
#include "Graph.h"

void verifyReadableInputFile(char* jsonFileName);

int main(int argc, char *argv[]) {
    // Make sure that the executable was given exactly 2 command-line argument

    if (argc > 5) {
        std::cerr << errorMessages[E_WRONG_NUMBER_ARGS] << std::endl;
        exit(E_WRONG_NUMBER_ARGS);
    }

    verifyReadableInputFile(argv[argc - 1]);

    // Create Parser object for the JSON file and get the map it returns.
    Parser parser(argv[argc - 1]);
    std::map<std::string, std::vector<std::string>> requisiteMap = parser.parseJSONObject();

    // Create Graph object for the JSON file and build the graph
    Graph graph;
    graph.buildGraph(requisiteMap);

    // Run the given command
    std::string command = argv[1];

    if (command == "-test"){
        std::cout << graph.pathFromTo("CS 242", "CS 115").empty();
        return 0;
    }

    if (command == "-cyclic"){
        std::cout << "The graph induced by " << argv[argc - 1];
        if (!graph.isCyclic()){
            std::cout << " does not";
        }
        std::cout << " contains a cycle." << std::endl;
    }
    else if (command == "-print"){
        graph.printGraph();
    }
    else if (command == "-includes"){
        if (graph.isALabel(argv[2])){
            std::cout << argv[argc - 1] << " includes " << argv[2] << "." << std::endl;
            return 0;
        }
        std::cout << argv[argc - 1] << " does not include " << argv[2] << "." << std::endl;
    }
    else if (command == "-together"){
        if (graph.canBeTakenConcurrently(argv[2], argv[3])){
            std::cout << argv[2] << " and " << argv[3] << " can be taken concurrently." << std::endl;
            return 0;
        }
        std::cout << argv[2] << " and " << argv[3] << " cannot be taken concurrently." << std::endl;
    }
    else if (command == "-allpairs"){
        for (auto&[key, value] : requisiteMap){
            for (auto&[key2, value2] : requisiteMap){
                if (key != key2){
                    if (graph.canBeTakenConcurrently(key, key2)){
                        std::cout << key << " and " << key2 << " can be taken concurrently." << std::endl;
                    }
                    else {
                        std::cout << key << " and " << key2 << " cannot be taken concurrently." << std::endl;
                    }
                }
            }
        }
    }
    else if (command == "-chains"){
        std::vector<std::vector<std::string>> prereqs;
        graph.prerequisiteChainsFor(argv[2], prereqs);
        for (std::vector<std::string>& i : prereqs){
            int iter = 0;
            for (int j = static_cast<int>(i.size()) - 1; j > -1; j--){ // Iterate in reverse to get the correct order
                std::cout << i[j];
                if (iter != static_cast<int>(i.size()) - 1){std::cout << ", ";} // If not last element, print comma
                iter++;
            }
            std::cout << std::endl;
        }
    }
    else if (command == "-length"){
        std::cout << "The length of the longest prerequisite chain of " << argv[2]
                  << " is " << graph.longestChain(argv[2]) << "." << std::endl;
    }
    else if (command == "-longest"){
        std::cout << "The length of the longest chain in " << argv[argc - 1] << " is " << graph.longestChain() << "." << std::endl;
    }
    else if (command == "-indegree"){
        int counter = graph.degreeOfDependency(argv[2]);
        std::cout << "The number of courses that directly require" << argv[2]
                  << " as a prerequisite is " << counter << "." << std::endl;
    }
    else {
        std::cout << "Command not recognized!";
    }
    return 0;
};

/** ***************************************************************************
 * Make sure that the filename passed as a command-line argument is a valid,
 * readable file. This does not necessarily mean that it is a correctly
 * formatted JSON file.
 *
 * Will exit the program with error if the file cannot be opened or cannot
 * be read.
 *
 * This is also an example of a function that uses the provided error
 * messages but extends them with additional, situation-specific information.
 *
 * @param jsonFileName: the command-line argument, which should be the name
 *          of a valid, readable file
 **************************************************************************** */
void verifyReadableInputFile(char* jsonFileName) {
    std::fstream inputStream;
    inputStream.open(jsonFileName, std::ios::in);

    if (!inputStream.is_open()) {
        std::cerr << errorMessages[E_BAD_INPUT_FILE] << jsonFileName << std::endl;
        exit(E_BAD_INPUT_FILE);
    }
    inputStream.close(); // close file! Parser will reopen it later.
}
