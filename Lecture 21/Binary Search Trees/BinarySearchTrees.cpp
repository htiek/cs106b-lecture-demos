/*****************************************************
 * File: BinarySearchTrees.cpp
 *
 * A program to play around with binary search trees!
 */
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "TreeGraphics.h"
using namespace std;

/* Type: Node
 * A node in a binary search tree.
 */
struct Node {
    int value;
    Node* left;
    Node* right;
};

/* Constructs this specific BST:
 *
 *                    49
 *                  /    \
 *                 25    77
 *                /  \     \
 *               12  37    96
 *
 * This is NOT how you typically make a BST. Think of this like the original
 * code we saw that manually constructed a linked list - it's something to
 * get us started, but in practice you'd build the tree using other methods.
 */
Node* makeInitialTree() {
    return new Node {
        49,
        new Node {
            25,
            new Node {
                12, nullptr, nullptr
            },
            new Node {
                37, nullptr, nullptr
            }
        },
        new Node {
            77,
            nullptr,
            new Node {
                96, nullptr, nullptr
            }
        }
    };
}

/* Returns whether the given element is in the BST pointed at by
 * root.
 */
bool contains(Node* root, int key) {
    /* Base Case: The empty tree has nothing in it. */
    if (root == nullptr) {
        return false;
    }
    /* Base Case: If the item you want is at the root, great! It was very
     * easy to find.
     */
    else if (key == root->value) {
        return true; // You just saw it!
    }
    /* Recursive Cases: Otherwise, if the key is anywhere, it will be either
     * to the left or the right, based on how it compares against the
     * root.
     */
    else if (key < root->value) {
        return contains(root->left, key);
    } else /*  key > root->value */ {
        return contains(root->right, key);
    }
}

/* Prints all nodes in the BST in sorted order. */
void printTree(Node* root) {
    /* Base Case: An empty tree has nothing in it. */
    if (root == nullptr) {
        return; // Nothing to see here folks, move along
    }
    /* Recursive Case: List everything smaller than the root
     * in sorted order, then the root, then everything bigger
     * than the root in sorted order.
     */
    else {
        printTree(root->left);
        cout << root->value << endl;
        printTree(root->right);
    }
}

/* Adds the value to the given tree. */
void add(Node*& root, int key) {
    /* Base Case: If the tree is empty, it now has just one
     * element.
     */
    if (root == nullptr) {
        /* In lecture, we wrote the following:
         *
         *   root = new Node;
         *   root->value = key;
         *   root->left = root->right = nullptr;
         *
         * However, the option shown below is a bit more compact and
         * I'm personally more a fan of it.
         */
        root = new Node { key, nullptr, nullptr };
    }
    /* Base Case: If the key is already in the tree, great! There's
     * nothing to do.
     */
    else if (key == root->value) {
        // Do nothing
    }
    /* Recursive Case: Add the key to the proper subtree. */
    else if (key < root->value) {
        add(root->left, key);
    } else /*  key > root->value */ {
        add(root->right, key);
    }
}

int main() {
    /* Constructs this specific BST:
     *
     *                    49
     *                  /    \
     *                 25    77
     *                /  \     \
     *               12  37    96
     */
    Node* root = makeInitialTree();
    drawTree(root);

    printTree(root);

    while (true) {
        int value = getInteger("Enter value: ");
        if (contains(root, value)) {
            cout << "Yep! It's there." << endl;
        } else {
            cout << "Nope! Not there. Except now it is. :-)" << endl;
            add(root, value);
        }

        drawTree(root);
    }
}
