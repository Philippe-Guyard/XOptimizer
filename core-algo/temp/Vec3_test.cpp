#include<iostream>
#include<math.h>
#include<vector>

#include<cstdio>
#include<time.h>
#include<math.h>

#include<random>

#include<algorithm>

#include"Vec3_temp.cpp"


int main(){
    //Testing Vec3
    // Test constructors
    std::cout << "Testing default constructor" << std::endl;
    std::cout << "Code output: " << Vec3() << std::endl;
    std::cout << "Expecting (0, 0, 0)" << std::endl;

    double x, y, z;
    x = 1;
    y = -4;
    z = 7;
    Vec3 v1 = Vec3(x, y, z);
    std::cout << "Testing standard constructor" << std::endl;
    std::cout << "Code output: " << v1 << std::endl;
    std::cout << "Expecting (" << x << ", " << y << ", " << z << ")" << std::endl;

    double phi, theta;
    phi = 30;
    theta = 67;
    std::cout << "Testing spherical-to-carteisian constructor" << std::endl;
    std::cout << "Code output: " << Vec3(theta, phi) << std::endl;
    std::cout << "Expecting (" << R_earth*sin(phi)*cos(theta) << ", " << R_earth*sin(phi)*sin(theta) << ", " << R_earth*cos(phi) << ")" << std::endl;

    // If these tests up until now function correctly, then getters and setters all work fine

    // Test norms
    std::cout << "Testing norm and norm2" << std::endl;
    std::cout << "Code output: " << v1.norm() << ", " << v1.norm2() << std::endl;
    std::cout << "Expecting " << sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) << ", " << pow(x, 2) + pow(y, 2) + pow(z, 2) << std::endl;

    // Test operators
    double x2, y2, z2, r, q;
    x2 = -7;
    y2 = 3;
    z2 = 10;
    r = 5;
    q = 2;
    Vec3 v2 = Vec3(x2, y2, z2);

    std::cout << "Code output: " << v1+v2 << std::endl;
    std::cout << "Expecting (" << x + x2 << ", " << y + y2 << ", " << z + z2 << ")" << std::endl;
    std::cout << "Code output: " << v1-v2 << std::endl;
    std::cout << "Expecting (" << x - x2 << ", " << y - y2 << ", " << z - z2 << ")" << std::endl;
    std::cout << "Code output: " << -v1 << std::endl;
    std::cout << "Expecting (" << -x << ", " << -y << ", " << -z << ")" << std::endl;
    std::cout << "Code output: " << r*v1 << std::endl;
    std::cout << "Expecting (" << r*x << ", " << r*y << ", " << r*z << ")" << std::endl;
    std::cout << "Code output: " << v2*r << std::endl;
    std::cout << "Expecting (" << r*x2 << ", " << r*y2 << ", " << r*z2 << ")" << std::endl;
    std::cout << "Code output: " << v1/q << std::endl;
    std::cout << "Expecting (" << x/q << ", " << y/q << ", " << z/q << ")" << std::endl;


    // Testing ArrayVec3
    // Test constructors
    std::cout << "Testing default constructor" << std::endl;
    std::cout << "Code output: " << ArrayVec3() << std::endl;
    std::cout << "Expecting no output (empty array)" << std::endl;

    int num_vecs = 5;
    std::vector<Vec3> points;
    points.resize(num_vecs);
    for (int i = 0; i < num_vecs; i++){
        points[i] = Vec3();
    }
    std::cout << "Testing base constructor" << std::endl;
    std::cout << "Code output: " << ArrayVec3(points) << std::endl;
    std::cout << "Expecting : (0, 0, 0)";
    for (int i = 1; i < num_vecs - 1; i++){
        std::cout << ", (0, 0, 0)";
    }
    std::cout << ", (0, 0, 0)" << std::endl;

    // Test operators (setter assumed to function)
    std::cout << "Testing [] operator" << std::endl;
    points.resize(2);
    points[0] = v1;
    points[1] = v2;
    ArrayVec3 arr = ArrayVec3(points);
    std::cout << "Code output: " << arr[0] << ", " << arr[1] << std::endl;
    std::cout << "Expecting (" << x << ", " << y << ", " << z << "), " << "(" << x2 << ", " << y2 << ", " << z2 << ")" << std::endl;

    std::cout << "Test clear operator" << std::endl;
    arr.clear();
    std::cout << "Code output: " << arr << std::endl;
    std::cout << "Expecting no output (empty array)" << std::endl;

    std::cout << "Testing push_back operator" << std::endl;
    arr.push_back(v1);
    std::cout << "Code output: " << arr << std::endl;
    std::cout << "Expecting (" << x << ", " << y << ", " << z << ")" << std::endl;

    //TODO: test clustering algorithm on Vec3 by comparing with outputs using kmeans form external libraries

}



























