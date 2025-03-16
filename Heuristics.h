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

int unit_handle_duplicates(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses);

/************************************
 *
 *
 *          DLSI HEURISTIC
 *
 *
 ***********************************/

#endif //HEURISTICS_H
