//
// Created by Husam Study on 3/14/2025.
//

#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "Clause.h"
#include <vector>
#include <algorithm>

// GLOBAL VARIABLES!




/************************************
 *
 *
 *               DPLL
 *
 *
 ***********************************/

int DPLL(vector<Clause> & clauses, vector<int> & solution, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp, bool & sat);

/************************************
 *
 *
 *         UN/UPDATE CLAUSES
 *
 *
 ***********************************/

int do_update_clauses(vector<Clause> & clauses, const int & literal, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp);

void undo_update_clauses(vector<Clause> & clauses, const int & literal, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp);

/************************************
 *
 *
 *         UN/UPDATE SOLUTION
 *
 *
 ***********************************/

void do_update_solution(vector<int> & solution, const int & literal);

void undo_update_solution(vector<int> & solution, const int & literal);

/************************************
 *
 *
 *        UNIT CLAUSE FUNCTIONS
 *
 *
 ***********************************/

int unit_handle_duplicates(const vector<Clause> & clauses, vector<int> & units);

int unit_find_false(const vector<bool> & bools);

int unit_find_variable(vector<int> & units, const int & literal);

int unit_update_function(vector<Clause> & clauses, const int & literal)


#endif //HEURISTICS_H
