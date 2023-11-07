//
// Created by Ethan Edwards on 11/1/2023.
//

#include "Graph.h"

#include <utility>

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

bool Graph::pathFromToHelper(std::string fromNodeLabel, std::string toNodeLabel, std::vector<std::string> &path) {
    if (fromNodeLabel == toNodeLabel){
        path.push_back(graphMap[fromNodeLabel]->courseID());
        graphMap[fromNodeLabel]->onPath() = true;
        return true;
    }
    if (graphMap[fromNodeLabel]->prereqNodes().empty() || graphMap[fromNodeLabel]->onPath()){
        return false;
    }
    for (auto & i : graphMap[fromNodeLabel]->prereqNodes()){
        if (pathFromToHelper(i->courseID(), toNodeLabel, path)){
            path.push_back(graphMap[fromNodeLabel]->courseID());
            graphMap[fromNodeLabel]->onPath() = true;
            return true;
        }
    }
    return false;
}

std::vector<std::string> Graph::pathFromTo(std::string fromNodeLabel, std::string toNodeLabel) {
    std::vector<std::string> path;
    pathFromToHelper(std::move(fromNodeLabel), std::move(toNodeLabel), path);
    return path;
}

bool Graph::canBeTakenConcurrently(std::string node1Label, std::string node2Label) {
    // NIGHTMARE NIGHTMARE NIGHTMARE
}

void Graph::prereqChainsHelper(std::string courseID, std::vector<std::vector<std::string>> &chains){
    if (graphMap[courseID]->prereqNodes().empty()){
        std::vector<std::string> chain;
        chain.push_back(courseID);
        chains.push_back(chain);
        return;
    }
    for (auto & i : graphMap[courseID]->prereqNodes()){
        prereqChainsHelper(i->courseID(), chains);
        for (auto & j : chains){
            if (std::find(j.begin(), j.end(), courseID) == j.end()) {

                j.push_back(courseID);
            }
        }
    }
}

void Graph::prerequisiteChainsFor(std::string courseID, std::vector<std::vector<std::string>> &prerequisiteChains) {
    prereqChainsHelper(std::move(courseID), prerequisiteChains);
}

bool Graph::isCyclic() {
    return false;
}

int Graph::degreeOfDependency(std::string courseID) {
    int counter = 0;
    for (auto&[key, value] : graphMap){
        for (auto & i : value->prereqNodes()){
            if (i->courseID() == courseID){
                counter++;
            }
        }
    }
    return counter;
}

int Graph::longestChain() {
    // HELL HELL HELL HELL
}

int Graph::longestChain(std::string courseID) {
    // HELL HELL HELL HELL
}

bool Graph::isALabel(std::string courseID) {
    return graphMap.find(courseID) != graphMap.end();
}

