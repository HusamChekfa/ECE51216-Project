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
#include <unordered_map>
#include "Heuristics.h"



int main() {
    vector<Clause> clauses;
    string fileName = "C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf";
    //std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    int a = Parse(fileName, clauses);
    //cout << a;

    unordered_map<unsigned int, vector<Clause>> map_clauses;
    int b = mapParse(fileName, map_clauses);
    cout << b;

    map_clauses.at(0).at(0).literals.s



    return 0;
}