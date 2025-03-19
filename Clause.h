// Clause.h
#ifndef CLAUSE_H
#define CLAUSE_H

#include <vector>

using namespace std;

// globals: defined in Clause.cpp
extern unsigned g_Clause_Count; // global - # of unresolved clauses
extern unsigned g_Unit_count;   // global - # of unit clauses

struct Clause {
    vector<int> literals;
    unsigned unassigned = 0; // count of unassigned variables // might not be useful if we go for the map BCP
    bool satisfied = false; // whether clause is satisfied
};

#endif // CLAUSE_H
