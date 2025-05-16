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
#include "Heuristics.h"

void print_solution(const vector<int> & sol);

void clean_solution(vector<int> & sol) {
    for (int i = 1; i < sol.size(); ++i) {
        if (sol[i] == 0) {
            sol[i] = -1;
        }
    }
}

void print_solution(const vector<int> & sol) {
    cout << "ASSIGNMENT:";
    for (int i = 1; i < sol.size(); ++i) {
        cout << i << "=" << (sol[i] == 1 ? "1 " : "0 ");
    }
    cout << endl;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfile.cnf>\n";
        return 1;
    }

    size_t numVars = 0;
    vector<Clause> clauses;

    int a = Parse(argv[1], clauses, numVars);
    vector<int> solution(numVars + 1, 0);
    vector<vector<unsigned>> uncomplemented(numVars + 1);
    vector<vector<unsigned>> complemented(numVars + 1);
    int c = Parse_uncomp(clauses, uncomplemented, complemented);
    int b = DPLL(clauses, solution, uncomplemented, complemented);
    if (b == 0) {
        // Satsified
        // call clean_solution
        clean_solution(solution);
        cout << "RESULT:SAT" << endl;
        // run_sat() - this prints output in proper format
        print_solution(solution);
    }
    else {
        // Unsatisfied
        cout << "RESULT:UNSAT" << endl;
    }

    return 0;
}
