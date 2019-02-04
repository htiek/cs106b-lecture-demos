/* File: Crosswords.cpp
 *
 * A program to generate dense crosswords.
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "console.h"
using namespace std;

/**
 * Given a grid and a column, extracts the word at that column up to a certain
 * number of characters.
 *
 * @param grid The grid in question.
 * @param col Which column to extract
 * @param numRows How many rows to read
 * @return The contents of that column.
 */
string contentsOfColumn(const Grid<char>& grid, int col, int numRows) {
    string result;
    for (int row = 0; row < numRows; row++) {
        result += grid[row][col];
    }
    return result;
}

/**
 * Given a grid, reports whether every column is a prefix of some legal
 * English word.
 *
 * @param grid The grid in question.
 * @param colWords A collection of all words that can fit in a column.
 * @param maxRow The maximum row to descend down to.
 * @return Whether all columns are feasible prefixes of real words.
 */
bool areColumnsFeasible(const Grid<char>& grid, int maxRow, const Lexicon& colWords) {
    for (int col = 0; col < grid.numCols(); col++) {
        string prefix = contentsOfColumn(grid, col, maxRow);
        if (!colWords.containsPrefix(prefix)) return false;
    }
    return true;
}

/**
 * Prints a crossword to the console.
 *
 * @param crossword The crossword in question.
 */
void printCrossword(const Grid<char>& crossword) {
    for (int row = 0; row < crossword.numRows(); row++) {
        for (int col = 0; col < crossword.numCols(); col++) {
            cout << crossword[row][col];
        }
        cout << endl;
    }
}

/**
 * Returns whether it's possible to extend a partial crossword into a full one.
 * If so, the crossword is updated to contain the solution.
 *
 * @param crossword The partial crossword.
 * @param nextRow The next row that needs to be filled in.
 * @param rowWords All words that can fit in the rows.
 * @param colWords All words that can fit in the columns.
 * @return Whether the crossword can be extended.
 */
bool recCanMakeCrossword(Grid<char>& crossword,
                         int nextRow,
                         const Lexicon& rowWords,
                         const Lexicon& colWords) {
    /* Base case: If any of the columns cannot be extended into a word, stop searching. */
    if (!areColumnsFeasible(crossword, nextRow, colWords)) return false;

    /* Base case: If we've finished all the rows, we're done! */
    if (nextRow == crossword.numRows()) return true;

    /* Otherwise, try placing each word down here. */
    for (string word: rowWords) {
        /* Copy the word in. */
        for (int i = 0; i < crossword.numCols(); i++) {
            crossword[nextRow][i] = word[i];
        }

        /* See if this works! */
        if (recCanMakeCrossword(crossword, nextRow + 1, rowWords, colWords)) return true;
    }

    return false;
}

/**
 * Returns whether the crossword grid can be filled in so that each row and
 * column are words.
 *
 * @param crossword The partial crossword.
 * @param english All English words.
 */
bool canMakeCrossword(Grid<char>& crossword, const Lexicon& english) {
    /* Split the Lexicon into two smaller lexicons, one for words that can appear
     * in rows, and one for words that can appear in columns.
     */
    Lexicon rowWords, colWords;
    for (string word: english) {
        if (word.length() == crossword.numCols()) rowWords += word;

        /* No else here - the grid could be a square! */
        if (word.length() == crossword.numRows()) colWords += word;
    }

    return recCanMakeCrossword(crossword, 0, rowWords, colWords);
}

int main() {
    Lexicon english("EnglishWords.txt");
	
    /* The dimensions here are arbitrary but give rise to some pretty cool words! */
    Grid<char> crossword(4, 7);

    cout << "Starting..." << endl;

    if (canMakeCrossword(crossword, english)) {
        printCrossword(crossword);
	} else {
		cout << "No solution found." << endl;
	}
    return 0;
}
