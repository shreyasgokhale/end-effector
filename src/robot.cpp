//
// Created by shreyas on 28.11.20.
//

#include "../include/robot.h"
#include "math.h"

// https://gist.github.com/dbrockman/4773781
#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)


float calculateAngle(float x1, float y1, float x2, float y2)
{
    return atan((y2- y1)/(x2-x1));

}

float calculateLength(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) );
}

const std::pair<float, float> &Link::getOrigin() const {
    return origin;
}

void Link::setOrigin(const std::pair<float, float> &origin) {
    Link::origin = origin;
}

void Link::setOrigin(const float x, const float y) {
    Link::x1 = x;
    Link::y1 = y;
    Link::origin = std::make_pair(x, y);
}

float Link::getLength() const {
    return length;
}

void Link::setLength(float length) {
    Link::length = length;
}

/**
 * Constructor
 * Initializes Link using x,y, length and thetaInDeg
 * @param x, y : Origin coordinates of the Link
 * @param length : Length of the Link
 * @param thetaInDeg : Angle made by Link with respect to the x axis, in degrees
 */
Link::Link(float x, float y, float length, double thetaInDeg) : x1(x), y1(y), length(length), theta(degreesToRadians(thetaInDeg)) {
    Link::origin = std::make_pair(x, y);
}




bool Link::initLink(float x1, float y1, float x2, float y2) {
    Link::setOrigin(x1, y1);
    Link::length = calculateLength(x1, y1, x2, y2);
    Link::theta = calculateAngle(x1, y1, x2, y2);

    return true;
}

Link::Link() {

}

double Link::getTheta() const {
    return theta;
}

double Link::getThetaDeg() const {
    return radiansToDegrees(theta);
}


