#pragma once

#ifndef ADT_BST_FROM_HPP
    #include "binary_search_tree.hpp"
#endif

#include <cassert>
#include <iostream>
#include <utility>

namespace ADT {

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
    : root(nullptr) {}

}
