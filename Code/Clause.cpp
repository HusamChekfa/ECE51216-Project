//
// Created by Husam Study on 3/14/2025.
//

#include "Clause.h"

unsigned g_Clause_Count = 0; // global - # of unresolved clauses
unsigned g_Unit_count = 0;   // global - # of unit clauses
unordered_set<int> g_Unates;

vector<int> g_dlis_pos;
vector<int> g_dlis_neg;

