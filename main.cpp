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

int main() {
    string path = "";
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/";
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/50v218c1000iAllSat/";
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/50v218c1000iAllUnSat/";
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf20-01-small.cnf";
    //string path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/";
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf";
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/broken.cnf";

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf20-91/"; // 1000 SAT

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf50-218/"; // 1000 SAT
    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf50-218/"; // 1000 UNSAT

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf75-325/"; // 100 SAT
    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf75-325/"; // 100 UNSAT

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf100-430/"; // 1000 SAT
    // works //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf100-430/"; // 1000 UNSAT

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf125-538/"; // 100 SAT
    // works //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf125-538/"; // 100 UNSAT

    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf150-645/"; // 100 SAT
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf150-645/"; // 100 UNSAT

    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf175-753/"; // 100 SAT
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf175-753/"; // 100 UNSAT

    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf200-860/"; // 100 SAT
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf200-860/"; // 100 UNSAT

    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf225-960/"; // 100 SAT
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf225-960/"; // 100 UNSAT

    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf250-1065/"; // 100 SAT
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf250-1065/"; // 100 UNSAT





    vector<string> paths;
    for (const auto& entry : filesystem::directory_iterator(path)) {
        paths.push_back(path + entry.path().filename().string());
    }
    //path += "uuf50-01.cnf";
    //paths.push_back(path);

    // for (string s : paths) {
    //     cout << s << endl;
    // }
   // paths.push_back(path);
    //paths.push_back("broken.cnf");

    for (const string & p : paths) {
        for (int yyy = 0; yyy < 4; ++yyy) {
            g_rec = 0;
            //global_start_time = std::chrono::high_resolution_clock::now();
            //global_end_time = std::chrono::high_resolution_clock::now();
            size_t numVars = 0;
            cout << p << endl;
            bool satisfied = false;
            vector<Clause> clauses;
            //solution.clear();
            //uncomplemented.clear();
            //complemented.clear();
            //fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/ok.cnf";

            int a = Parse(p, clauses, numVars);
            vector<int> solution(numVars + 1, 0);
            vector<vector<unsigned>> uncomplemented(numVars + 1);
            vector<vector<unsigned>> complemented(numVars + 1);
            int c = Parse_uncomp(clauses, uncomplemented, complemented);
            vector<Clause> to_check = clauses;
            auto start = std::chrono::high_resolution_clock::now();
            int b = DPLL(clauses, solution, uncomplemented, complemented, satisfied);
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
                //exit(3);
            }
        }
    }

    cout << " Fail # " << fail << endl;
    cout << " Unsat # " << unsat << endl;
    cout << " Sat # " << sat << endl;

    return 0;


    /*
    size_t numVars = 0;
    //vector<Clause> clauses(1);
    vector<Clause> clauses;
    //vector<int> solution;

    bool satisfied = false;

    string fileName = "";
    fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf";
    fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf20-01-small.cnf";


    //fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/b.cnf";
    //fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/quinn.cnf";
    //fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/ok.cnf";
    fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/global.cnf";


    cout << "Current working directory: " << filesystem::current_path() << endl;
    int a = Parse(fileName, clauses, numVars);

    vector<int> solution(numVars + 1, 0);
    vector<vector<unsigned>> uncomplemented(numVars + 1);
    vector<vector<unsigned>> complemented(numVars + 1);
    int c = Parse_uncomp(clauses, uncomplemented, complemented);

    vector<Clause> to_check = clauses;

    int b = DPLL(clauses, solution, uncomplemented, complemented, satisfied);

    // STDOUT?
    if (b == 0) {
        // Satsified
        // call clean_solution
        clean_solution(solution);
        cout << "RESULT:SAT" << endl;
        // run_sat() - this prints output in proper format
        print_solution(solution);
        check(to_check, solution);

    }
    else {
        // Unsatisfied
        cout << "RESULT:UNSAT" << endl;
    }

    string path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/";
    vector<string> paths;
    for (const auto& entry : filesystem::directory_iterator(path)) {
        paths.push_back(path + entry.path().filename().string());
    }

    for (string s : paths) {
        cout << s << endl;
    }

    satisfied = false;
    solution.clear();
    clauses.clear();
    uncomplemented.clear();
    complemented.clear();
    to_check.clear();
    //fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/ok.cnf";

    a = Parse("C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/ok.cnf", clauses, numVars);
    c = Parse_uncomp(clauses, uncomplemented, complemented);
    to_check = clauses;
    b = DPLL(clauses, solution, uncomplemented, complemented, satisfied);
    if (b == 0) {
        // Satsified
        // call clean_solution
        clean_solution(solution);
        cout << "RESULT:SAT" << endl;
        // run_sat() - this prints output in proper format
        print_solution(solution);
        check(to_check, solution);

    }
    else {
        // Unsatisfied
        cout << "RESULT:UNSAT" << endl;
    }

    */

    return 0;
}