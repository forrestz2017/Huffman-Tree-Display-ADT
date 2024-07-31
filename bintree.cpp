// ------------------------------------------------ bintree.cpp -------------------------------------------------------
// Programmer Name: Forrest Zhang
// Course Section Number: CSS 343
// Creation Date: 7/3/2024
// Date of Last Modification: 7/10/2024
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Implementation file for the BinTree class, providing the functionality of a binary search tree (BST).
// --------------------------------------------------------------------------------------------------------------------
// This file contains the implementation of the BinTree class, including constructors, destructors, operator overloads, 
// and utility functions for various operations like insertion, retrieval, traversal, height calculation, and conversion 
// to/from arrays.
// --------------------------------------------------------------------------------------------------------------------

#include "bintree.h"

BinTree::BinTree() : root(nullptr) {} // default Constructor: Initializes the root to nullptr, indicating an empty tree

BinTree::BinTree(const BinTree& other) { // copy Constructor
    root = copyTree(other.root); // call helper function to perform deep copy
}

BinTree::~BinTree() { // Destructor
    makeEmpty(); // Clean up the tree by deallocating all nodes
}

// Assignment Operator
BinTree& BinTree::operator=(const BinTree& other) {
    if (this != &other) { // Check for self-assignment
        makeEmpty(); // Clean up the current tree
        root = copyTree(other.root); // Copy the other tree
    }
    return *this;
}

// copyTree: Recursively copies another tree
// input: other - pointer to the root node of the tree to copy
// Output: pointer to the root node of the newly copied tree
BinTree::Node* BinTree::copyTree(const Node* other) {
    if (other == nullptr) {
        return nullptr; // base case: if the node to copy is null, return null
    }
    Node* node = new Node; // Allocate a new node
    node->data = new NodeData(*other->data); // deep copy the data
    node->left = copyTree(other->left); // Recursively copy the left subtree
    node->right = copyTree(other->right); // Recursively copy the right subtree
    return node; // Return the new node
}

// isEmpty: Simply checks if the root is nullptr
// Output: true if the tree is empty, false otherwise
bool BinTree::isEmpty() const {
    return root == nullptr; // Tree is empty if root is null
}

// makeEmpty: Calls makeEmptyHelper to recursively delete all nodes
void BinTree::makeEmpty() {
    makeEmptyHelper(root); // Start recursive deletion from the root
}

// makeEmptyHelper: Recursively deletes all nodes in the tree
// Input: node - reference to the pointer to the node to delete
void BinTree::makeEmptyHelper(Node*& node) {
    if (node != nullptr) { // If the node is not null
        makeEmptyHelper(node->left); // Recursively delete the left subtree
        makeEmptyHelper(node->right); // Recursively delete the right subtree
        delete node->data; // Delete the data
        delete node; // Delete the node itself
        node = nullptr; // Set the node pointer to null
    }
}

// insert: Calls insertHelper to recursively find the correct position for the new node
// Input: data - pointer to the data to insert
// Output: true if the insertion was successful, false otherwise (if duplicate)
bool BinTree::insert(NodeData* data) {
    return insertHelper(root, data); // Start recursive insertion from the root
}

// insertHelper: Recursively inserts a new node into the BST
// Input: node - reference to the pointer to the current node, data - pointer to the data to insert
// Output: true if the insertion was successful, false otherwise (if duplicate)
bool BinTree::insertHelper(Node*& node, NodeData* data) {
    if (node == nullptr) { // Base case: found the correct position
        node = new Node{ data, nullptr, nullptr }; // Allocate a new node and assign the data
        return true; // Insertion successful
    }
    else if (*data < *node->data) { // If data is less than current node's data
        return insertHelper(node->left, data); // Recursively insert into the left subtree
    }
    else if (*data > *node->data) { // If data is greater than current node's data
        return insertHelper(node->right, data); // Recursively insert into the right subtree
    }
    else {
        return false; // Duplicate data, do not insert
    }
}

// retrieve: Uses retrieveHelper to recursively search for a node
// Input: target - reference to the data to find, data - reference to the pointer where the found data should be stored
// Output: true if the node was found, false otherwise
bool BinTree::retrieve(const NodeData& target, NodeData*& data) const {
    return retrieveHelper(root, target, data); // Start recursive retrieval from the root
}

// retrieveHelper: Recursively searches for a node in the BST
// Input: node - pointer to the current node, target - reference to the data to find, data - reference to the pointer where the found data should be stored
// Output: true if the node was found, false otherwise
bool BinTree::retrieveHelper(Node* node, const NodeData& target, NodeData*& data) const {
    if (node == nullptr) { // Base case: reached a null node, target not found
        return false;
    }
    else if (target == *node->data) { // If the target data matches the current node's data
        data = node->data; // Store the found data
        return true; // Target found
    }
    else if (target < *node->data) { // If target is less than current node's data
        return retrieveHelper(node->left, target, data); // Recursively search in the left subtree
    }
    else { // If target is greater than current node's data
        return retrieveHelper(node->right, target, data); // Recursively search in the right subtree
    }
}

// displaySideways: Uses sideways helper to print the tree structure
void BinTree::displaySideways() const {
    sideways(root, 0); // Start displaying from the root with initial level 0
}

// sideways: Recursively prints the tree structure sideways
// Input: current - pointer to the current node, level - the current depth level in the tree
void BinTree::sideways(Node* current, int level) const {
    if (current != nullptr) { // If the current node is not null
        level++; // Increment the level for the next depth
        sideways(current->right, level); // Recursively display the right subtree

        // Indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl; // Print the current node's data
        sideways(current->left, level); // Recursively display the left subtree
    }
}

