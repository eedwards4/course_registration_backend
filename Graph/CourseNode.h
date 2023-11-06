//
// Created by Ethan Edwards on 11/1/2023.
//

#ifndef CANBETAKENTOGETHER_COURSENODE_H
#define CANBETAKENTOGETHER_COURSENODE_H


#include<vector>
#include<string>

class CourseNode {
public:
    explicit CourseNode(std::string id) : _courseID(std::move(id)) {};
    std::vector<CourseNode *> prereqNodes() {return _prereqNodes;}
    void addPrereqNode(CourseNode *);
    int numPrereqs() {return _prereqNodes.size();}
    std::string courseID() {return _courseID;}
    void courseID(std::string nodeName) {_courseID = nodeName;}
    bool &visited() {return _visited;}
    bool &onPath() {return _onPath;}
    bool hasPrereq() {return _prereqNodes.size() > 0;}

private:
    std::vector<CourseNode *> _prereqNodes;
    bool _visited = false;
    bool _onPath = false;
    std::string _courseID;
};


#endif //CANBETAKENTOGETHER_COURSENODE_H
