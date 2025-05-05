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
        //a//cout << "\t\tSUCCESS !!!! " << endl;
        //print_solution(sol);
        ++sat;
    }
    else {
        //a//cout << "\t\tWRONG SOLUTION!!!!! " << endl;
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
    //a//cout << "\t\tASSIGNMENT:";
    for (int i = 1; i < sol.size(); ++i) {
        //a//cout << i << "=" << (sol[i] == 1 ? "1 " : "0 ");
    }
    cout << endl;
}

int main() {
    std::vector<double> elapsed_seconds;
    string path = "";// "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf20-01-small.cnf";
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
    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf100-430/"; // 1000 UNSAT

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf125-538/"; // 100 SAT
    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf125-538/"; // 100 UNSAT

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf150-645/"; // 100 SAT
    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf150-645/"; // 100 UNSAT

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf175-753/"; // 100 SAT
    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf175-753/"; // 100 UNSAT

    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf200-860/"; // 100 SAT
    path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf200-860/"; // 100 UNSAT

    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf225-960/"; // 100 SAT
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf225-960/"; // 100 UNSAT

    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf250-1065/"; // 100 SAT
    //path = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uuf250-1065/"; // 100 UNSAT





    vector<string> paths;
    //paths.push_back(path);
    //paths.push_back("C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/uf125-538/uf125-054.cnf");
    for (const auto& entry : filesystem::directory_iterator(path)) {
        paths.push_back(path + entry.path().filename().string());
    }
    //for (const auto & a : paths) cout << a << endl;
    //path += "uuf50-01.cnf";
    //paths.push_back(path);

    // for (string s : paths) {
    //     cout << s << endl;
    // }
   // paths.push_back(path);
    //paths.push_back("broken.cnf");

    for (const string & p : paths) {
        size_t numVars = 0;
        //a//cout << p << endl;
        vector<Clause> clauses;

        int a = Parse(p, clauses, numVars);
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
            //a//cout << "\t\tRESULT:SAT" << endl;
            // run_sat() - this prints output in proper format
            print_solution(solution);
            check(to_check, solution);
            std::chrono::duration<double> elapsed = end - start;
            cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;
            elapsed_seconds.push_back(elapsed.count());
        }
        else {
            // Unsatisfied
            //a//cout << "\t\tRESULT:UNSAT" << endl;
            ++unsat;
            std::chrono::duration<double> elapsed = end - start;
            cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;
            elapsed_seconds.push_back(elapsed.count());
            //exit(3);
        }
    }
    cout << endl << endl << endl << endl;

    ///for (double elapsed_second : elapsed_seconds) {
    ///    cout << elapsed_second << endl;
    ///}

    cout << " Fail # " << fail << endl;
    cout << " Unsat # " << unsat << endl;
    cout << " Sat # " << sat << endl;

    if (!path.empty() && path.back() == '/') {
        path.pop_back();
    }

    // Find last slash
    size_t lastSlash = path.find_last_of("/\\");
    std::string lastPart = path.substr(lastSlash + 1);

    //std::cout << "Last part: " << lastPart << "\n"; // Outputs: uf20-91
    lastPart += ".txt";

    std::ofstream outFile(lastPart);
    if (!outFile) {
        std::cerr << "Failed to open file: " << lastPart << "\n";
        return 1;
    }

    for (double val : elapsed_seconds) {
        outFile << val << "\n";
    }



    return 0;
}