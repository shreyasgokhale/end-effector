//
// Created by shreyas on 28.11.20.
//


#include "../include/robot.h"


// https://gist.github.com/dbrockman/4773781
#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)


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
        std::pair<float, float> e = manipulator.back().getEnd(global_theta);
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
    Robot::global_theta += l.getTheta();

#ifdef DEBUG
    std::cout << "Link Added!" << std::endl;
#endif
    return true;
}


bool Robot::addLink(float length, float theta) {
    Link l;
    if (manipulator.empty())
        l = Link(0.0, 0.0, length, theta);
    else {
        l = Link(manipulator.back().getEnd(global_theta), length, theta);
    }

#ifdef DEBUG
    std::cout << "ORIGIN X = " << l.getOrigin().first << " Y = " << l.getOrigin().second << std::endl;
    std::cout << "END X = " << l.getEnd(global_theta).first << " Y = " << l.getEnd(global_theta).second << std::endl;
#endif

    Robot::manipulator.push_back(l);
    Robot::global_theta += l.getTheta();

#ifdef DEBUG
    std::cout << "Link Added!" << std::endl;
#endif

    return true;
}

void Robot::printStructure() {
    if (!manipulator.empty()) {
        for (auto it:manipulator) {
            std::pair<float, float> origin = it.getOrigin();
            std::cout << "(" << origin.first << "," << origin.second << ") --> ";
        }
        std::cout << "(" << manipulator.back().getEnd(global_theta).first << "," << manipulator.back().getEnd(global_theta).second << ") "
                  << std::endl;
    } else {
        std::cerr << "Manipulator is empty" << std::endl;
    }
}


void Robot::getEndEffector( const std::shared_ptr<float>& x,  const std::shared_ptr<float>& y,  const std::shared_ptr<float>& theta){
    *x = (float) manipulator.back().getEnd(global_theta).first;
    *y = (float) manipulator.back().getEnd(global_theta).second;
    *theta = radiansToDegrees(global_theta);
}

Robot::~Robot() {

}
