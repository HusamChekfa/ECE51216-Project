//
// Created by Husam Study on 3/14/2025.
//

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "Clause.h"

int Parse(const string & filename, vector<Clause> & clauses, vector<vector<unsigned>> & uncomp, vector<vector<unsigned>> & comp);



#endif //PARSER_H
