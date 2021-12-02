#include<iostream>
#include<math.h>
#include<vector>

#include<cstdio>
#include<time.h>
#include<math.h>

#include<random>

#include<algorithm>

/**
 * For Giuseppe:
 * 
 * Find the radius of the earth and write it to a constant R_earth (in km)
 * 
 * Write a constructor to Vec3 that receives two angles phi and theta (Recall that PHY102 stuff
 * that converted spherical coordinates to cartesian coordinates.) The Radius should be R_earth.
 * 
 * Test with inputs by writing a main file with small tests. You can do std::cout with Vec3 and ArrayVec3, so
 *      std::cout << Vec3(1,6,-1);
 * should work. This can help you to test.
 */

double R_earth = 6371;

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

Vec3::Vec3(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

// Done assuming the angles are in degrees, if radians replace with angle*180/pi
Vec3::Vec3(double theta, double phi){
    x = R_earth*sin(phi)*cos(theta);
    y = R_earth*sin(phi)*sin(theta);
    z = R_earth*cos(phi);

}

Vec3::Vec3(){
    x = 0;
    y = 0;
    z = 0;
}

Vec3::~Vec3(){}

// Getters and Setters:

double Vec3::get_x() const{
    return x;
}

double Vec3::get_y() const{
    return y;
}

double Vec3::get_z() const{
    return z;
}

void Vec3::set_x(double x){
    this->x = x;
}

void Vec3::set_y(double y){
    this->y = y;
}

void Vec3::set_z(double z){
    this->z = z;
}

// Norm:

double Vec3::norm2() const{
    return x*x+y*y+z*z;
}

double Vec3::norm() const{
    return sqrt(norm2());
}

// Dist:

double dist2(Vec3 u, Vec3 v){
    return (u-v).norm2();
}

double dist(Vec3 u, Vec3 v){
    return sqrt(dist(u,v));
}


// OPERATORS

std::ostream &operator<<(std::ostream &os, const Vec3& v){

    return os << "Vec3: (" << v.get_x() << "," << v.get_y() <<"," << v.get_z() << ")";
}

Vec3 Vec3::operator+(const Vec3& u)   const{
    return Vec3(x+u.get_x(), y+u.get_y(), z+u.get_z());
}

Vec3 Vec3::operator-(const Vec3& u)   const{
    return Vec3(x-u.get_x(), y-u.get_y(), z-u.get_z());
}

Vec3 Vec3::operator-()    const{
    return Vec3(-x,-y,-z);
}



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

/**

ArrayVec3 class

**/

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

ArrayVec3::ArrayVec3(){
}

ArrayVec3::ArrayVec3(std::vector<Vec3> points){
    this->points = points;
}

ArrayVec3::~ArrayVec3(){
}

std::ostream &operator<<(std::ostream &os, const ArrayVec3& A){
    /**
     * Function responsible for std::cout ArrayVec3 objects.
     * 
     */
    std::ostream& res = os << "ArrayVec3: " << "(size: " << A.size() << ")" << std::endl;
    for(int i=0; i<A.size(); ++i){
        std::cout << A[i] << " ";
    }

    return res;
}

Vec3 ArrayVec3::operator[](int i)    const{
    return points[i];
}

void ArrayVec3::set_entry(int i, Vec3 v){

    if(i >= this->size()){
        throw std::exception();
    }

    points[i] = v;
}

int ArrayVec3::size()   const{
    return points.size();
}

void ArrayVec3::clear(){
    points.clear();
}

void ArrayVec3::push_back(Vec3 v){
    points.push_back(v);
}


// Useful Functions for clustering

int ArrayVec3::find_closest_point(Vec3 v)   const{

    double min_dist2 = dist2(v, points[0]);
    int closest_index = 0;

    for(int i=1; i<this->size(); ++i){
        if( min_dist2 > dist2(v, points[i]) ){
            closest_index = i;
            min_dist2 = dist2(v, points[i]);
        }
    }

    return closest_index;
}

Vec3 ArrayVec3::center_of_mass()    const{

    if(this->size() == 0){
        return Vec3(0,0,0);
    }

    Vec3 mu;
    for(const auto& v : points){
        mu = mu+v;
    }

    return mu/(double) this->size();
}

double ArrayVec3::cost_of_array()  const{
/**
* Returns the cost of the array defined by:
*   sum (P_i - G)**2
* where P_1,...P_n are the points and G is the center of mass.
*/

    Vec3 mu = center_of_mass();
    double cost = 0;

    for(const auto& v : points){
        cost += dist2(v, mu);
    }

    return cost;
}

// Clustering

std::vector< std::vector<int> > ArrayVec3::k_means(int num_clusters)    const{

    if( num_clusters <= 0 ){
        throw std::exception();
    }

    int n = this->size();
    num_clusters = std::min(num_clusters, n);

     // not really a meaningful number
    int num_iter = 5000;


    // setting up the random device
    // #include<time.h> is necessary
    std::random_device dev;
    std::mt19937 rng(dev());
    rng.seed(time(0));
    std::uniform_int_distribution<std::mt19937::result_type> distr(0, n-1);


    std::vector< std::vector<int> > clusters;
    clusters.resize(num_clusters);

    // defines the centers randomly
    ArrayVec3 centers;

    for(int i=0; i<num_clusters; ++i){
        centers.push_back( points[distr(rng)] );
    }

    for(int iteration=0; iteration<num_iter; iteration++){

        for(int i=0; i<num_clusters; ++i){
            clusters[i].clear();
        }

        for(int i=0; i<n; ++i){
            // finds the closest cluster
            int closest_cluster = centers.find_closest_point(points[i]);

            // assigns this point to the new cluster
            clusters[closest_cluster].push_back(i);
        }

        // adjusts the values of centers

        // DEBUG STATEMENT
        //std::cout << "ITERATION " << iteration << std::endl;

        for(int i=0; i<num_clusters; i++){

            ArrayVec3 points_in_cluster;

            for(auto index : clusters[i]){
                points_in_cluster.push_back( points[index] );
            }

            centers.set_entry(i, points_in_cluster.center_of_mass());

            // DEBUG STATEMENT
            //std::cout << "CENTER: " << centers[i] << std::endl;
        }
    }

    return clusters;

}
