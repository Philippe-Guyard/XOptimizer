#include <iostream>
#include "kdtree.h"

/*
 * Inspired by https://github.com/crvs/KDTree
 */

template<size_t k> KdTreeNode<k>::KdTreeNode(const std::array<double, k>& value, KdTreeNodePtr left, KdTreeNodePtr right){
    this->value = std::array<double, k>(value);
    this->left = left;
    this->right = right;
}

template<size_t k> KdTreeNode<k>::KdTreeNode(const std::array<double, k>& value){
     KdTreeNode(value, nullptr, nullptr);
}

template<size_t k> double  KdTreeNode<k>::coord_at(int index) {
    if (index < 0 || index >= k)
        throw std::invalid_argument("Invalid index for KdTreeNode");
    return value[index];
}

template<size_t k> double KdTreeNode<k>::dist2(const KdTreeNode<k>& other) const {
    double result = 0;
    for(int i = 0; i < k; ++i)
        result += (value[i] - other.value[i]) * (value[i] - other.value[i]);
    return result;
}

template<size_t k> std::shared_ptr<KdTreeNode<k>> NewKDNodePtr() {
    std::shared_ptr<KdTreeNode<k>> mynode = std::make_shared< KdTreeNode<k> >();
    return mynode;
    //return nullptr;
}

// Bubblesort
template<size_t k> inline void sort(std::vector<std::array<double, k>> point_array, const int &length, const size_t &level){

    for (int i = 0; i < length-1; i ++){
        for (int j = 0; j <length - i -1; j++){
            if (point_array[j][level] > point_array[j+1][level]){
                std::array<double,k> temp = point_array[j];
                point_array[j] = point_array[j+1];
                point_array[j+1] = temp;
            }
        }
    }
}

template <size_t k> KdTree<k>::KdTree(std::vector<std::array<double, k>> point_array){

    size_t length = point_array.size();
    size_t level = 0;

    root = KdTree<k>::make_tree(point_array, length, level);
}


template<size_t k> KdTreeNodePtr<k> KdTree<k>::make_tree(std::vector<std::array<double, k>> point_array ,  //
                            const size_t &length,                  //
                            const size_t &level                    //
) {
    if (length == 0){
        return nullptr;
    }

    size_t dim = k;

    if (length > 1){
        sort(point_array, length, level);
    }

    const size_t middle = floor(length/2);
    std::vector<std::array<double, k>> left_vector(point_array.begin(), point_array.begin() + middle);
    std::vector<std::array<double, k>> right_vector(point_array.begin() + middle, point_array.end());
    size_t l_len = length/2;
    size_t r_len = length - l_len - 1;


    KDNodePtr left;
    left = make_tree(left_vector, l_len, (level + 1) % dim);

    KDNodePtr right;
    right = make_tree(right_vector, r_len, (level + 1) % dim);


    return std::make_shared<KdTreeNode<k>>(point_array[middle], left, right);
}
