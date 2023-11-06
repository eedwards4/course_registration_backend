//
// Created by Ethan Edwards on 11/1/2023.
//

#include "CourseNode.h"

void CourseNode::addPrereqNode(CourseNode *node) {
    _prereqNodes.push_back(node);
}
