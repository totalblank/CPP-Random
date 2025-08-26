#pragma once

#include <iostream>
#include <utility>
#include <functional>

namespace ADT {
    template <typename Object, typename Comparator=std::less<Object>>
    class BinarySearchTree
    {
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree & rhs);
        BinarySearchTree(BinarySearchTree && rhs);
        ~BinarySearchTree();

        const Object & findMin() const;
        const Object & findMax() const;
        bool contains(const Object & x) const;
        bool isEmpty() const;
        void printTree(std::ostream & out = std::cout) const;

        void makeEmpty();
        void insert(const Object & x);
        void insert(Object && x);
        void remove(const Object & x);

        BinarySearchTree & operator=(const BinarySearchTree & rhs);
        BinarySearchTree & operator=(BinarySearchTree && rhs);

    private:
        struct BinaryNode
        {
            Object element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode(const Object & theElement, BinaryNode *lt, BinaryNode *rt)
                : element{ theElement }, left{ lt }, right{ rt } { }
            BinaryNode(Object && theElement, BinaryNode *lt, BinaryNode *rt)
                : element{std::move( theElement ) }, left{ lt }, right{ rt } { }
        };

        BinaryNode *root;
        Comparator isLessThan;

        void insert(const Object & x, BinaryNode *& t);
        void insert(Object && x, BinaryNode *& t);
        void remove(const Object & x, BinaryNode *& t);
        BinaryNode * findMin(BinaryNode *t) const;
        BinaryNode * findMax(BinaryNode *t) const;
        bool contains(const Object & x, BinaryNode *t) const;
        void makeEmpty(BinaryNode *& t);
        void printTree(BinaryNode *t, std::ostream & out) const;
        BinaryNode * clone(BinaryNode *t) const;
    };
}


#define ADT_BST_FROM_HPP // Tell the TPP we came from the header (prevents recursive include)
#include "binary_search_tree.tpp" // Template definitions
#undef ADT_BST_FROM_HPP
