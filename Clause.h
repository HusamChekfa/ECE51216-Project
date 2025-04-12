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
    vector<int> literals; // 0 1 2 3 4 5 // 0 1 0 0 -1 -1
    vector<bool> assigned_literals; // keep track of which literals have an assigned value
    vector<int> lits; // 1 -4 -5;
    unsigned unassigned = 0; // count of unassigned variables // might not be useful if we go for the map BCP
    bool is_satisfied = false; // whether clause is satisfied


    /*
     *  DLIS + [  , , , ,  , ]
     *  DLIS - [ , , , ,  ]
     *
     *  1 2 3 4 5 6 7 8 .. 19000
     *
     *  1 2 3
     *
     *
     *
     *
     **/

};

#endif // CLAUSE_H
