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

template<size_t k> KdTreeNodePtr<k> NewKDNodePtr() {
    KdTreeNodePtr<k> mynode = std::make_shared< KdTreeNode<k> >();
    return mynode;
}

inline void sort_on_idx(const pointIndexArr::iterator &begin,  //
                        const pointIndexArr::iterator &end,    //
                        size_t idx) {
    comparer comp(idx);
    comp.idx = idx;

    using std::placeholders::_1;
    using std::placeholders::_2;

    std::nth_element(begin, begin + std::distance(begin, end) / 2,
                     end, std::bind(&comparer::compare_idx, comp, _1, _2));
}


template <size_t k> KdTree<k>::KdTree(pointVec point_array) {
    leaf = std::make_shared< KdTreeNode<k> >();
    // iterators
    pointIndexArr arr;
    for (size_t i = 0; i < point_array.size(); i++) {
        arr.push_back(pointIndex(point_array.at(i), i));
    }

    auto begin = arr.begin();
    auto end = arr.end();

    size_t length = arr.size();
    size_t level = 0;  // starting

    root = KdTree::make_tree(begin, end, length, level);
}

template<size_t k> KdTreeNodePtr<k> KdTree<k>::make_tree(const pointIndexArr::iterator &begin,  //
                            const pointIndexArr::iterator &end,    //
                            const size_t &length,                  //
                            const size_t &level                    //
) {
    if (begin == end) {
        return NewKdTreeNodePtr<k>();  // empty tree
    }

    size_t dim = begin->first.size();

    if (length > 1) {
        sort_on_idx(begin, end, level);
    }

    auto middle = begin + (length / 2);

    auto l_begin = begin;
    auto l_end = middle;
    auto r_begin = middle + 1;
    auto r_end = end;

    size_t l_len = length / 2;
    size_t r_len = length - l_len - 1;

    KDNodePtr left;
    if (l_len > 0 && dim > 0) {
        left = make_tree(l_begin, l_end, l_len, (level + 1) % dim);
    } else {
        left = leaf;
    }
    KDNodePtr right;
    if (r_len > 0 && dim > 0) {
        right = make_tree(r_begin, r_end, r_len, (level + 1) % dim);
    } else {
        right = leaf;
    }

    // KDNode result = KDNode();
    return std::make_shared<KdTreeNode<k>>(*middle, left, right);
}
