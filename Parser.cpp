//
// Created by Husam Study on 3/14/2025.
//

#include "Parser.h"
#include <fstream>
#include <iostream>

using fs = std::fstream;

int Parse(const std::string &filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();

    return 0;
}

