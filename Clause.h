// Clause.h
#ifndef CLAUSE_H
#define CLAUSE_H

#include <vector>
#include <iostream>

using namespace std;

enum Variable { COMPLEMENT = -1, UNASSIGNED = 0, UNCOMPLEMENT = 1};

// globals: defined in Clause.cpp
extern unsigned g_Clause_Count; // global - # of unresolved clauses
extern unsigned g_Unit_count;   // global - # of unit clauses

struct Clause {
    vector<int> literals;
    vector<bool> assigned_literals; // keep track of which literals have an assigned value
    unsigned unassigned = 0; // count of unassigned variables // might not be useful if we go for the map BCP
    bool is_satisfied = false; // whether clause is satisfied

};

#endif // CLAUSE_H
