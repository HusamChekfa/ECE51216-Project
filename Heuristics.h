//
// Created by Husam Study on 3/14/2025.
//

#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "Clause.h"
#include <unordered_map>
#include <vector>
#include <algorithm>


/************************************
 *
 *
 *      UNIT CLAUSE HEURISTICS
 *
 *
 ***********************************/
// MAIN function that handles checking & dealing with ALL unit clauses
// checks if anything exists in the vector in map_clauses[1] which holds the unit clauses
// if there exists anything:
/*
 *   --- SANITIZE UNIT CLAUSES ---
 *   look for variable duplicates:
 *      delete duplicates LITERALS BUT keep original (first seen) (ex. a * a * a -> a)
 *      upon seeing variable's complement, escape. current solution fails. (ex. a * a' = 0)
 *   --- NOW DUPLICATES & OPPOSITES ARE GONE FROM UNIT CLAUSES ---
 *   iterate thru each unit clause
 *      any matching literal in clauses size 2+ = satisfied, remove clauses.
 *      any opposite literal in clauses size 2+ = unresolved, remove variable from clause, move clause to --its_Size
 */

// MAIN unit clause heuristic function.
/*
 * Return values:
 *   (currently don't have an idea why to differentiate b/w successes. Could be useful later. Easy to implement too.)
 *   -1 = fail. Opposite units were found (a * -a = 0). Current solution is unsat. Choose another sol.
 *   0 = successful. But nothing was done (no unit clauses found).
 *   1+ = successful. No opposite units found. Handled unit clauses. There was 1+ unit clause.
 */
int unit(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses);


// duplicate handler
/*
 *   remove all duplicates found (ex. a * a * a * a -> a)
 *   if opposite is found, return -1. this solution fails. (ex. a * -a = 0)
 *   Return values:
 *     (currently don't have an idea why to differentiate b/w successes. Could be useful later. Easy to implement too.)
 *     -1 = fail. Opposites found.
 *     0 = successful. No units found. --> useless, can just check if map.at(1).size() == 0
 *     1 = successful. Units found. No opposites.ok 
 *
 *     0 = successful. But no duplicates found.
 *     1+ = successful. No duplicates found. No opposites found. Removed duplicates. There were 1+ duplicates.
 */
int unit_handle_duplicates(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses);


// prune non-unit clauses
/*
 *   remove literal existence from nonunit clauses
 *   if same literal found, remove clause entirely (satisfied)
 *   if opposite literal found, remove opposite from clause, move close to map[size-1]
 *     if [size-1] == 1, check for that remaining literal duplicates in unit vector (call unit_prune_handle_duplicates)
 *       if  matched - remove duplicates
 *       if opposite found - escape, solution fails.
 *   Return values:
 *     (currently don't have an idea why to differentiate b/w successes. Could be useful later. Easy to implement too.)
 *     -1 = fail. unit_prune_handle_duplicates was called and opposites were found.
 *     0 = successful. No literals were found.
 *     1+ = idk, awkward since there are = and opposite literals that could be removed. don't need for now.
 */
int unit_prune_nonunit_clauses(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses, int literal, size_t clause_size);


// prune non-unit clauses
/*
 *
 *   if same literal found, remove clause entirely (satisfied)
 *   if opposite literal found, remove opposite from clause, move close to map[size-1]
 *     if [size-1] == 1, check for that remaining literal duplicates in unit vector (call unit_prune_handle_duplicates)
 *       if  matched - remove duplicates
 *       if opposite found - escape, solution fails.
 *   Return values:
 *     (currently don't have an idea why to differentiate b/w successes. Could be useful later. Easy to implement too.)
 *     -1 = fail. unit_prune_handle_duplicates was called and opposites were found.
 *     0 = successful. No literals were found.
 *     1+ = idk, awkward since there are = and opposite literals that could be removed. don't need for now.
 */
int unit_prune_nonunit_clauses2(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses, int literal, size_t clause_size);



// ONLY CALLED BY unit_prune_nonunit_clauses
/*
 *   if  matched - remove duplicates
 *   if opposite found - escape, solution fails.
 *   Return values:
 *      -1 = fail. opposities found. solution doesn't work.
 *      0 = successful. No literals were found.
 *      1+ = successful. No duplicates found. No opposites found. Removed duplicates. There were 1+ duplicates.
 */
int unit_prune_handle_duplicates(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses, int literal);

/************************************
 *
 *
 *          DLSI HEURISTIC
 *
 *
 ***********************************/

#endif //HEURISTICS_H
