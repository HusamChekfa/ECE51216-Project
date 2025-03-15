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

using namespace std;

int main() {
    vector<Clause> clauses;
    //std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    int a = Parse("C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf", clauses);
    cout << a;

    return 0;
}