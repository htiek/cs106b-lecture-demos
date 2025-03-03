/*****************************************************
 * File: RangeSearches.cpp
 *
 * Code to perform range searches over a BST.
 */
#include <iostream>
#include <string>
#include <iomanip>
#include "TreeGraphics.h"
#include "vector.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Type: Node
 * A node in a binary search tree.
 */
struct Node {
    string value;
    Node* left;
    Node* right;
};

/* All the USPS abbreviations. */
const Vector<string> kUSPSCodes = {
    "UT", "KY", "AK", "IL", "LA",
    "FL", "AL", "MN", "NH", "VI",
    "MI", "WA", "MS", "TN", "RI",
    "MT", "DE", "NV", "ND", "NC",
    "WI", "NE", "MA", "HI", "NM",
    "IA", "CT", "WV", "OR", "ID",
    "KS", "MO", "GA", "SD", "VT",
    "AZ", "CO", "OK", "WY", "VA",
    "NY", "NJ", "SC", "PA", "TX",
    "PR", "AR", "ME", "CA", "DC",
    "MD", "IN", "OH"
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

/* Build a tree of all USPS codes. */
Node* americanTree() {
    Node* root = nullptr;
    for (string element: kUSPSCodes) {
        insertInto(root, element);
    }
    return root;
}

void printInRange(Node* root, const string& low, const string& high) {

}

int main() {
    Node* root = americanTree();
    drawTree(root);

    while (true) {
        string low  = getLine("From: ");
        string high = getLine("To:   ");
        printInRange(root, low, high);
    }
    return 0;
}
