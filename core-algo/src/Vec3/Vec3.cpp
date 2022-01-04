#include "Vec3.hpp"


Vec3::Vec3(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

// Done assuming the angles are in degrees, if radians replace with angle*180/pi
Vec3::Vec3(double theta, double phi){
    
    // Later change this to a static attribute
    double R_earth = 6371000; // in m

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


/**

ArrayVec3 class

**/


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

std::vector< int > match_function_0(ArrayVec3 arr1, ArrayVec3 arr2){
/**
* This is the function that will receive sets of Vec3 arr1 and arr2, and will return
* the minimum cost matching between the points in arr1 and arr2.
*
* Cost here is arbitrary because it currently uses a heuristic method to do this matching.
*
* Temporary name because no better name came to mind.
*
* INPUT:
*   Requirement: arr1 and arr2 need to have the same size.
*
* RETURN:
*   vector<int> : A vector with arr2.size() entries, each of them corresponding to
*   the cluster assigned to each inventory in arr1 (respecting the positions).
*
*/

    if(arr1.size() != arr2.size()){
        throw std::exception();
    }

    // n^2 naive way of doing it:
    int n = arr2.size();
    std::vector<bool> chosen(n, false);
    std::vector<int> res(n, 0);

    for(int i=0; i<n; ++i){

        long double min_dist2 = std::numeric_limits<long double>::max();
        int best_index = -1;

        for(int j=0; j<n; ++j){

            if(chosen[j]){
                continue;
            }

            if( dist2(arr1[i], arr2[j]) <= min_dist2 ){
                best_index = j;
                min_dist2 = dist2(arr1[i], arr2[j]);
            }

        }

        assert( best_index != -1 );
        res[i] = best_index;
        chosen[best_index] = true;
    }

    return res;
}

std::vector< ArrayVec3 > match_function_1(ArrayVec3 arr1, ArrayVec3 arr2){
/**
* This is the function that will receive the inventories as arr1, the clients as arr2
* and will match them accordingly.
*
* Temporary name because no better name came to mind.
*
* RETURN:
*   vector<ArrayVec3> : A vector with arr1.size() entries, each of them corresponding to
*   the cluster assigned to each inventory in arr1 (respecting the positions).
*
*/
    // Clusters the clients into up to arr1.size() clusters
    std::vector< std::vector<int> > clusters = arr2.k_means( arr1.size() );

    std::vector< ArrayVec3 > clusters_Vec3;
    std::vector< Vec3 > centers;

    for(auto& cluster : clusters){
        // cluster contains the indices of the Vec3 in the cluster
        ArrayVec3 cluster_Vec3;

        for(auto i : cluster){
            cluster_Vec3.push_back( arr2[i] );
        } // cluster_Vec3 now is an ArrayVec3 structure corresponding to the cluster

        clusters_Vec3.push_back( cluster_Vec3 );
        centers.push_back(cluster_Vec3.center_of_mass());
    }

    // Now centers is filled with the centers of the clusters
    // The default value is 0 in the case of an empty cluster
    while( centers.size() < arr1.size() ){
        clusters_Vec3.push_back( ArrayVec3() );
        centers.push_back( Vec3(0,0,0) );
    }

    std::vector<int> matching = match_function_0(arr1, centers);

    std::vector<ArrayVec3> res;
    for(auto i : matching){
        res.push_back( clusters_Vec3[i] );
    }

    return res;
}
