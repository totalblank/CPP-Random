#pragma once

#ifndef ADT_BST_FROM_HPP
    #include "binary_search_tree.hpp"
#endif

#include <cassert>

/*
 * public members
 */
namespace ADT {

template <typename Object, typename Comparator>
BinarySearchTree<Object, Comparator>::BinarySearchTree()
    : root(nullptr), isLessThan(Comparator{}) {}

/*
 * Returns true if x in found in the tree
 */
template <typename Object, typename Comparator>
bool BinarySearchTree<Object, Comparator>::contains(const Object & x) const
{
    return contains(x, root);
}

/*
 * Insert x into the tree; duplicates are ignored
 */
template <typename Object, typename Comparator>
void BinarySearchTree<Object, Comparator>::insert(const Object & x)
{
    insert(x, root);
}

}

/*
 * private members
 */

namespace ADT {

/*
 * Internal method to test if an item is in a subtree.
 * x is item to search for.
 * t is the node that roots the subtree
 */
template <typename Object, typename Comparator>
bool BinarySearchTree<Object, Comparator>::contains(const Object & x, BinaryNode *t) const
{
    if (t == nullptr)
        return false;
    else if (isLessThan(x, t->element))
        return contains(x, t->left);
    else if(isLessThan(t->element, x))
        return contains(x, t->right);
    else
        return true; // Match
}

/*
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <typename Object, typename Comparator>
typename BinarySearchTree<Object, Comparator>::BinaryNode*
BinarySearchTree<Object, Comparator>::findMax(BinaryNode* t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

/*
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <typename Object, typename Comparator>
typename BinarySearchTree<Object, Comparator>::BinaryNode*
BinarySearchTree<Object, Comparator>::findMin(BinaryNode* t) const
{
    if (t != nullptr)
        while(t->right != nullptr)
            t = t->right;
    return t;
}

/*
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree
 * Set the new root of the subtree
 */
template <typename Object, typename Comparator>
void BinarySearchTree<Object, Comparator>::insert(const Object & x, BinaryNode *& t)
{
    if (t == nullptr)
        t = new BinaryNode{ x, nullptr, nullptr };
    else if (isLessThan(x, t->element))
        insert(x, t->left);
    else if (isLessThan(t->element, x))
        insert(x, t->right);
    else ; // Duplicate; do nothing
}

}
