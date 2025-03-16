//
// Created by Husam Study on 3/14/2025.
//

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "Clause.h"
#include <unordered_map>

int Parse(const std::string & filename, std::vector<Clause> & clauses);

int mapParse(const std::string & filename, std::unordered_map<unsigned int, std::vector<Clause>> & clauses);

int addClauseToMap(std::unordered_map<unsigned int, std::vector<Clause>> & clauses, const Clause& newClause);

#endif //PARSER_H
