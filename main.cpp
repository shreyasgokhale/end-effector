#include <iostream>
#include "include/link.h"
#include "math.h"
#include "include/robot.h"

int main() {

//    Link l2;
//    l2.initLink(1,1,4,4);

//    std::cout << "Length of L1: " << l1.getLength() << std::endl;
//    std::cout << "Theta of L1 in rad: " << l1.getTheta() << std::endl;
//
//    std::cout << "Length of L2: " << l2.getLength() << std::endl;
//    std::cout << "Theta of L2: " << l2.getThetaDeg() << std::endl;

    Robot r1 = Robot("Manipulator 1");

  //
//    r1.addLink(l2);
//    r1.printStructure();
    Link l1 = Link(0.0,0.0,1,45);

    r1.addLink(l1);
    r1.addLink(1, 45);
    r1.addLink(2, 30);

    r1.printStructure();


    return 0;
}
