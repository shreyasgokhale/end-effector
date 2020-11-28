#include <iostream>
#include "include/robot.h"
#include "math.h"

int main() {

    Link l1 = Link(0,0,1,30);
    Link l2;
    l2.initLink(2,2,4,4);

    std::cout << "Length of L1: " << l1.getLength() << std::endl;
    std::cout << "Theta of L1 in rad: " << l1.getTheta() << std::endl;

    std::cout << "Length of L2: " << l2.getLength() << std::endl;
    std::cout << "Theta of L2: " << l2.getThetaDeg() << std::endl;


    return 0;
}
