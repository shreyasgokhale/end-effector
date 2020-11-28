//
// Created by shreyas on 28.11.20.
//

#include <iostream>
#include <utility>
#include "../include/robot.h"

Robot::Robot(std::string name) : name(std::move(name)) {}

bool Robot::addLink(Link l) {

//  Check if the end of the first link matches the start of the second link
    if (manipulator.empty()) {
        std::pair<float, float> o = l.getOrigin();

#ifdef DEBUG
        std::cout << "ORIGIN X = " << o.first << " Y = " << o.second << std::endl;
#endif
//      Check if the first link insertion has 0,0 origin
        if (!(o.first == 0.0 && o.second == 0.0)) {
            std::cerr << "Link origin does not match system origin" << std::endl;
            return false;
        }
    } else {
        std::pair<float, float> e = manipulator.back().getEnd();
        std::pair<float, float> o = l.getOrigin();

#ifdef DEBUG
        std::cout << "ORIGIN X = " << o.first << " Y = " << o.second << std::endl;
        std::cout << "END X = " << e.first << " Y = " << e.second << std::endl;
#endif

        if (e != o) {
            std::cerr << "Link origin does not match end of last element" << std::endl;
            return false;
        }
    }

    Robot::manipulator.push_back(l);
    std::cout << "Link Added!" << std::endl;
    return true;
}


bool Robot::addLink(float length, float theta) {
    Link l;
    if (manipulator.empty())
        l = Link(0.0, 0.0, length, theta);
    else {
        l = Link(manipulator.back().getEnd(), length, theta);
    }

#ifdef DEBUG
    std::cout << "ORIGIN X = " << l.getOrigin().first << " Y = " << l.getOrigin().second << std::endl;
    std::cout << "END X = " << l.getEnd().first << " Y = " << l.getEnd().second << std::endl;
#endif

    Robot::manipulator.push_back(l);
    std::cout << "Link Added!" << std::endl;
    return true;
}

void Robot::printStructure() {
    if (!manipulator.empty()) {
        for (auto it:manipulator) {
            std::pair<float, float> origin = it.getOrigin();
            std::cout << "( " << origin.first << "," << origin.second << ") --> ";
        }
        std::cout << "( " << manipulator.back().getEnd().first << "," << manipulator.back().getEnd().second << ") "
                  << std::endl;
    } else {
        std::cerr << "Manipulator is empty" << std::endl;
    }
}

