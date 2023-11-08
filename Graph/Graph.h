//
// Created by Ethan Edwards on 11/1/2023.
//

#ifndef CANBETAKENTOGETHER_GRAPH_H
#define CANBETAKENTOGETHER_GRAPH_H


#include<map>
#include<vector>
#include<stack>
#include<iostream>

#include "CourseNode.h"

class Graph {
public:
    Graph();
    void buildGraph(const std::map<std::string, std::vector<std::string>> &);
    void printGraph();

    std::vector<std::string> pathFromTo(std::string fromNodeLabel, std::string toNodeLabel);
    bool canBeTakenConcurrently(std::string node1Label, std::string node2Label);
    void prerequisiteChainsFor(std::string courseID, std::vector<std::vector<std::string>> &prerequisiteChains);
    bool isCyclic();
    int degreeOfDependency(std::string courseID); // How many courses directly depend on this courseID?
    int longestChain();        // among all course IDs
    int longestChain(std::string courseID); // that starts with course ID
    bool isALabel(std::string courseID);    // membership test -- is courseID the label of a graph node?

private:
    std::map<std::string, CourseNode *> graphMap;
    // You will have to define private helper functions for a few of the functions that traverse the
    // graph recursively.

    bool isCyclicHelper(std::string courseID);
    bool pathFromToHelper(std::string fromNodeLabel, std::string toNodeLabel, std::vector<std::string> &path);
    void prereqGetter(std::string init, std::string courseID, std::vector<std::pair<bool, std::vector<std::string>>>& chains);

};


#endif //CANBETAKENTOGETHER_GRAPH_H
