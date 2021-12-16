#pragma once

#include<iostream>
#include<math.h>
#include<vector>
#include<assert.h>

#include<cstdio>
#include<time.h>
#include<math.h>

#include<random>

#include<algorithm>

class Vec3{

public:

    Vec3();
    Vec3(double x, double y, double z);

    Vec3(double theta, double phi);

    ~Vec3();

    double get_x() const;
    double get_y() const;
    double get_z() const;

    void set_x(double x);
    void set_y(double y);
    void set_z(double z);

    double norm2() const;
    double norm() const;


    // OPERATORS

    Vec3 operator+(const Vec3& u)   const;
    Vec3 operator-(const Vec3& u)   const;
    Vec3 operator-()    const;

protected:

    double x,y,z;

};

double dist2(Vec3 u, Vec3 v);

double dist(Vec3 u, Vec3 v);


std::ostream &operator<<(std::ostream &os, const Vec3& v);


template<typename R>
Vec3 operator*(const Vec3& v, R r){
    return Vec3(r*v.get_x(), r*v.get_y(), r*v.get_z());
}

template<typename R>
Vec3 operator*(R r, const Vec3& v){
    return v*r;
}

template<typename R>
Vec3 operator/(const Vec3& v, R r){
    if(r < 1e-7){
        throw std::overflow_error("Divide by 0 exception.");
    }

    return Vec3(v.get_x()/r, v.get_y()/r, v.get_z()/r);
}

/////////////////////////////////////////////////////////
// ArrayVec3 class

class ArrayVec3{

public:
    ArrayVec3();
    ArrayVec3(std::vector<Vec3> points);
    ~ArrayVec3();

    Vec3 operator[](int i)   const;
    void set_entry(int i, Vec3 v);

    int size()  const;

    void clear();
    void push_back(Vec3 v);

    // Methods for clustering
    Vec3 center_of_mass()   const;
    double cost_of_array()   const;

    // Helper Functions
    int find_closest_point(Vec3 v)  const;


    // Clustering
    std::vector< std::vector<int> > k_means(int num_clusters)    const;


protected:
    std::vector<Vec3> points;

};


std::ostream &operator<<(std::ostream &os, const ArrayVec3& A);


std::vector< int > match_function_0(ArrayVec3 arr1, ArrayVec3 arr2);
std::vector< ArrayVec3 > match_function_1(ArrayVec3 arr1, ArrayVec3 arr2);
