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





























/*
   I knew that dame was trouble as soon as I set eyes on her, see: there was a
   stain on her clingy dress, wine, difficult to get out (you notice these things
   when you've been in the business as long as I have); there was a piece of gum
   stuck to the bottom of her high heel, cherry, that would leave a gristly pink
   trail following her every step (you pick up on these things when you are as
   experienced as I); and when she coolly asked me directions to the detective's
   office, I pointed her down the hall and went back to mopping the floor.

                                      --Bridget Parmenter, Katy, TX
                                        Grand Panjandrum's Special Award
                                        2018 Bulwer-Lytton Fiction Contest
 */
