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

struct Clause {
    vector<int> literals;
    unsigned int unassigned = 0; // count of unassigned variables
};

int main() {


    //std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    int a = Parse("C:/Users/Husam Study/Documents/GitHub/ECE51216-Project/SAT/20v91c1000iAllSat/uf20-01.cnf");
    cout << a;




    return 0;

}