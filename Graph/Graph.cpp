//
// Created by Ethan Edwards on 11/1/2023.
//

#include "Graph.h"

Graph::Graph() = default;

void Graph::buildGraph(const std::map<std::string, std::vector<std::string>> &requisiteMap) {
    for (auto&[key, value] : requisiteMap){
        CourseNode *courseNode = new CourseNode(key);
        if (graphMap.find(key) == graphMap.end()){
            graphMap[key] = courseNode;
        }
        for (auto & i : value){
            CourseNode *prereqNode = new CourseNode(i);
            if (graphMap.find(i) == graphMap.end()){
                graphMap[i] = prereqNode;
            }
            graphMap[key]->addPrereqNode(graphMap[i]);
        }
    }
}

void Graph::printGraph() {
    for (auto&[key, value] : graphMap){
        std::cout << key << ": ";
        int iter = 0;
        for (auto & i : value->prereqNodes()){
            std::cout << i->courseID();
            if (iter != value->prereqNodes().size() - 1){std::cout << ", ";} // If not last element, print comma
            iter++;
        }
        std::cout << std::endl;
    }
}


