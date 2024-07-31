// ------------------------------------------------ bintree.h -------------------------------------------------------
// Programmer Name: Forrest Zhang
// Course Section Number: CSS 343
// Creation Date: 7/3/2024
// Date of Last Modification: 7/8/2024
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Header file for the BinTree class, which represents a binary search tree (BST) with various operations like
// insertion, retrieval, traversal, height calculation, and conversion to/from arrays.
// --------------------------------------------------------------------------------------------------------------------
// This file contains the class definition for BinTree, including constructors, destructors, operator overloads, and utility functions.
// --------------------------------------------------------------------------------------------------------------------

#pragma once
#include "nodedata.h"
#include <iostream>

using namespace std;

class BinTree {
    friend ostream& operator<<(ostream&, const BinTree&);

public:
    // Constructor: Initializes an empty binary search tree
    BinTree();

    // Copy Constructor: Creates a deep copy of another BinTree
    BinTree(const BinTree&);

    // Destructor: Calls makeEmpty to clean up dynamically allocated memory
    ~BinTree();

    // Assignment Operator: Assigns one BinTree to another with deep copy
    BinTree& operator=(const BinTree&);

    // Equality Operator: Checks if two BinTrees are equal
    bool operator==(const BinTree&) const;

    // Inequality Operator: Checks if two BinTrees are not equal
    bool operator!=(const BinTree&) const;

    // isEmpty: Returns true if the tree is empty, false otherwise
    bool isEmpty() const;

    // makeEmpty: Empties the tree by deleting all nodes
    void makeEmpty();

    // insert: Inserts a new NodeData into the tree
    bool insert(NodeData*);

    // retrieve: Retrieves a NodeData from the tree
    bool retrieve(const NodeData&, NodeData*&) const;

    // displaySideways: Displays the tree structure sideways for easier visualization
    void displaySideways() const;

    // getHeight: Returns the height of a given NodeData in the tree
    int getHeight(const NodeData&) const;

    // bstreeToArray: Converts the BST to a sorted array
    void bstreeToArray(NodeData* []);

    // arrayToBSTree: Converts a sorted array to a balanced BST
    void arrayToBSTree(NodeData* []);

private:
    struct Node {
        NodeData* data;  // Pointer to the data object
        Node* left;      // Pointer to the left subtree
        Node* right;     // Pointer to the right subtree
    };

    Node* root;  // Root of the tree

    // tree/array manipulation
    void inorderHelper(Node*) const;  // Helper for inorder traversal
    void sideways(Node*, int) const;   // Helper for displaySideways
    void makeEmptyHelper(Node*&);     // Helper for makeEmpty
    Node* copyTree(const Node* other); // Helper for deep copying a tree
    bool insertHelper(Node*&, NodeData*); // Helper for insert
    bool retrieveHelper(Node*, const NodeData&, NodeData*&) const; // Helper for retrieve
    int getHeightHelper(Node*) const; // Helper for getHeight
    Node* arrayToBSTreeHelper(NodeData* [], int, int); // Helper for arrayToBSTree
    int bstreeToArrayHelper(Node*, NodeData* [], int); // Helper for bstreeToArray
    bool equalsHelper(Node*, Node*) const; // Helper for equality check
};

