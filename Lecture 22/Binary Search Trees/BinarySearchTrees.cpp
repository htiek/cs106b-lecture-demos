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

bool contains(Node* root, const string& key) {
    /* TODO: This is a very pessimistic function that
     * always returns false. Improve upon this.
     */
    return false;
}

int main() {
    Node* root = makeTreeTree();

    while (true) {
        string name = getLine("Enter tree: ");
        if (contains(root, name)) {
            cout << "Tree-mendous!" << endl;
        } else {
            cout << "If at first you don't succeed, tree, tree again!" << endl;
        }
    }

    /* TODO: Clean up the memory! We'll see how to do this on Wednesday. */
}
