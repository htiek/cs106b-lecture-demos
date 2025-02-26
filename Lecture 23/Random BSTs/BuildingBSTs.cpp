/*****************************************************
 * File: BuildingBSTs.cpp
 *
 * A demo to build BSTs incrementally from a given
 * data set and visualize how the tree is formed.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "TreeGraphics.h"
using namespace std;

/* Type: Node
 * A node in a binary search tree.
 */
struct Node {
    string value;
    Node* left;
    Node* right;
};

void insertInto(Node*& root, const string& key) {
    /* Base case: If we insert into an empty tree, just make a new node for the key. */
    if (root == nullptr) {
        root = new Node { key, nullptr, nullptr };
    }
    /* Otherwise, see where we go. */
    else if (key < root->value) {
        insertInto(root->left, key);
    } else if (key > root->value) {
        insertInto(root->right, key);
    } /* else if (key == root->value) // do nothing */
}

/* Deletes all the nodes in a tree. This approach uses a postorder traversal;
 * we delete the children before deleting the node itself.
 */
void deleteTree(Node* root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

const double kPauseTime = 50;

Node* treeFrom(const string& filename) {
    Node* tree = nullptr;

    /* Read the file contents one line at a time. */
    ifstream input(filename);
    for (string line; getline(input, line); ) {
        insertInto(tree, line);
        drawTree(tree);
        pause(kPauseTime);
    }

    return tree;
}

int main() {
    Node* root = treeFrom("res/SFO-March.csv");
    //Node* root = treeFrom("res/WomensOlympicMarathon2016.csv");
    deleteTree(root);
    return 0;
}
