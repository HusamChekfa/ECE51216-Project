//
// Created by Husam Study on 3/14/2025.
//

#include "Parser.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Clause {
    vector<int> literals;
    unsigned int unassigned = 0; // count of unassigned variables
};

int Parse(const std::string &filename) {
    // Open the CNF DIMACS file
    ifstream inputFile("C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf");

    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    int numVariables = 0;
    int numClauses = 0;
    vector<Clause> clauses;

    while (getline(inputFile, line)) {
        // Remove leading/trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Skip empty lines or comments (lines starting with 'c')
        if (line.empty() || line[0] == 'c') {
            continue;
        }

        // Process the header line (starts with 'p cnf')
        if (line[0] == 'p' && line[1] == ' ') {
            stringstream ss(line);
            string temp;
            ss >> temp >> temp >> numVariables >> numClauses;
        }
        // Process clauses (lines with integers followed by 0)
        else {
            stringstream ss(line);
            Clause clause;
            int literal;
            while (ss >> literal) {
                if (literal == 0) {
                    break; // End of clause
                }
                clause.literals.push_back(literal);
                ++clause.unassigned;
            }
            clauses.push_back(clause);
        }
    }

    inputFile.close();

    // Output parsed clauses (for debugging)
    cout << "Number of Variables: " << numVariables << endl;
    cout << "Number of Clauses: " << numClauses << endl;
    cout << "Clauses:" << endl;
    for (const auto& clause : clauses) {
        for (int literal : clause.literals) {
            cout << literal << " ";
        }
        cout << "0" << endl;
    }


    return 0;
}


/*
int Parse(const std::string &filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();

    return 0;
}
*/

