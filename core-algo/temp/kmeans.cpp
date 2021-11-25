#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<random>

#include<vector>
#include<cstdio>

double compute_distance(std::pair<int, int> p1, std::pair<int, int> p2){
    int x1 = p1.first;
    int y1 = p1.second;
    int x2 = p2.first;
    int y2 = p2.second;
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


/*
* IMPORTANT:
*
*   k_means should actually return a vector<vector<int>> with each inner vector<int> containing the indices of the points in that cluster.
* That is, you use the indices in the vector points.
*
*/


// Maybe these function will make it easier to code 

int find_closest_point(std::pair<double, double> point,const std::vector< std::pair<double, double> >& list_of_points){

    int index_best = 0;
    double distance_best = compute_distance(point , list_of_points[0]);

    for(int i=1; i<list_of_points.size(); ++i){
        if( compute_distance(point, list_of_points[i]) < distance_best ){
            index_best = i;
            distance_best = compute_distance(point, list_of_points[i]);
        }
    }

    return index_best;
}

std::pair<double,double> find_center_of_mass(const std::vector< std::pair<double, double> >& list_of_points){

    std::pair<double, double> mu = {0, 0};

    for(const auto& point : list_of_points){
        mu.first += point.first;
        mu.second += point.second;
    }

    mu.first = mu.first / (EdgeWeight) list_of_points.size();
    mu.second = mu.second / (EdgeWeight) list_of_points.size();

    return mu;
}

double compute_cluster_cost(const std::vector< std::pair<double, double> >& list_of_points){

    std::pair<double, double> mu = find_center_of_mass(list_of_points);

    double total_cost = 0;
    for(auto point : list_of_points){
        total_cost += compute_distance(mu, point);
    }

    return total_cost;
}


std::vector<std::vector<std::pair<double, double> > > k_means(std::vector<std::pair<double, double> > points, int k, int max_iter, double eps){
    std::vector<std::pair<double, double> > centers;
    std::vector<std::pair<double, double> > not_centers = points;
    int n = points.size();
    
    /**
     * 
     * 
    Using random properly is difficult in c++ you can search for mersene twister to do it properly.
    
    Code:

    std::random_device dev;
    std::mt19937 rng(dev());

    rng.seed(time(0));

    std::uniform_int_distribution<std::mt19937::result_type> distr(a, b); 

    // samples an integer uniformly at random in [a,b]
    distr(rng);

    // samples another integer at random (independent from previous used samples)
    distr(rng);
    distr(rng);

    */

    // srand(time(0));

    int index = rand() % n;
    centers.push_back(points[index]);
    not_centers.erase(not_centers.begin()+index);
    std::default_random_engine generator (time(0));

    std::vector<double> dist;
    std::vector<double> min_dist;

    // initialize centers using randomization (k_means++ algorithm)

    while (centers.size() != k){
        int current_size_not_cent = not_centers.size();
        int current_size_cent = centers.size();
        
        // compute distances from chosen centers, choose minimum_distance

        for (int i = 0; i < current_size_not_cent; i++){
            for (int j = 0; j < current_size_cent; j++){
                dist.push_back(compute_distance(not_centers[i], centers[j]));
            }
            min_dist.push_back(*std::min_element(dist.begin(), dist.end()));
        }
        std::discrete_distribution<int> distribution (min_dist.begin(), min_dist.end());
        index = distribution(generator);
        centers.push_back(not_centers[index]);
        dist.clear();
        min_dist.clear();
    }

    // initialize the clusters

    std::vector<std::vector<std::pair<double, double> > > clusters;
    clusters.resize(k);
    int cluster_index = 0;
    double current_dist;
    double current_min;
    for (int i = 0; i < n; i++){
        current_min = compute_distance(points[i], centers[0]);
        for (int j = 0; j < k; j++){
            current_dist = compute_distance(points[i], centers[j]);
            if (current_dist < current_min){
                current_min = current_dist;
                cluster_index = j;
            }
        }
        clusters[cluster_index].push_back(points[i]);
    }

    // Initialize loss (used to measure convergence)

    double loss = 0;
    for (int i = 0; i < k; i++){
        for (int j = 0; j < clusters[i].size(); j++){
            loss += compute_distance(clusters[i][j], centers[i]);
        }
    }
    double new_loss;

    // body of the iterative algorithm
    int num_iter = 0;
    while(num_iter < max_iter){
        for(int i = 0; i < k; i++){
            double first = 0;
            double second = 0;
            for(int j = 0; j < clusters[i].size(); j++){
                first += clusters[i][j].first;
                second += clusters[i][j].second;
            }
            first = first/clusters[i].size();
            second = second/clusters[i].size();
            centers[i].first = first;
            centers[i].second = second;
        }
        cluster_index = 0;
        for (int i = 0; i < n; i++){
            current_min = compute_distance(points[i], centers[0]);
            for (int j = 0; j < k; j++){
                current_dist = compute_distance(points[i], centers[j]);
                if (current_dist < current_min){
                    current_min = current_dist;
                    cluster_index = j;
                }
            }
        clusters[cluster_index].push_back(points[i]);
        }
        if(num_iter >= max_iter/3){
            for (int i = 0; i < k; i++){
                for (int j = 0; j < clusters[i].size(); j++){
                    new_loss += compute_distance(clusters[i][j], centers[i]);
                }
            }        
            if(new_loss - loss <= eps){
                break;
            }
            loss = new_loss;
        }
    }

};









