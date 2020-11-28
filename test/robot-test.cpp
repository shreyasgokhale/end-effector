//
// Created by shreyas on 28.11.20.
//

#include "gtest/gtest.h"
#include "../include/robot.h"
#include "../include/link.h"
#include "math.h"

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