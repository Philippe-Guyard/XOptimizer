#include <iostream>
#include <array>
#include <memory>
#include <stdexcept>
#include <cmath>
#pragma once


/*
 * Inspired by https://github.com/crvs/KDTree
 */

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

    double coord_at(int index);

    double dist2(const KdTreeNode<k>& other) const;

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
