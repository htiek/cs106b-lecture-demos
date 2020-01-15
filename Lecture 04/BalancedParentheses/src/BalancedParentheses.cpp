/* File: BalancedParentheses.cpp
 *
 * A program that checks whether the parentheses in a string are
 * balanced.
 */
#include <iostream>
#include <string>
#include "stack.h"
#include "simpio.h"
#include "console.h"
using namespace std;

/* Helper functions that test various properties of
 * characters.
 */
bool isOpenParenthesis(char ch);
bool isCloseParenthesis(char ch);
bool areMatchingParentheses(char open, char close);

/* Given a string, are the parentheses balanced within
 * that string? The parameter is accepted by const
 * reference because (1) we don't want to copy the
 * text (that's wasteful), and (2) we don't want this
 * function to make changes to it.
 */
bool parensAreBalancedIn(const string& text) {
    /* All the open parentheses that have not yet
     * been matched.
     */
    Stack<char> opens;

    /* Read all characters in the order in which they
     * appear in the input.
     */
    for (char ch: text) {
        if (isOpenParenthesis(ch)) {
            opens.push(ch);
        } else if (isCloseParenthesis(ch)) {
            /* If there's nothing to match against,
             * we have a mismatched close parenthesis.
             */
            if (opens.isEmpty()) {
                return false;
            }

            /* Otherwise, we'd better match the last
             * open parenthesis we encountered!
             */
            char lastOpen = opens.pop();
            if (!areMatchingParentheses(lastOpen, ch)) {
                return false;
            }
        }
    }

    /* Once we're here, if any parentheses haven't been
     * matched, then we have a mismatch.
     */
    return opens.isEmpty();
}

int main() {
    while (true) {
        string text = getLine("Enter some text: ");
        if (parensAreBalancedIn(text)) {
            cout << "Yep!" << endl;
        } else {
            cout << "Nah" << endl;
        }
    }
}

bool isOpenParenthesis(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}
bool isCloseParenthesis(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}
bool areMatchingParentheses(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}
