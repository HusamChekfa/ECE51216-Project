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
    vector<Clause> clauses;
    string fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf";
    cout << "Current working directory: " << filesystem::current_path() << endl;
    int a = Parse(fileName, clauses);
    cout << a << endl;
    cout << g_Unit_count << endl;
    cout << g_Clause_Count << endl;



    return 0;
}