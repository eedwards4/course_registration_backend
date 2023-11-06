//
// Created by Ethan Edwards on 11/1/2023
//

#include <iostream>
#include <fstream>

#include "constants.hpp"
#include "Parser/Parser.hpp"
#include "Graph/Graph.h"

void verifyReadableInputFile(char* jsonFileName);

int main(int argc, char *argv[]) {
    // Make sure that the executable was given exactly 2 command-line argument
    /*
    if (argc != 3) {
        std::cerr << errorMessages[E_WRONG_NUMBER_ARGS] << std::endl;
        exit(E_WRONG_NUMBER_ARGS);
    }
     */

    //for (int i = 0; i < argc; i++){
    //    std::cout << i << " " << argv[i] << "\n";
    //}

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
        graph.printGraph();
    }

    if (command == "-cyclic"){
        std::cout << "The graph induced by " << argv[argc - 1];
        if (!graph.isCyclic()){
            std::cout << " does not";
        }
        std::cout << " contains a cycle." << std::endl;
    }
    else if (command == "-includes"){ // Determines whether the map includes a course
        for (auto&[key, value] : requisiteMap){
            if (key == argv[2]){
                std::cout << argv[argc - 1] << " includes " << argv[2] << "." << std::endl;
                return 0;
            }
        }
        std::cout << argv[argc - 1] << " does not include " << argv[2] << "." << std::endl;
    }
    else if (command == "-together"){

    }
    else if (command == "-allpairs"){

    }
    else if (command == "-chains"){

    }
    else if (command == "-length"){

    }
    else if (command == "-print"){
        graph.printGraph();
    }
    else if (command == "-longest"){

    }
    else if (command == "-indegree"){

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
