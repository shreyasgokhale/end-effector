cmake_minimum_required(VERSION 3.18)
project(end_effector_assignment)

set(CMAKE_CXX_STANDARD 11)

add_executable(end_effector_assignment main.cpp src/robot.cpp include/robot.h)