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

/* Returns a BST containing a bunch of Marlon Brando movies. Normally, you wouldn't construct
 * a BST this way; this is just here for the lecture demo.
 */
Node* makeBrandoTree() {
    return new Node {
        "On the Waterfront",
        new Node {
            "Apocalypse Now",
            new Node {
                "A Streetcar Named Desire",
                nullptr,
                nullptr
            },
            new Node {
                "Julius Caesar",
                nullptr,
                nullptr
            }
        },
        new Node {
            "The Godfather",
            new Node {
                "Superman",
                nullptr,
                nullptr
            },
            new Node {
                "Viva Zapata!",
                nullptr,
                nullptr
            }
        }
    };
}

bool contains(Node* root, const string& key) {
    /* Base case: If the tree is empty, your key isn't here. */
    if (root == nullptr) return false;

    /* Recursive case: See how we compare to the root. */
    if (key == root->value) return true;
    else if (key < root->value) return contains(root->left, key);
    else /*  key > root->value */ return contains(root->right, key);
}

void printTree(Node* root) {
    /* Base case: Empty tree has nothing to print. */
    if (root == nullptr) return;

    /* Otherwise, print things in sorted order! To do that, we need to
     *
     *   1. print the smaller elements in sorted order,
     *   2. then print our value,
     *   3. then print the larger values in sorted order.
     */
    printTree(root->left);
    cout << root->value << endl;
    printTree(root->right);
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

int main() {
    Node* root = makeBrandoTree();
    printTree(root);

    while (true) {
        string movie = getLine("Enter movie title: ");
        if (contains(root, movie)) {
            cout << "Stellaaaaaaa(r!)" << endl;
        } else {
            cout << "You don't understand! I could've been a contender! I could've had class!" << endl;
            insertInto(root, movie);
        }
    }

    /* TODO: Clean up the memory! We'll see how to do this on Monday of next week. */
	return 0;
}
