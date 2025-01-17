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
bool parensMatch(char open, char close);

/* Given a string, are the parentheses balanced in
 * that string?
 */
bool parensAreBalancedIn(const string& text) {

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

/* Is a character some sort of open parenthesis? */
bool isOpenParenthesis(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

/* Is a character some sort of close parenthesis? */
bool isCloseParenthesis(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

/* Do the given pair of an open parenthesis and a close
 * parenthesis match one another?
 */
bool parensMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}
