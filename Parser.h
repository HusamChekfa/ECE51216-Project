//
// Created by Husam Study on 3/14/2025.
//

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "Clause.h"
#include <unordered_map>

int Parse(const string & filename, vector<Clause> & clauses);

int mapParse(const string & filename, unordered_map<unsigned, vector<Clause>> & clauses);

int addClauseToMap(unordered_map<unsigned, vector<Clause>> & clauses, const Clause& newClause);

#endif //PARSER_H
