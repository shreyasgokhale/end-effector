//
// Created by shreyas on 28.11.20.
//

#ifndef END_EFFECTOR_ASSIGNMENT_ROBOT_H
#define END_EFFECTOR_ASSIGNMENT_ROBOT_H


#include <utility>

class Link{

private:

    float x1,y1, length = 0;
    double theta = 0;
public:
    double getTheta() const;

private:
    std::pair<float,float> origin = {x1, y1};

public:
    Link(float x, float y, float length, double thetaInDeg);


    bool initLink(float x1, float y1, float x2, float y2);


    const std::pair<float, float> &getOrigin() const;


    float getLength() const;
    void setLength(float length);
    void setOrigin(const std::pair<float, float> &origin);
    void setOrigin(float x, float y);

    Link();

    double getThetaDeg() const;
};


#endif //END_EFFECTOR_ASSIGNMENT_ROBOT_H
