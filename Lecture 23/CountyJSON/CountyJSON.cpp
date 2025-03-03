/***********************************************************
 * File: CountyJSON.cpp
 *
 * Code to analyze a JSON file of US county population data.
 */

#include <iostream>
#include <string>
#include <fstream>
#include "vector.h"
#include "console.h"
#include "Utilities/JSON.h"
using namespace std;

Vector<int> totalPopulationOf(JSON json) {
    if (json.type() == JSON::Type::ARRAY) {
        Vector<int> result;
        for (int i = 0; i < json.size(); i++) {
            result += json[i].asInteger();
        }
        return result;
    }

    Vector<int> totals;
    for (JSON child: json) {
        auto thisState = totalPopulationOf(json[child]);
        if (totals.isEmpty()) {
            totals = thisState;
        }
        else {
            for (int i = 0; i < totals.size(); i++) {
                totals[i] += thisState[i];
            }
        }
    }
    return totals;
}

int main() {
    ifstream input("CountyPopulations.json", ios::binary);
    JSON json = JSON::parse(input);

    cout << totalPopulationOf(json) << endl;
    return 0;
}





