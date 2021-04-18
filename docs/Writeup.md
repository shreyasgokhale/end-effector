# Calculate End Effector

## First Impressions

1. The problem describes a system of links and joints which can move freely.
2. The problem statements describes everything in 2D coordinates, hence 2D system is assumed for solving this problem. One can extend this to 3D if required.

## Design Choices

1. The system needs to be user friendly, thus degree is preferred for angle unit. But internally, radians make everything easy. So appropriate conversion must be used for handling.
2. A link seems to be the smallest unit in the system. Hence, we can start by modelling class for link.

To implement the actual robot, there are multiple options

1. A C++ vector consisting of all the Link objects or pointers to Link objects in order 
2. C++ vector of joints, which is a pair of two pointers of Link objects
3. Single/ Double Linked list connecting Links with one other
4. Single/ Double Linked list connecting Joints, which hold pointers to Link objects

Following condition is mentioned for task 4

> To test for the extensibility of your code, we want to add an arbitrary number of links between link 3 end the end effector.

The way I interpret this is: One should be able to add links at the end of the current robot. But we are not going to add bunch of links in between the existing robot structure, or remove a couple (at least for now)

Considering this, we can go for option 1 for now as it is the easiest to implement. Otherwise, we can consider 2 or even 4 if it is required in future. 

Regarding pointers vs values, this is one interesting read [https://www.bfilipek.com/2014/05/vector-of-objects-vs-vector-of-pointers.html#summary](https://www.bfilipek.com/2014/05/vector-of-objects-vs-vector-of-pointers.html#summary). In our use case, we need to access the lengths/ angles of each link to calculate final angle so value based approaches will give us faster access. And as discussed before we consider that we wont change a lot of links in between. So Object Vector it is.

## Creating Model

The model uses 2 classes: Link - which controls all properties of link and Robot which ties them up together. We can add link using different ways: specifying two points or one origin point, length and theta. We can obtain both if needed. The theta is expressed in deg for user and rad internally.

When adding multiple links, we can just invoke `addLink` repeatedly with length of the link and angle to create the manipulator chain. The end point of last link will be used as the start of the next link. 

One thing to note: All the values in the code will use float, at the moment. This means that float -float multiplications will be double and converted back to float before saving. Maybe in future we can go for more precise formats. 

## Adding Tests

To test, GTest was selected as a framework as it quite powerful and easy to start with. Moreover, Google provides a CMake script, along with helpful docs so you can add the library directly at build time. 

## Task 1: Merge devel branch into master

As all the required steps for creating a model were already done, changes were merged into master branch.

## Task 2: Finding End Effector

We already have all the ingredients to find the end effector. We just need to get the end of the last link and the total angle.

But the function was giving incorrect results. This is when I realized that I made a mistake. When calculating the endpoint, the angle w.r.t. coordinate system is required, but previously, I was using just the theta of applied angle to the link. The fix was easy, adding `global_theta` variable for robot which maintains a sum of all the angles in the manipulator so far. One added benefit: This is also the end effector angle!

## Task 3: Finding Circle Intersect

For this, we just have to check if the distance between end effector point and the center of circle is less than the radius of the circle

## Task 4: Adding links

In current implementation, we can already add links effortlessly using function `addLink` . A function to remove the last link was also added.Adding- Removing middle links will require recomputing the origins of sequential link. Although it is not implemented here, it should be trivial.

If we want to the user to easily add and delete links, the IO functionality can also be added later. In this case, we can give names to the individual links and a search function can be used to find the links.

## Next?

To develop further, here are some of the TODOs that I can think of

1. Creating better tests for testing some edge cases. Using tests in more effective manner
2. Optimization of current implementations
3. Adding new functionalities and methods as mentioned above.
4. Code cleanup and better organization, Using C++ goodies, reducing reuse
5. Using Travis / CircleCI for creating auto build-test-coverage setup