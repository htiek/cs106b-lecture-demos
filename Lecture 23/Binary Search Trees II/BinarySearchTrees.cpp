/*****************************************************
 * File: BinarySearchTrees.cpp
 *
 * A program to play around with binary search trees!
 */
#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Type: Node
 * A node in a binary search tree.
 */
struct Node {
    string value;
    Node* left;
    Node* right;
};

bool contains(Node* root, const string& key) {
    /* Base case: If the tree is empty, your key isn't here. */
    if (root == nullptr) return false;

    /* Recursive case: See how we compare to the root. */
    if (key == root->value) return true;
    else if (key < root->value) return contains(root->left, key);
    else /*  key > root->value */ return contains(root->right, key);
}

void printBetween(Node* root, const string& low, const string& high) {
    if (root == nullptr) return;

    if (high < root->value) {
        printBetween(root->left, low, high);
    } else if (low > root->value) {
        printBetween(root->right, low, high);
    } else {
        printBetween(root->left, low, high);
        cout << root->value << endl;
        printBetween(root->right, low, high);
    }
}

/* Prints out the full contents of a BST in sorted order. */
void printContentsOf(Node* root) {
    /* Base case: Empty tree has nothing to print. */
    if (root == nullptr) return;

    /* Otherwise, print things in sorted order! To do that, we need to
     *
     *   1. print the smaller elements in sorted order,
     *   2. then print our value,
     *   3. then print the larger values in sorted order.
     */
    printContentsOf(root->left);
    cout << root->value << endl;
    printContentsOf(root->right);
}

/* Frees all memory used by the given BST. */
void deleteTree(Node* root) {
    if (root == nullptr) return;

    deleteTree(root->right);
    deleteTree(root->left);
    delete root;
}

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

/* Returns a BST containing a bunch of California trees. Normally, you wouldn't construct
 * a BST this way; this is just here for the lecture demo.
 */
Node* makeTreeTree() {
    return new Node {
        "Douglas Fir",
        new Node {
            "Bristlecone Pine",
            new Node {
                "Bay Laurel",
                nullptr,
                nullptr
            },
            new Node {
                "Coast Redwood",
                nullptr,
                nullptr
            }
        },
        new Node {
            "Jeffrey Pine",
            new Node {
                "Giant Sequoia",
                nullptr,
                nullptr
            },
            new Node {
                "Manzanita",
                nullptr,
                nullptr
            }
        }
    };
}



int main() {
    Node* root = makeTreeTree();

    insertInto(root, "Joshua Tree");
    insertInto(root, "Ponderosa Pine");

    printBetween(root, "D", "K");

    deleteTree(root);

    return 0;
}
