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




int main() {
    size_t numVars = 0;
    vector<Clause> clauses;
    //vector<int> solution;
    vector<vector<unsigned>> uncomplemented;
    vector<vector<unsigned>> complemented;
    bool satisfied = false;
    string fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf";
    cout << "Current working directory: " << filesystem::current_path() << endl;
    int a = Parse(fileName, clauses, uncomplemented, complemented, numVars);
    cout << a << endl;
    cout << g_Unit_count << endl;
    cout << g_Clause_Count << endl;

    vector<int> solution(numVars, 0);

    int b = DPLL(clauses, solution, uncomplemented, complemented, satisfied);




    // STDOUT?
    if (b == 0) {
        // Satsified
        // call clean_solution
        cout << "RESULT:SAT" << endl;
        // run_sat() - this prints output in proper format

    }
    else {
        // Unsatisfied
        cout << "RESULT:UNSAT" << endl;
    }





    return 0;
}