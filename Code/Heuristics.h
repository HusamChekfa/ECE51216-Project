//
// Created by Husam Study on 3/14/2025.
//

#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "Clause.h"
#include <vector>
#include <unordered_set>

/************************************
 *
 *
 *               DPLL
 *
 *
 ***********************************/

int DPLL(vector<Clause> & clauses, vector<int> & solution, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp);

/************************************
 *
 *
 *               DLIS
 *
 *
 ***********************************/

void DLIS_find_unate(const vector<int> & curr_sol);

void do_update_DLIS(const int & literal);

void undo_update_DLIS(const int & literal);

/************************************
 *
 *
 *         UN/UPDATE CLAUSES
 *
 *
 ***********************************/

int do_update_clauses(vector<Clause> & clauses, const int & literal, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp, unordered_set<unsigned> & clauses_satisfied);

void undo_update_clauses(vector<Clause> & clauses, const int & literal, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp);

void undo_update_clauses_satisfied(vector<Clause> & clauses, const unordered_set<unsigned> & clauses_satisfied); //const vector<unsigned> & units_sat);

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

int unit_find_false(const vector<int> & literals, const vector<bool> & bools); // was just bools; need literals since literals & bools size = # of vars not # in clause

int unit_find_variable(vector<int> & units, const int & literal);

#endif //HEURISTICS_H