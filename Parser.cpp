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
        return 1;
    }

    string line;
    int numVariables = 0;
    int numClauses = 0;
    int clauseSize = 0;
    int i = 1;
    //vector<Clause> clauses;
    //int completed = 0; // PARSER TESTING VARIABLE; FIXED LAST 2 % AND 0 LINES IN .TXT PARSE
    while (getline(inputFile, line)) {
        clauseSize = 0;
        // if (completed == 91) {
        //     completed = 100;
        // }
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
            //clauses = vector<Clause>(numVariables + 1);
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
                //clause.literals.push_back(literal);
                else if (literal > 0) {
                    clause.literals[literal] = 1;
                }
                else {
                    clause.literals[-literal] = -1;
                }
                //clause.assigned_literals.push_back(false);
                ++clause.unassigned;
                ++clauseSize;
            }
            //clauses[i] = clause;
            ++i;
            clauses.push_back(clause);
            ++g_Clause_Count;
            if (clauseSize == 1) {
                ++g_Unit_count;
            }
            //++completed;
        }
    }

    inputFile.close();

    /*
    // Output parsed clauses (for debugging)
    cout << "Number of Variables: " << numVariables << endl;
    cout << "Number of Clauses: " << numClauses << endl;
    cout << "Clauses:" << endl;
    for (int k = 1; k < clauses.size(); ++k) { // const auto& clause : clauses
        for (int j = 1; j < numVariables + 1; ++j) {
            if (clauses[k].literals[j] == 1) {
                cout << j << ' ';
            }
            else if (clauses[k].literals[j] == -1) {
                cout << -j << ' ';
            }
            //cout << clauses[k].literals[j];
        }
        // for (int literal : clause.literals) {
        //     cout << literal << " ";
        // }
        //cout << "0" << endl;
        cout << endl;
    }
    */

    if (clauses.size() != numClauses) {// + 1) {
        cout << "ERROR: vector Clauses size != numVariables." << endl;
        return -1;
    }
    // if (uncomp.size() - 1 != numVariables) {
    //     cout << "ERROR: vector Uncomplement size - 1 != numVariables." << endl;
    //     return -2;
    // }
    // if (comp.size() - 1 != numVariables) {
    //     cout << "ERROR: vector Complement size - 1 != numVariables." << endl;
    //     return -3;
    // }

    numVars = numVariables;


    return 0;
}

int Parse_uncomp(const vector<Clause> & clauses, vector<vector<unsigned>> & uncomp, vector<vector<unsigned>> & comp) {
    for (int clause_num = 0; clause_num < clauses.size(); ++clause_num) { // const auto& clause : clauses
        for (int lit_num = 1; lit_num < clauses[0].literals.size(); ++lit_num) {
            if (clauses[clause_num].literals[lit_num] == 1) {
                uncomp[lit_num].push_back(clause_num);
            }
            else if (clauses[clause_num].literals[lit_num] == -1) {
                comp[lit_num].push_back(clause_num);
            }
        }
        // for (int literal : clause.literals) {
        //     cout << literal << " ";
        // }
        //cout << "0" << endl;
        //cout << endl;
    }



    return 0;
}
// maybe add var/clause count as & for main?
/*
 int Parse(const string &filename, vector<Clause> & clauses, vector<vector<unsigned>> & uncomp, vector<vector<unsigned>> & comp) {
    // Open the CNF DIMACS file
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    int numVariables = 0;
    int numClauses = 0;
    int clauseSize = 0;
    //vector<Clause> clauses;
    //int completed = 0; // PARSER TESTING VARIABLE; FIXED LAST 2 % AND 0 LINES IN .TXT PARSE
    while (getline(inputFile, line)) {
        // if (completed == 91) {
        //     completed = 100;
        // }
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
                clause.assigned_literals.push_back(false);
                ++clause.unassigned;
                ++clauseSize;
            }
            clauses.push_back(clause);
            ++g_Clause_Count;
            if (clauseSize == 1) {
                ++g_Unit_count;
            }
            //++completed;
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

    if (clauses.size() != numVariables) {
        cout << "ERROR: vector Clauses size != numVariables." << endl;
        return -1;
    }
    if (uncomp.size() - 1 != numVariables) {
        cout << "ERROR: vector Uncomplement size - 1 != numVariables." << endl;
        return -2;
    }
    if (comp.size() - 1 != numVariables) {
        cout << "ERROR: vector Complement size - 1 != numVariables." << endl;
        return -3;
    }


    return 0;
}

*/



