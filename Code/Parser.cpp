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

int Parse(const string &filename, vector<Clause> & clauses, size_t & numVars) {
    // Open the CNF DIMACS file
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error opening file." << endl;
        exit(5);
    }

    string line;
    int numVariables = 0;
    int numClauses = 0;
    int clauseSize = 0;
    int i = 1;

    while (getline(inputFile, line)) {
        clauseSize = 0;
        // Remove leading/trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Skip empty lines or comments (lines starting with 'c')
        if (line.empty() || line[0] == 'c' || line[0] == '%' || line[0] == '0') {
            continue;
        }

        // Process the header line (starts with 'p cnf')
        if (line[0] == 'p' && line[1] == ' ') {
            stringstream ss(line);
            string temp;
            ss >> temp >> temp >> numVariables >> numClauses;
            g_dlis_pos = vector<int>(numVariables + 1, 0);
            g_dlis_neg = vector<int>(numVariables + 1, 0);
        }
        // Process clauses (lines with integers followed by 0)
        else {
            stringstream ss(line);
            Clause clause;
            clause.literals = vector<int>(numVariables + 1,0);
            clause.assigned_literals = vector<bool>(numVariables + 1, false);
            int literal;
            while (ss >> literal) {
                if (literal == 0) {
                    break; // End of clause
                }
                else if (literal > 0) {
                    clause.literals[literal] = 1;
                    ++g_dlis_pos[literal];
                }
                else {
                    clause.literals[-literal] = -1;
                    ++g_dlis_neg[-literal];
                }
                ++clause.unassigned;
                ++clauseSize;
                clause.lits.push_back(literal);
            }
            ++i;
            clauses.push_back(clause);
            ++g_Clause_Count;
            if (clauseSize == 1) {
                ++g_Unit_count;
            }
        }
    }

    inputFile.close();

    if (clauses.size() != numClauses) {// + 1) {
        cout << "ERROR: vector Clauses size != numVariables." << endl;
        return -1;
    }
    numVars = numVariables;
    return 0;
}

int Parse_uncomp(const vector<Clause> & clauses, vector<vector<unsigned>> & uncomp, vector<vector<unsigned>> & comp) {
    for (int clause_num = 0; clause_num < clauses.size(); ++clause_num) {
        for (int lit_num = 1; lit_num < clauses[0].literals.size(); ++lit_num) {
            if (clauses[clause_num].literals[lit_num] == 1) {
                uncomp[lit_num].push_back(clause_num);
            }
            else if (clauses[clause_num].literals[lit_num] == -1) {
                comp[lit_num].push_back(clause_num);
            }
        }
    }
    return 0;
}
