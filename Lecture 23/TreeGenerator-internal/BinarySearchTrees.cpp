/*****************************************************
 * File: BinarySearchTrees.cpp
 *
 * A program to play around with binary search trees!
 */
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
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

/* Deletes all the nodes in a tree. This approach uses a postorder traversal;
 * we delete the children before deleting the node itself.
 */
void deleteTree(Node* root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* Finds all elements in the tree within a given range, printing them in
 * sorted order.
 */
void printInRange(Node* root, const string& low, const string& high) {
    /* Empty trees don't have anything in any range. */
    if (root == nullptr) return;

    /* If the range is purely to the left, just look there. */
    if (high < root->value) {
        printInRange(root->left, low, high);
    }
    /* If the range is purely to the right, just look there. */
    else if (root->value < low) {
        printInRange(root->right, low, high);
    }
    /* Otherwise, we're in the range, and so we need to print ourselves.
     * But there might also be other matches, and we'll need to find those
     * as well!
     */
    else {
        printInRange(root->left, low, high);
        cout << root->value << endl;
        printInRange(root->right, low, high);
    }
}

Node* treeFrom(const string& filename) {
    Node* tree = nullptr;

    ifstream input(filename);
    for (string line; getline(input, line); ) {
        insertInto(tree, line);
    }

    return tree;
}

int heightOf(Node* tree) {
    if (tree == nullptr) return -1;
    return 1 + max(heightOf(tree->left), heightOf(tree->right));
}

int sizeOf(Node* tree) {
    return tree == nullptr? 0 : 1 + sizeOf(tree->left) + sizeOf(tree->right);
}

void drawLinks(Node* tree, ostream& out) {
    if (tree == nullptr) return;
    out << quoted(tree->value) << " [label=\"\",shape=circle,penwidth=5]" << endl;

    if (tree->left) {
        out << quoted(tree->value) << " -> " << quoted(tree->left->value) << " [headport=n,tailport=w,penwidth=5]" << endl;
        drawLinks(tree->left, out);
    }
    if (tree->right) {
        out << quoted(tree->value) << " -> " << quoted(tree->right->value) << " [headport=n,tailport=e,penwidth=5]" << endl;
        drawLinks(tree->right, out);
    }
}

void drawTree(Node* tree) {
    ofstream output("res/tree.dot");
    output << "digraph G {";

    drawLinks(tree, output);

    output << "}";

    output.close();
    system("dot res/tree.dot -Tpng -o res/tree.png && xdg-open res/tree.png");
}

int main() {
    //Node* root = makeTreeTree();
    //Node* root = treeFrom("res/SFO-4PM-Temperature-2010.csv");
    //Node* root = treeFrom("res/SP500.csv");
    Node* root = treeFrom("res/WomensOlympicMarathon2016.csv");
    cout << heightOf(root) << endl;
    cout << sizeOf(root) << endl;
    cout << log(sizeOf(root)) / log(2.0) << endl;

    drawTree(root);

//    Node* root = makeTreeTree();

//    insertInto(root, "Joshua Tree");
//    insertInto(root, "Ponderosa Pine");

//    printInRange(root, "C", "J");
//    deleteTree(root);
    return 0;
}
