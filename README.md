## Calculate End Effector

### Building and Running
For building, make sure you have CMake 3.18+ installed.

From root folder, run following commands. This will also download the GTest 
framework in your build folder.

```shell script
mkdir build
cd build
cmake ../
make
```

From build folder, execute following
 
```shell script
./end_effector
```
This will run 12 predefined tests

### Structure
The code is structured in 3 folders with respective functions.

```
include/
src/
test/
docs/
```
When main is executed, it runs all the test cases present in `test/robot-test.cpp`

You can add your own tests or even use main file directly.

For debugging, use function `Robot::printStructure()` to print the current manipulator structure.

For more clarifications, have a look at [writeup](docs/Writeup.md).