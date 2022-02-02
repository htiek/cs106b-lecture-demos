/*****************************************************
 * File: BinarySearchTrees.cpp
 *
 * A program to play around with binary search trees!
 */
#include <iostream>
#include <string>
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

bool contains(Node* tree, const string& value) {
    if (tree == nullptr) return false;

    if (value == tree->value) {
        return true;
    } else if (value < tree->value) {
        return contains(tree->left, value);
    } else /* (value > tree->value) */  {
        return contains(tree->right, value);
    }
}

void printTree(Node* tree) {
    if (tree == nullptr) return;

    printTree(tree->left);        // Line 1
    cout << tree->value << endl;
    printTree(tree->right);       // Line 2
}

void insertInto(Node*& tree, const string& value) {
    if (tree == nullptr) {
        Node* node = new Node;
        node->value = value;
        node->left  = nullptr;
        node->right = nullptr;
        tree = node;
    } else if (value < tree->value) {
        insertInto(tree->left, value);
    } else if (value > tree->value) {
        insertInto(tree->right, value);
    } /* else (value == tree->value) do nothing; */
}

int main() {
    Node* root = makeTreeTree();
    printTree(root);

    while (true) {
        string name = getLine("Enter tree: ");
        if (contains(root, name)) {
            cout << "Tree-mendous!" << endl;
        } else {
            cout << "If at first you don't succeed, tree, tree again!" << endl;
            insertInto(root, name);
        }
    }

    /* TODO: Clean up the memory! We'll see how to do this on Monday. */
    return 0;
}
