# Question

Halodi Robotics Programming Case

This case is to evaluate your coding skills and basic robotics/controls knowledge.

Rules:

- **The main goal of this case study is to evaluate your programming skills.**
    - **Correct solutions are secondary. If your code is well written and tested, fixing the mathematics should be trivial.**
- Write the code in C++.
    - Add clear build instructions and if applicable, a build file(preferably CMake).
- Feel free to look up as much as you want, but do implement the answers in your own coding style. Do not plagiarize, and provide citations if warranted.
- Do not use a kinematics library, but implement your own solution
    - You should not need a mathematics/matrix library either, but if it results in cleaner code feel free to use one.
- We are looking for good programming practises demonstrating clean, re-usable, extendable, and maintainable code. Each step builds on code written in the previous steps.
    - Feel free to make assumptions and document them if information is missing in the case.
    - If a question is unclear or you get stuck, feel free to reach out (jesper@halodi.com).
- Provide test cases using a common testing platform for your language (for example, Google Test, Boost.Test, cppunit, etc).
    - Bonus points: Use test driven development
- Add documentation where necessary. Document public API functions. Use good class, function, and variable names.
- Develop against a local git repository, and commit at least after every question.
    - If using test driven development, show that using commits
    - Send the whole repository (include the .git directory) when finished
- At the end of the case, zip up your work and send it to Linda (linda@halodi.com) and Jesper (jesper@halodi.com)

## 

## Model

You’ll be implementing the kinematics for the manipulator model shown in Figure 1. The manipulator consists of 3 links, with lengths L1, L2, and L3 and corresponding joint angles (θ1,θ2,θ3).

- Create an object oriented model of the robot to store the parameters
- Use reasonable defaults for the parameters and make them easy to change.

[https://lh6.googleusercontent.com/y1DXQ11KQe9oIUVXJzlUIpWef8oimeHZ8ANHeDTX5N3yTH2ufVxVeRiXVTAy2yL5gdL1IKZ7cbsQMXyFs6u7Ffq_VPhMsECLWDMQf2J8pMR4VAJUvS6QkspftwJaOqzWD1lLQwc](https://lh6.googleusercontent.com/y1DXQ11KQe9oIUVXJzlUIpWef8oimeHZ8ANHeDTX5N3yTH2ufVxVeRiXVTAy2yL5gdL1IKZ7cbsQMXyFs6u7Ffq_VPhMsECLWDMQf2J8pMR4VAJUvS6QkspftwJaOqzWD1lLQwc)

Figure 1: 3 DOF manipulator in the X-Y plane with end effector pose p(x,y,θp), where θp is the orientation of the end effector. The link lengths are L1, L2, and L3. The joint angles are (θ1,θ2,θ3)

## 2) Forward kinematics

We want to know the end effector position p(x,y,θp) based on the joint angles (θ1,θ2,θ3)

- Create an implementation of the forward kinematics of the manipulator using the manipulator model created in section 1).
- Create test cases for the forward kinematics
    - For example, test for sets of angles that allow easy calculation by hand

## 3) Intersection

Given a circle with midpoint (x,y) and radius r, we want to know if the end effector position p(x,y,θp) is in that circle.

- Create a function that tests if the manipulator is in the circle, given x,y,r and the joint angles (θ1,θ2,θ3)
- Provide test cases for the intersection

## 4) Adding links

To test for the extensibility of your code, we want to add an arbitrary number of links between link 3 end the end effector.

- Allow the user to add an arbitrary amount of links to the manipulator
- Make sure that the test cases you implemented for forward kinematics and intersection test work with a larger number of links.