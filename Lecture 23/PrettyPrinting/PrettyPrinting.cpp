/*************************************************
 * File: PrettyPrinting.cpp
 *
 * Code to print out a somewhat reasonable representation
 * of a multiway tree.
 */

#include <iostream>
#include <string>
#include "vector.h"
#include "simpio.h"
#include "console.h"
using namespace std;

/* Type: Node
 *
 * A node in a multiway tree.
 */
struct Node {
    string value;
    Vector<Node*> children;
};

/* Returns this exact tree:
 *          A
 *         /|\
 *        / | \
 *       B  C  D
 *        // \\
 *      / /   \ \
 *    /  /     \  \
 *   E   F     G   H
 *  / \       / \
 * I   J     K   L
 *               |
 *               M
 */
Node* makeTree() {
    Node* b = new Node{ "B", {} };
    Node* i = new Node{ "I", {} };
    Node* j = new Node{ "J", {} };
    Node* e = new Node{ "E", {i, j} };
    Node* f = new Node{ "F", {} };
    Node* k = new Node{ "K", {} };
    Node* m = new Node{ "M", {} };
    Node* l = new Node{ "L", {m} };
    Node* g = new Node{ "G", {k, l}};
    Node* h = new Node{ "H", {} };
    Node* c = new Node{ "C", {e, f, g, h}};
    Node* d = new Node{ "D", {} };
    Node* a = new Node{ "A", {b, c, d}};
    return a;
}

void freeTree(Node* root) {
    if (root != nullptr) {
        for (Node* child: root->children) {
            freeTree(child);
        }
        delete root;
    }
}

void prettyPrint(Node* tree) {

}

int main() {
    Node* tree = makeTree();

    prettyPrint(tree);

    freeTree(tree);
    return 0;
}






