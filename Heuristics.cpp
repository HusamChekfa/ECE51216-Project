//
// Created by Husam Study on 3/14/2025.
//

#include "Heuristics.h"

int DPLL(vector<Clause> & clauses, vector<int> & solution, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp, bool & sat) {
    int ret = -100;
    vector<int> units_added_to_solution;
    vector<int> clauses_satisfied; // allow easier undo








    
    unsigned count_added = 0;
    while(g_Unit_count != 0) {
        if (unit_handle_duplicates(clauses, units_added_to_solution) == -1) {
            // problem .. backtrack .. a * a' = 0
            return -1;
        }
        for (int val : units_added_to_solution) {
            do_update_solution(solution, val);
            if (do_update_clauses(clauses, val, uncomp, comp) == -1) {
                for (int i = 0; i < count_added; ++i) {
                    undo_update_clauses(clauses, units_added_to_solution[i], uncomp, comp);
                }
                return -1;
            }
            ++count_added;
        }




    }
    // check if all clauses are satisfied; if yes -> formula is SAT!
    if (g_Clause_Count == 0) {
        sat = true;
        return 0;
    }










}

void undo_update_clauses(vector<Clause> & clauses, const int & literal, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp) {
    if (literal > 0) {
        for (const unsigned & i : comp[literal]) {
            clauses[i].assigned_literals[literal] = false;
            ++clauses[i].unassigned;
        }
        for (const unsigned & i : uncomp[literal]) {
            clauses[i].assigned_literals[literal] = false;
            ++clauses[i].unassigned;
            // how to know if it was true or false before we added this variable. rather, it may be g
            if (clauses[i].is_satisfied == true) {

            }





        }
    }
    else {
        for (const unsigned & i : uncomp[-literal]) {
            clauses[i].assigned_literals[-literal] = false;
            ++clauses[i].unassigned;
        }

        // NEEDED HERE TOO!!!!










    }

    if (literal > 0) {
        for (const unsigned & i : comp[literal]) {
            if (count == 0) {
                break;
            }
            clauses[i].assigned_literals[literal] = false;
            ++clauses[i].unassigned;
            -- count;
        }
    }
    else {
        for (const unsigned & i : uncomp[-literal]) {
            if (count == 0) {
                break;
            }
            clauses[i].assigned_literals[-literal] = false;
            ++clauses[i].unassigned;
            -- count;
        }
    }
}

int do_update_clauses(vector<Clause> & clauses, const int & literal, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp) {
    unsigned count = 0; // need for undo, count how many opposite literal clause done so far, in case any get 0'd out, we EXACTLY know how many to un-update
    if (literal > 0) {
        // deal with opposite literal first
        for (const unsigned & i : comp[literal]) {
            if (clauses[i].is_satisfied == false && clauses[i].unassigned == 1) {
                // ERROR !
                goto error_fixing;
            }
            clauses[i].assigned_literals[literal] = true;
            if (--clauses[i].unassigned == 1) {
                ++g_Unit_count;
            }
            ++count;
        }
        // same
        for (const unsigned & i : uncomp[literal]) {
            clauses[i].is_satisfied = true;
            --clauses[i].unassigned;
            --g_Clause_Count;
        }
    }
    else {
        // deal with opposite literal first
        for (const unsigned & i : uncomp[-literal]) {
            if (clauses[i].is_satisfied == false && clauses[i].unassigned == 1) {
                // ERROR !
                goto error_fixing;
            }
            clauses[i].assigned_literals[-literal] = true;
            if (--clauses[i].unassigned == 1) {
                ++g_Unit_count;
            }
            ++count;
        }
        // same
        for (const unsigned & i : comp[-literal]) {
            clauses[i].is_satisfied = true;
            --clauses[i].unassigned;
            --g_Clause_Count;
        }

    }

    return 0;

    error_fixing:
    if (literal > 0) {
        for (const unsigned & i : comp[literal]) {
            if (count == 0) {
                break;
            }
            clauses[i].assigned_literals[literal] = false;
            ++clauses[i].unassigned;
            -- count;
        }
    }
    else {
        for (const unsigned & i : uncomp[-literal]) {
            if (count == 0) {
                break;
            }
            clauses[i].assigned_literals[-literal] = false;
            ++clauses[i].unassigned;
            -- count;
        }
    }

    return -1;
}

void do_update_solution(vector<int> & solution, const int & literal) {
    if (literal > 0) {
        solution[literal] = 1;
    }
    else {
        solution[-literal] = -1;
    }
}

void undo_update_solution(vector<int> & solution, const int & literal) {
    solution[abs(literal)] = 0;
}


int unit_handle_duplicates(const vector<Clause> & clauses, vector<int> & units) {
    //vector<int> units;
    unsigned unit_count = g_Unit_count;
    for (size_t i = 0; i < clauses.size() && unit_count > 0; ++i) {
        if (clauses[i].is_satisfied == false && clauses[i].unassigned == 1) {
            // find false in the vector
            int j = unit_find_false(clauses[i].assigned_literals);
            // check if opposite literal in units - if so, curr sol is UNSAT
            if (unit_find_variable(units, clauses[i].literals[j]) == -1) {
                return -1;
            }
            --unit_count;
        }
    }

    return 0;
}

int unit_find_false(const vector<bool> & bools) {
    for (int i = 0; i < bools.size(); ++i) {
        if (!bools[i]) {
            return i;
        }
    }
    cout << "ERROR: UNIT_FIND_FALSE RETURNED -1" << endl;
    exit(1); // should never happen.
}

int unit_find_variable(vector<int> & units, const int & literal) {
    // first check if opposite is found
    // if so, return -1; unsat (a * a' = 0)
    auto it = find(units.begin(), units.end(), -literal);
    if (it != units.end()) {
        return -1;
    }

    // check if same literal is found
    // if so, only return 1
    // if not, add literal to units then return 0
    it = find(units.begin(), units.end(), literal);
    if (it != units.end()) {
        return 1;
    }

    units.push_back(literal);

    return 0;
}

// use goto:



