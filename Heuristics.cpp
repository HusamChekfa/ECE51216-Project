//
// Created by Husam Study on 3/14/2025.
//

#include "Heuristics.h"
#include <algorithm>

void t_val(const vector<Clause> & clauses) {
    unsigned units = 0;
    unsigned c_count = 0;
    for (const Clause & c : clauses) {
        if (!c.is_satisfied) {
            ++c_count;
            if (c.unassigned == 1) ++units;
        }
    }
    g_Unit_count = units;
    g_Clause_Count = c_count;
}

int DPLL(vector<Clause> & clauses, vector<int> & solution, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp) {
    vector<int> units_added_to_solution;
    unordered_set<unsigned> clauses_satisfied; // allow easier undo
    int while_unit_count = 0;
    unsigned count_added = 0;
    vector<int> unates_added_to_solution;
    t_val(clauses);

    while ((g_Unit_count != 0) || (!g_Unates.empty())) {
        while(g_Unit_count != 0) {

            if (unit_handle_duplicates(clauses, units_added_to_solution) == -1) {
                // problem .. backtrack .. a * a' = 0

                for (int i = 0; i < count_added; ++i) {
                    undo_update_clauses(clauses, units_added_to_solution[i], uncomp, comp);
                    undo_update_solution(solution, units_added_to_solution[i]);
                }
                for (int i : unates_added_to_solution) {
                    undo_update_clauses(clauses, i, uncomp, comp);
                    undo_update_solution(solution, i);
                }
                undo_update_clauses_satisfied(clauses, clauses_satisfied);

                t_val(clauses);
                return -1;
            }

            for (int temp = while_unit_count; temp < units_added_to_solution.size(); ++temp) {//(int val : units_added_to_solution) {
                do_update_solution(solution, units_added_to_solution[temp]); // val instead of u[t]
                if (do_update_clauses(clauses, units_added_to_solution[temp], uncomp, comp, clauses_satisfied) == -1) { // val instead of u[t]
                    for (int i = 0; i < count_added; ++i) {
                        undo_update_clauses(clauses, units_added_to_solution[i], uncomp, comp);
                        undo_update_solution(solution, units_added_to_solution[i]);
                    }
                    for (int i : unates_added_to_solution) {
                        undo_update_clauses(clauses, i, uncomp, comp);
                        undo_update_solution(solution, i);
                    }
                    undo_update_solution(solution, units_added_to_solution[temp]);
                    undo_update_clauses_satisfied(clauses, clauses_satisfied);

                    t_val(clauses);
                    return -1;
                }
                ++count_added;
                ++while_unit_count;
            }
        }
        DLIS_find_unate(solution);
        t_val(clauses);


        while ((g_Unit_count == 0) && (!g_Unates.empty())) {
            // same as unit but for unates; break asap when u see there is  a unit that's why == not != for unit count
            // remove from unate
            int val = *g_Unates.begin();
            unates_added_to_solution.push_back(val);
            g_Unates.erase(val);
            do_update_solution(solution, val);
            do_update_clauses(clauses, val, uncomp, comp, clauses_satisfied);
            t_val(clauses);
        }

        DLIS_find_unate(solution);
        t_val(clauses);
    }

    // check if all clauses are satisfied; if yes -> formula is SAT!
    //t_val(clauses);
    if (g_Clause_Count == 0) {
        return 0;
    }

    unordered_set<unsigned> clauses_satisfied_dpll;

    int literalChoice = 0;

    unsigned max_sum = 0;
    for (int i = 1; i < solution.size(); ++i) {
        if (solution[i] != 0) continue;

        unsigned curr_sum = g_dlis_pos[i] + g_dlis_neg[i];
        if (curr_sum > max_sum) {
            max_sum = curr_sum;
            literalChoice = i;
        }
    }

    if (literalChoice == 0) {
        return -1;
    }

    //t_val(clauses);

    decision_one:
    // add decision to solution
    do_update_solution(solution, literalChoice);
    // update_function wrt decision
    if (do_update_clauses(clauses, literalChoice, uncomp, comp, clauses_satisfied_dpll) == -1) {
        undo_update_solution(solution, literalChoice);
        goto decision_two;
    }

    // call DPLL

    if (DPLL(clauses, solution, uncomp, comp) == 0) {
        return 0;
    }

    undo_update_clauses(clauses, literalChoice, uncomp, comp);
    undo_update_clauses_satisfied(clauses, clauses_satisfied_dpll);// dpll_units_sat);
    clauses_satisfied_dpll.clear();
    undo_update_solution(solution, literalChoice);

    t_val(clauses);

    decision_two:

    literalChoice *= -1;

    do_update_solution(solution, literalChoice);

    if (do_update_clauses(clauses, literalChoice, uncomp, comp, clauses_satisfied_dpll) == -1) {
        undo_update_solution(solution, literalChoice);
        goto both_fail;
    }

    if (DPLL(clauses, solution, uncomp, comp) == 0) {
        return 0;
    }

    undo_update_clauses(clauses, literalChoice, uncomp, comp);
    undo_update_clauses_satisfied(clauses, clauses_satisfied_dpll);
    undo_update_solution(solution, literalChoice);


    both_fail:


    for (const int & i : units_added_to_solution) {
        undo_update_clauses(clauses, i, uncomp, comp);
        undo_update_solution(solution, i);
    }
    for (const int & i : unates_added_to_solution) {
        undo_update_clauses(clauses, i, uncomp, comp);
        undo_update_solution(solution, i);
    }
    undo_update_clauses_satisfied(clauses, clauses_satisfied);

    t_val(clauses);
    return -1;
}