// Operator<<: Inorder traversal to display the tree in sorted order
// Input: output - the output stream, tree - reference to the BinTree to display
// Output: the modified output stream
ostream& operator<<(ostream& output, const BinTree& tree) {
    tree.inorderHelper(tree.root); // Perform inorder traversal starting from the root
    output << endl; // End the line after displaying the tree
    return output;
}

// inorderHelper: Recursively performs inorder traversal
// Input: node - pointer to the current node
void BinTree::inorderHelper(Node* node) const {
    if (node != nullptr) { // If the current node is not null
        inorderHelper(node->left); // Recursively traverse the left subtree
        cout << *node->data << " "; // Print the current node's data
        inorderHelper(node->right); // Recursively traverse the right subtree
    }
}

// getHeight: Uses getHeightHelper to calculate the height of a specific node
// Input: data - reference to the data whose height is to be calculated
// Output: the height of the node with the given data
int BinTree::getHeight(const NodeData& data) const {
    Node* node = root; // Start from the root
    while (node != nullptr) { // Traverse the tree to find the node
        if (*node->data == data) {
            return getHeightHelper(node); // Calculate height once the node is found
        }
        else if (data < *node->data) {
            node = node->left; // Move to the left subtree
        }
        else {
            node = node->right; // Move to the right subtree
        }
    }
    return 0; // Return 0 if the node is not found
}

// getHeightHelper: Recursively calculates the height of a node
// Input: node - pointer to the current node
// Output: the height of the node
int BinTree::getHeightHelper(Node* node) const {
    if (node == nullptr) { // Base case: if the node is null, height is 0
        return 0;
    }
    int leftHeight = getHeightHelper(node->left); // Recursively calculate height of the left subtree
    int rightHeight = getHeightHelper(node->right); // Recursively calculate height of the right subtree
    return 1 + max(leftHeight, rightHeight); // Height of the node is 1 plus the maximum height of its subtrees
}

// bstreeToArray: Converts the BST to an array and then calls makeEmpty to clear the tree
// Input: arr - array to store the tree nodes
void BinTree::bstreeToArray(NodeData* arr[]) {
    bstreeToArrayHelper(root, arr, 0); // Convert the tree to an array
    makeEmpty(); // Clear the tree
}

// bstreeToArrayHelper: Recursively converts the BST to a sorted array
// Input: node - pointer to the current node, arr - array to store the nodes, index - current index in the array
// Output: the next index in the array
int BinTree::bstreeToArrayHelper(Node* node, NodeData* arr[], int index) {
    if (node == nullptr) { // Base case: if the node is null, return the current index
        return index;
    }
    index = bstreeToArrayHelper(node->left, arr, index); // Recursively convert the left subtree
    arr[index++] = node->data; // Store the current node's data in the array
    node->data = nullptr; // Clear the node's data to avoid double deletion
    index = bstreeToArrayHelper(node->right, arr, index); // Recursively convert the right subtree
    return index; // Return the next index
}

// arrayToBSTree: Uses arrayToBSTreeHelper to create a balanced BST from a sorted array
// Input: arr - sorted array to convert to a BST
void BinTree::arrayToBSTree(NodeData* arr[]) {
    int size = 0; // Initialize size to 0
    while (arr[size] != nullptr) { // Calculate the size of the array
        size++;
    }
    root = arrayToBSTreeHelper(arr, 0, size - 1); // Convert the array to a balanced BST
}

// arrayToBSTreeHelper: Recursively constructs a balanced BST from a sorted array
// Input: arr - sorted array, start - start index of the current subarray, end - end index of the current subarray
// Output: pointer to the root node of the constructed subtree
BinTree::Node* BinTree::arrayToBSTreeHelper(NodeData* arr[], int start, int end) {
    if (start > end) { // Base case: if the start index is greater than the end index, return null
        return nullptr;
    }
    int mid = (start + end) / 2; // Calculate the mid index
    Node* node = new Node{ arr[mid], nullptr, nullptr }; // Create a new node with the middle element
    node->left = arrayToBSTreeHelper(arr, start, mid - 1); // Recursively construct the left subtree
    node->right = arrayToBSTreeHelper(arr, mid + 1, end); // Recursively construct the right subtree
    return node; // Return the root node of the constructed subtree
}

// Equality Operator: Compares two trees for equality
// Input: other - reference to the other BinTree to compare
// Output: true if the trees are equal, false otherwise
bool BinTree::operator==(const BinTree& other) const {
    return equalsHelper(root, other.root); // Compare the two trees starting from the root
}

// Inequality Operator: Checks if two trees are not equal
// Input: other - reference to the other BinTree to compare
// Output: true if the trees are not equal, false otherwise
bool BinTree::operator!=(const BinTree& other) const {
    return !(*this == other); // Return the negation of the equality check
}

// equalsHelper: Recursively compares two trees for equality
// Input: a - pointer to the root of the first tree, b - pointer to the root of the second tree
// Output: true if the trees are equal, false otherwise
bool BinTree::equalsHelper(Node* a, Node* b) const {
    if (a == nullptr && b == nullptr) {
        return true; // Both nodes are null, so they are equal
    }
    else if (a == nullptr || b == nullptr) {
        return false; // One of the nodes is null, so they are not equal
    }
    else {
        return *a->data == *b->data && equalsHelper(a->left, b->left) && equalsHelper(a->right, b->right); // Compare data and subtrees
    }
}
