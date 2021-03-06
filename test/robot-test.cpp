//
// Created by shreyas on 28.11.20.
//

#include "gtest/gtest.h"
#include "../include/robot.h"
#include "../include/link.h"
#include <memory>
#include "math.h"

// A polygon with 360 sides of length 0.1, and 1 degree; should end back at the start
TEST(AddingLinks, Add2AndRemove1Link) {
    Robot r1 = Robot("Manipulator 1");
    for (int i = 0; i < 360; i++) {
        ASSERT_TRUE(r1.addLink(0.1, 1));
        ASSERT_TRUE(r1.addLink(0.1, 1));
        ASSERT_TRUE(r1.removeEndLink());
    }

    std::shared_ptr<float> x = std::make_shared<float>();
    std::shared_ptr<float> y = std::make_shared<float>();
    std::shared_ptr<float> theta = std::make_shared<float>();
    r1.getEndEffector(x, y, theta);
    EXPECT_EQ(*theta, float(360));
    EXPECT_EQ(trunc(*x), 0);
    EXPECT_EQ(trunc(*y), 0);
//    r1.printStructure();
}




// A polygon with 360 sides of length 0.1, and 1 degree; should end back at the start
TEST(AddingLinks, AddManyLinks) {
    Robot r1 = Robot("Manipulator 1");
    for (int i = 0; i < 360; i++) {
        ASSERT_TRUE(r1.addLink(0.1, 1));
    }
    std::shared_ptr<float> x = std::make_shared<float>();
    std::shared_ptr<float> y = std::make_shared<float>();
    std::shared_ptr<float> theta = std::make_shared<float>();
    r1.getEndEffector(x, y, theta);
    EXPECT_EQ(*theta, float(360));
    EXPECT_EQ(trunc(*x), 0);
    EXPECT_EQ(trunc(*y), 0);
//    r1.printStructure();
}

// link structure for tests Intersection and  EndEffector is as follows
/*
                    +
                    |  (0.414,2.414)
                    |   oXXXXo (1.414,2.414)
                    |        X
                    |        X
                    |        X
                    |        o (1.414,1.414)
                    |      X
                    |    X
                    |  X
                    |X
+-------------------X--------------------+
                    |
                    |
                    |
                    |

 */

TEST(Intersection, TestIfIntersect) {
    Robot r1 = Robot("Manipulator 1");
    ASSERT_TRUE(r1.addLink(2, 45));
    ASSERT_TRUE(r1.addLink(1, 45));
    ASSERT_TRUE(r1.addLink(1, 90));
    ASSERT_TRUE(r1.isInTheCircle(2, 3, 2));
    ASSERT_FALSE(r1.isInTheCircle(-1, 1, 2));
//    r1.printStructure();
}

TEST(Intersection, TestIfDontIntersect) {
    Robot r1 = Robot("Manipulator 1");
    ASSERT_TRUE(r1.addLink(2, 45));
    ASSERT_TRUE(r1.addLink(1, 45));
    ASSERT_TRUE(r1.addLink(1, 90));
    ASSERT_FALSE(r1.isInTheCircle(-1, 1, 2));
//    r1.printStructure();
}


TEST(EndEffector, ThreeLinks) {
    Robot r1 = Robot("Manipulator 1");
    ASSERT_TRUE(r1.addLink(2, 45));
    ASSERT_TRUE(r1.addLink(1, 45));
    ASSERT_TRUE(r1.addLink(1, 90));
    std::shared_ptr<float> x = std::make_shared<float>();
    std::shared_ptr<float> y = std::make_shared<float>();
    std::shared_ptr<float> theta = std::make_shared<float>();
    r1.getEndEffector(x, y, theta);
    EXPECT_EQ(*theta, float(180));
//    r1.printStructure();
}

TEST(EndEffector, LoopTest) {
    Robot r1 = Robot("Manipulator 1");
    ASSERT_TRUE(r1.addLink(1, 90));
    ASSERT_TRUE(r1.addLink(1, 90));
    ASSERT_TRUE(r1.addLink(1, 90));
    ASSERT_TRUE(r1.addLink(1, 90));

    std::shared_ptr<float> x = std::make_shared<float>();
    std::shared_ptr<float> y = std::make_shared<float>();
    std::shared_ptr<float> theta = std::make_shared<float>();
    r1.getEndEffector(x, y, theta);

    EXPECT_EQ(*theta, float(360));

//  Due to the way math functions deal with numbers very close to zero

//  Truncate them to the nearest integer
    EXPECT_EQ(trunc(*x), 0);
    EXPECT_EQ(trunc(*y), 0);
//    r1.printStructure();
}


TEST(EndEffector, CheckTheta) {
    Robot r1 = Robot("Manipulator 1");
    ASSERT_TRUE(r1.addLink(1, 45));
    ASSERT_TRUE(r1.addLink(1, 45));

    std::shared_ptr<float> x = std::make_shared<float>();
    std::shared_ptr<float> y = std::make_shared<float>();
    std::shared_ptr<float> theta = std::make_shared<float>();
    r1.getEndEffector(x, y, theta);
    EXPECT_EQ(*theta, float(90));
}


TEST(RobotTest, CanAddOneLink) {
    Robot r1 = Robot("Manipulator 1");
    Link l1 = Link(0.0, 0.0, 1, 45);
    ASSERT_TRUE(r1.addLink(l1));
}


TEST(RobotTest, CanAddMultipleLinks) {
    Robot r1 = Robot("Manipulator 1");
    Link l1 = Link(0.0, 0.0, 1, 45);
    Link l2 = Link(std::make_pair(3, 4), 1, 45);
    ASSERT_TRUE(r1.addLink(l1));

//  Intentional Wrong link whose start does not match the end of the last link
    ASSERT_FALSE(r1.addLink(l2));
    ASSERT_TRUE(r1.addLink(1, 45));
}


TEST(LinkTest, CheckGetLength) {
    Link l1;
    l1.initLink(1, 0, 3, 0);
    EXPECT_EQ(float(l1.getLength()), float(2));
}


TEST(LinkTest, CheckGetThetaDeg) {
    Link l1;
    l1.initLink(1, 1, 2, 2);
    EXPECT_EQ(float(l1.getThetaDeg()), float(45));
}


TEST(LinkTest, CheckGetTheta) {
    Link l1;
    l1.initLink(0, 1, 0, 6);
    EXPECT_EQ(float(l1.getTheta()), (float) M_PI / 2);
}