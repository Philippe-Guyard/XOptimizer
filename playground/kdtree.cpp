#include <iostream>
#include <array>
#include <memory>
#include <stdexcept>
#include <cmath>

#include "kd_tree.h"

/*
 * Inspired by https://github.com/crvs/KDTree
 */



double KdTreeNode::coord_at(int index) {
    if (index < 0 || index >= k)
        throw std::invalid_argument("Invalid index for KdTreeNode");

    return value[index];
}

double KdTreeNode::dist2(const KdTreeNode<k>& other) const {
    double result = 0;
    for(int i = 0; i < k; ++i)
        result += (value[i] - other.value[i]) * (value[i] - other.value[i]);

    return result;
}


template<size_t k>
class KdTreeNode {
using KdTreeNodePtr = std::shared_ptr<KdTreeNode<k>>;

private:
    KdTreeNodePtr left, right;
    std::array<double, k> value;
public:
    KdTreeNode(const std::array<double, k>& value, KdTreeNodePtr left, KdTreeNodePtr right) {
        this->value = std::array<double, k>(value);
        this->left = left;
        this->right = right;
    }

    KdTreeNode(const std::array<double, k>& value) : KdTreeNode(value, nullptr, nullptr) {}

    double coord_at(int index) {
        if (index < 0 || index >= k)
            throw std::invalid_argument("Invalid index for KdTreeNode");

        return value[index];
    };

    double dist2(const KdTreeNode<k>& other) const {
        double result = 0;
        for(int i = 0; i < k; ++i)
            result += (value[i] - other.value[i]) * (value[i] - other.value[i]);

        return result;
    }

    void add_children() {

    }
};

class KdTree {
private:

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
