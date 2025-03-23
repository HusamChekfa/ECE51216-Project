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


void clean_solution(vector<int> sol) {
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

int main() {
    size_t numVars = 0;
    //vector<Clause> clauses(1);
    vector<Clause> clauses;
    //vector<int> solution;

    bool satisfied = false;
    string fileName = "";
    fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf";

    //fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/b.cnf";
    //fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/quinn.cnf";
    //fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/ok.cnf";
    fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/global.cnf";

    cout << "Current working directory: " << filesystem::current_path() << endl;
    int a = Parse(fileName, clauses, numVars);
    //cout << a << endl;
    //cout << g_Unit_count << endl;
    //cout << g_Clause_Count << endl;

    vector<int> solution(numVars + 1, 0);
    vector<vector<unsigned>> uncomplemented(numVars + 1);
    vector<vector<unsigned>> complemented(numVars + 1);
    int c = Parse_uncomp(clauses, uncomplemented, complemented);



    int b = DPLL(clauses, solution, uncomplemented, complemented, satisfied);

    // STDOUT?
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