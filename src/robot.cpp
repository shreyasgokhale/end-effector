//
// Created by shreyas on 28.11.20.
//


#include "../include/robot.h"


// https://gist.github.com/dbrockman/4773781
#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)


double calculateDistance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) +
                      pow(y2 - y1, 2));
}


Robot::Robot(std::string name) : name(std::move(name)) {}

/**
 * Add link to the manipulator
 * @param l: Link object
 * @return true if success
 */
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
            std::cerr << "Link origin does not match the end of last element! " << std::endl;
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

/**
 * Add link dirctly to the existing manipulator
 * @param length : Length of the link in units
 * @param theta : Angle made by link w.r.t the previous link
 * @return true if link added successfully
 */
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

bool Robot::removeEndLink(){
    if (manipulator.empty()) {
        std::cerr << "Manipulator Empty!" << std::endl;
        return false;
    }
    this->global_theta -= this->manipulator.back().getTheta();
    this->manipulator.pop_back();
    return true;
}



/**
 *  Prints Manipulator Structure
 */
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

/**
 * Gets position and total angle of end effector
 * @param x : pointer of x coordinate
 * @param y : pointer of y coordinate
 * @param thetaP : pointer of the total angle thetaP
 */
void Robot::getEndEffector( const std::shared_ptr<float>& x,  const std::shared_ptr<float>& y,  const std::shared_ptr<float>& thetaP){
    *x = (float) manipulator.back().getEnd(global_theta).first;
    *y = (float) manipulator.back().getEnd(global_theta).second;
    *thetaP = radiansToDegrees(global_theta);
#ifdef DEBUG
    std::cout << "End Effector X = " << *x << " Y = " <<  *y << " Theta = " <<  *thetaP << std::endl;
#endif
}

/**
 * Finds if the end effector is in the given circle
 * @param x : x coordinate of the center of the circle
 * @param y : y coordinate of the center of the circle
 * @param r : radius of the circle
 * @return : true if in the circle, false otherwise
 */
bool Robot::isInTheCircle(float x, float y, float r){
    return (calculateDistance(manipulator.back().getEnd(global_theta).first,
                            manipulator.back().getEnd(global_theta).second, x, y) <= r);
}

Robot::~Robot() {

}
