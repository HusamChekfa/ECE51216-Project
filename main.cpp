//
// Created by Husam Study on 3/14/2025.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "Parser.h"
using namespace std;

struct Clause {
    vector<int> literals;
};

int main() {


    //std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    // int a = Parse("C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf");
    // std::cout << a;

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