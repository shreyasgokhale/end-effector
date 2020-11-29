//
// Created by shreyas on 28.11.20.
//

#ifndef END_EFFECTOR_ASSIGNMENT_ROBOT_H
#define END_EFFECTOR_ASSIGNMENT_ROBOT_H

#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include "robot.h"
#include "vector"
#include "link.h"
#include "math.h"


class Robot {

public:
    Robot(std::string name);

    virtual ~Robot();

    bool addLink(Link l);

    bool addLink(float length, float theta);

    void printStructure();

    void getEndEffector(const std::shared_ptr<float> &x, const std::shared_ptr<float> &y,
                        const std::shared_ptr<float> &theta);

private:
    std::string name;
    std::vector<Link> manipulator = {};
    double global_theta = 0;

};


#endif //END_EFFECTOR_ASSIGNMENT_ROBOT_H
