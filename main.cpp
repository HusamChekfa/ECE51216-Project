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
#include <chrono>

unsigned fail = 0;
unsigned unsat = 0;
unsigned sat = 0;

void print_solution(const vector<int> & sol);

void check(vector<Clause> checking, const vector<int> & sol) {

    for (int i = 1; i < sol.size(); ++i) {
        for (int x = 0; x < checking.size();) {
            if (checking[x].literals[i] == sol[i]) {
                checking.erase(checking.begin()+ x);
            }
            else {
                ++x;
            }
        }
    }

    /*
    for (int i = 1; i < sol.size(); ++i) {
        auto it = checking.begin(); // Use an iterator
        while (it != checking.end()) {
            if (it->literals[i] == sol[i]) {
                it = checking.erase(it); // Erase returns the next valid iterator
            } else {
                ++it; // Only increment if not erasing
            }
        }
    }*/
    if (checking.size() ==  0) {
        cout << "\t\tSUCCESS !!!! " << endl;
        //print_solution(sol);
        ++sat;
    }
    else {
        cout << "\t\tWRONG SOLUTION!!!!! " << endl;
        print_solution(sol);
        for (int z = 0; z < checking.size(); ++z) {
            for (int y = 1; y < sol.size(); ++y) {
                if (checking[z].literals[y] != 0) {
                    cout << y * checking[z].literals[y] << " ";
                }
            }
            cout << endl;

        }
        ++fail;
        exit(1);
    }
    // for (int i = 1; i < sol.size(); ++i) {
    //     for (int x = 0; x < checking.size();) {
    //         if (checking[x].literals[i] == sol[i]) {
    //             checking.erase(x);
    //         }
    //         else {
    //             ++x;
    //         }
    //     }
    //
    // }
}
void clean_solution(vector<int> & sol) {
    for (int i = 1; i < sol.size(); ++i) {
        if (sol[i] == 0) {
            sol[i] = -1;
        }
    }
}

void print_solution(const vector<int> & sol) {
    cout << "\t\tASSIGNMENT:";
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
    vector<Clause> to_check = clauses;
    auto start = std::chrono::high_resolution_clock::now();
    int b = DPLL(clauses, solution, uncomplemented, complemented);
    auto end = std::chrono::high_resolution_clock::now();
    if (b == 0) {
        // Satsified
        // call clean_solution
        clean_solution(solution);
        cout << "\t\tRESULT:SAT" << endl;
        // run_sat() - this prints output in proper format
        print_solution(solution);
        check(to_check, solution);
        std::chrono::duration<double> elapsed = end - start;
        cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;
    }
    else {
        // Unsatisfied
        cout << "\t\tRESULT:UNSAT" << endl;
        ++unsat;
        std::chrono::duration<double> elapsed = end - start;
        cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;
        //exit(3);
    }

    cout << " Fail # " << fail << endl;
    cout << " Unsat # " << unsat << endl;
    cout << " Sat # " << sat << endl;

    return 0;
}