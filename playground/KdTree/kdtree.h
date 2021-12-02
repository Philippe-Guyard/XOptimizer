#include <iostream>
#include <array>
#include <memory>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <vector>


#pragma once


/*
 * Inspired by https://github.com/crvs/KDTree
 */

using pointIndex = typename std::pair< std::vector< double >, size_t >;
using pointIndexArr = typename std::vector< pointIndex >;

template<size_t k> class KdTreeNode{
public:
    using KdTreeNodePtr = std::shared_ptr<KdTreeNode>;

    KdTreeNode();

    KdTreeNode(const std::array<double, k>&, KdTreeNodePtr, KdTreeNodePtr);

    KdTreeNode(const std::array<double, k>&);

    double coord_at(int);

    double dist2(const KdTreeNode<k>& other) const;

private:
    KdTreeNodePtr left, right;
    std::array<double, k> value;
};

template<size_t k> using KdTreeNodePtr = std::shared_ptr< KdTreeNode<k> >;
template<size_t k> KdTreeNodePtr<k> NewKdTreeNodePtr();

using point_t = std::vector< double >;
using pointVec = std::vector< point_t >;


template<size_t k> class KdTree {
    using KDNodePtr = std::shared_ptr<KdTreeNode<k>>;
    using pointIndex = typename std::pair< std::vector< double >, size_t >;
    using pointIndexArr = typename std::vector< pointIndex >;
public:
    KdTree(pointVec point_array);
private:
    std::shared_ptr<KdTreeNode<k>> root;
    std::shared_ptr<KdTreeNode<k>> leaf;

    KDNodePtr make_tree(const pointIndexArr::iterator &begin,  //
                         const pointIndexArr::iterator &end,    //
                         const size_t &length,                  //
                         const size_t &level                    //
     );
};

class comparer {
   public:
    size_t idx;
    explicit comparer(size_t idx_);
    inline bool compare_idx(
        const std::pair< std::vector< double >, size_t > &,  //
        const std::pair< std::vector< double >, size_t > &   //
    );
};

