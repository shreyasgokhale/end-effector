//
// Created by shreyas on 28.11.20.
//

#ifndef END_EFFECTOR_ASSIGNMENT_ROBOT_H
#define END_EFFECTOR_ASSIGNMENT_ROBOT_H

#include <string>
#include "robot.h"
#include "vector"
#include "link.h"

class Robot{

public:
    Robot(const std::string &name);

    bool addLink(Link l);
    bool addLink(float length, float theta);
    void printStructure();


private:
    std::string name;
    std::vector <Link> manipulator = {};

};



#endif //END_EFFECTOR_ASSIGNMENT_ROBOT_H