void undo_update_DLIS(const int &literal) {
    if (literal > 0) {
        ++g_dlis_pos[literal];
    }
    else {
        ++g_dlis_neg[-literal];
    }
}

void do_update_DLIS(const int &literal) {
    if (literal > 0) {
        --g_dlis_pos[literal];
    }
    else {
        --g_dlis_neg[-literal];
    }
}


void DLIS_find_unate(const vector<int> &curr_sol) {
    unordered_set<int> unates;
    for (int i = 1; i < curr_sol.size(); ++i) {
        // skip if variable is already assigned
        if (curr_sol[i] != 0) continue;

        const bool pos_unate = (g_dlis_neg[i] == 0);
        const bool neg_unate = (g_dlis_pos[i] == 0);

        // 4 possibilites
        // binate -> skip
        // both 0 -> skip
        // pos unate true, negunate false -> insert i
        // pos unate false, negunate true -> insert -i
        if (pos_unate != neg_unate) {
            unates.insert(pos_unate ? i : -i);
        }
    }
    g_Unates = unates;
}

void undo_update_clauses_satisfied(vector<Clause> & clauses, const unordered_set<unsigned> & clauses_satisfied) { //const vector<unsigned> & units_sat) {
    for (const unsigned & i : clauses_satisfied) {
        clauses[i].is_satisfied = false;

        for (int x : clauses[i].lits) {
            undo_update_DLIS(x);
        }
    }

    t_val(clauses);
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
        }
    }
    else {
        for (const unsigned & i : uncomp[-literal]) {
            clauses[i].assigned_literals[-literal] = false;
            ++clauses[i].unassigned;
        }
        for (const unsigned & i : comp[-literal]) {
            clauses[i].assigned_literals[-literal] = false;
            ++clauses[i].unassigned;
        }
    }
}

int do_update_clauses(vector<Clause> & clauses, const int & literal, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp, unordered_set<unsigned> & clauses_satisfied) {
    unsigned count = 0; // need for undo, count how many opposite literal clause done so far, in case any get 0'd out, we EXACTLY know how many to un-update
    if (literal > 0) {
        // deal with opposite literal first
        for (const unsigned & i : comp[literal]) {
            if (clauses[i].is_satisfied == false && clauses[i].unassigned == 1) {
                // ERROR !
                goto error_fixing;
            }
            clauses[i].assigned_literals[literal] = true;
            --clauses[i].unassigned;
            ++count;
        }
        // same
        for (const unsigned & i : uncomp[literal]) {
            --clauses[i].unassigned;
            clauses[i].assigned_literals[literal] = true;
            if (clauses[i].is_satisfied == false) {
                clauses[i].is_satisfied = true;

                clauses_satisfied.insert(i);
                for (int x : clauses[i].lits) {
                    do_update_DLIS(x);
                }
            }
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
            if (--clauses[i].unassigned == 1 && clauses[i].is_satisfied == false) {

            }
            ++count;
        }
        // same
        for (const unsigned & i : comp[-literal]) {
            --clauses[i].unassigned;
            clauses[i].assigned_literals[-literal] = true;
            if (clauses[i].is_satisfied == false) {
                clauses[i].is_satisfied = true;

                for (int x : clauses[i].lits) {
                    do_update_DLIS(x);
                }
                clauses_satisfied.insert(i);
            }
        }

    }
    t_val(clauses);

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
            if (++clauses[i].unassigned == 2 && clauses[i].is_satisfied == false) { // before just == 2

            }
            -- count;
        }
    }
    t_val(clauses);
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
            int j = unit_find_false(clauses[i].literals, clauses[i].assigned_literals);
            // check if opposite literal in units - if so, curr sol is UNSAT
            if (unit_find_variable(units, clauses[i].literals[j]*j) == -1) {
                return -1;
            }
            --unit_count;
        }
    }

    return 0;
}

int unit_find_false(const vector<int> & literals, const vector<bool> & bools) {
    for (int i = 1; i < bools.size(); ++i) {
        if (literals[i] != 0 && !bools[i]) {
            return i;
        }
    }

    exit(1); // should never happen.
}

int unit_find_variable(vector<int> & units, const int & literal) {
    // first check if opposite is found
    // if so, return -1; unsat (a * a' = 0)
    auto it = ranges::find(units, -literal);
    if (it != units.end()) {
        return -1;
    }

    // check if same literal is found
    // if so, only return 1
    // if not, add literal to units then return 0
    it = ranges::find(units, literal);
    if (it != units.end()) {
        return 1;
    }

    units.push_back(literal);

    return 0;
}