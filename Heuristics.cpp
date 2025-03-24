//
// Created by Husam Study on 3/14/2025.
//

#include "Heuristics.h"

int DPLL(vector<Clause> & clauses, vector<int> & solution, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp, bool & sat) {
    int ret = -100;
    static int recursive = 1;
    //static int hey = 0;
    vector<int> units_added_to_solution;
    unordered_set<unsigned> clauses_satisfied; // allow easier undo
    vector<unsigned> while_units_sat;
    int while_unit_count = 0;
    int total = 0;

    unsigned count_added = 0;
    while(g_Unit_count != 0) {
        //cout << "hey";
        //++hey;
        //if (hey == 7) {
            //cout << "7hey";
        //}
        if (unit_handle_duplicates(clauses, units_added_to_solution) == -1) {
            // problem .. backtrack .. a * a' = 0
            for (int i = 0; i < count_added; ++i) {
                undo_update_clauses(clauses, units_added_to_solution[i], uncomp, comp);
                undo_update_solution(solution, units_added_to_solution[i]);
            }
            undo_update_clauses_satisfied(clauses, clauses_satisfied, while_units_sat);
            return -1;
        }
        for (int f = while_unit_count; f < units_added_to_solution.size(); ++f) {
            cout << "unit: " << units_added_to_solution[f] << endl;
            if  (units_added_to_solution[f] == 14) {
                cout << "14!!!!" << endl;
            }
        }
        total = 0;
        for (int x = 0; x < clauses.size(); ++x) {
            if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
                ++total;
                cout << "unit clause = " << x << endl;
            }
        }
        if (total != g_Unit_count) {
            cout << "not equalAAAA!" << endl;
        }
        for (int temp = while_unit_count; temp < units_added_to_solution.size(); ++temp) {//(int val : units_added_to_solution) {
            total = 0;
            for (int x = 0; x < clauses.size(); ++x) {
                if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
                    ++total;
                    cout << "unit clause = " << x << endl;
                }
            }
            if (total != g_Unit_count) {
                cout << "not equalBBB!" << endl;
            }
            do_update_solution(solution, units_added_to_solution[temp]); // val instead of u[t]
            if (do_update_clauses(clauses, units_added_to_solution[temp], uncomp, comp, clauses_satisfied, while_units_sat) == -1) { // val instead of u[t]
                total = 0;
                for (int x = 0; x < clauses.size(); ++x) {
                    if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
                        ++total;
                        cout << "unit clause = " << x << endl;
                    }
                }
                if (total != g_Unit_count) {
                    cout << "not equalFFFFF!" << endl; // NOT ENTERING
                }
                for (int i = 0; i < count_added; ++i) {
                    undo_update_clauses(clauses, units_added_to_solution[i], uncomp, comp);
                    total = 0;
                    for (int x = 0; x < clauses.size(); ++x) {
                        if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
                            ++total;
                            cout << "unit clause = " << x << endl;
                        }
                    }
                    if (total != g_Unit_count) {
                        cout << "not equalGGGGGG!" << endl;
                    }
                    undo_update_solution(solution, units_added_to_solution[i]);
                    total = 0;
                    for (int x = 0; x < clauses.size(); ++x) {
                        if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
                            ++total;
                            cout << "unit clause = " << x << endl;
                        }
                    }
                    if (total != g_Unit_count) {
                        cout << "not equalHHHHHH!" << endl;
                    }
                }
                undo_update_solution(solution, units_added_to_solution[temp]);
                total = 0;
                for (int x = 0; x < clauses.size(); ++x) {
                    if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
                        ++total;
                        cout << "unit clause = " << x << endl;
                    }
                }
                if (total != g_Unit_count) {
                    cout << "not equalIIIIII!" << endl;
                }
                undo_update_clauses_satisfied(clauses, clauses_satisfied, while_units_sat);
                cout << "we're here!!!" << endl;
                total = 0;
                for (int x = 0; x < clauses.size(); ++x) {
                    if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
                        ++total;
                        cout << "unit clause = " << x << endl;
                    }
                }
                if (total != g_Unit_count) {
                    cout << "not equalCCC!" << endl;
                }
                return -1;
            }
            ++count_added;
            ++while_unit_count;
        }
    }
    // check if all clauses are satisfied; if yes -> formula is SAT!
    if (g_Clause_Count == 0) {
        sat = true;
        return 0;
    }

    unordered_set<unsigned> clauses_satisfied_dpll;
    //unordered_set<unsigned> union_clauses;
    int literalChoice = 0;
    // make branch decision
    for (int i = 1; i < solution.size(); ++i) { // i starts at 1 since our vectors are size #vars + 1 for ease of reading, vec[0] is unused
        if (solution[i] == 0) {
            literalChoice = i;
            break;
        }
    }
    // if (literalChoice == 16) {
    //     cout << "16";
    // }
    cout << literalChoice << endl;
    if (literalChoice == 0) {
        // no more variables without a solution
        cout << " no literal c hoices !!! " << endl;
        return -1;
    }
    cout << "recursive = " << recursive << endl;
    ++recursive;
    if (recursive == 30) {
        cout << "recursive = 16";
        //exit(1);
    }

    vector<unsigned> dpll_units_sat;



    decision_one:
    // add decision to solution
    do_update_solution(solution, literalChoice);
    // update_function wrt decision
    if (do_update_clauses(clauses, literalChoice, uncomp, comp, clauses_satisfied_dpll, dpll_units_sat) == -1) {
        undo_update_solution(solution, literalChoice);
        goto decision_two;
    }
    // call DPLL
    if (DPLL(clauses, solution, uncomp, comp, sat) == 0) {
        // sat
        // don't think I need this:
        // sat = true;
        return 0;
    }

    total = 0;
    for (int x = 0; x < clauses.size(); ++x) {
        if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
            ++total;
            cout << "unit clause = " << x << endl;
        }
    }
    if (total != g_Unit_count) {
        cout << "not equalDDD!" << endl;
    }

    undo_update_clauses(clauses, literalChoice, uncomp, comp);
    undo_update_clauses_satisfied(clauses, clauses_satisfied_dpll, dpll_units_sat);
    clauses_satisfied_dpll.clear();
    dpll_units_sat.clear();
    undo_update_solution(solution, literalChoice);



    decision_two:

    literalChoice *= -1;

    total = 0;
    for (int x = 0; x < clauses.size(); ++x) {
        if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
            ++total;
        }
    }
    if (total != g_Unit_count) {
        cout << "not equalEEE!" << endl;
    }

    do_update_solution(solution, literalChoice);

    if (do_update_clauses(clauses, literalChoice, uncomp, comp, clauses_satisfied_dpll, dpll_units_sat) == -1) {
        undo_update_solution(solution, literalChoice);
        goto both_fail;
    }
    if (DPLL(clauses, solution, uncomp, comp, sat) == 0) {
        // sat
        // don't think I need this:
        // sat = true;
        return 0;
    }

    for (unsigned x : while_units_sat) {
        dpll_units_sat.push_back(x);
    }

    undo_update_clauses(clauses, literalChoice, uncomp, comp);
    undo_update_clauses_satisfied(clauses, clauses_satisfied_dpll, dpll_units_sat);
    //clauses_satisfied_dpll.clear();
    undo_update_solution(solution, literalChoice);
    cout << literalChoice << endl;


    both_fail:


    for (const int & i : units_added_to_solution) {
        undo_update_clauses(clauses, i, uncomp, comp);
        undo_update_solution(solution, i);
    }
    //undo_update_clauses_satisfied(clauses, clauses_satisfied);
    --recursive;

    return -1;
    /*
    // if (do_update_clauses(clauses, literalChoice, uncomp, comp, clauses_satisfied_dpll) == -1) {
    //     for (int i = 0; i < count_added; ++i) {
    //         undo_update_clauses(clauses, units_added_to_solution[i], uncomp, comp);
    //     }
    //     //undo_update_clauses_satisfied(clauses, clauses_satisfied_dpll);
    //     return -1;
    // }
    //
    // undo_update_clauses()

    // make branch decision
    // add decision to solution
    // update_function wrt decision
    // call DPLL

     *  if (DPLL(...) == 0) {
     *      sat = true;
     *      return 0;
     *  }
     *  // else
     *  undo_update_funct wrt decision
     *  remove decision from solution
     *  add complement of decision to solution
     *  update_func wrt to complemented deiciosn
     *  call dpll
     *  if (DPLL(...) == 0) {
     *      sat = true;
     *      return 0;
     *  }
     *  // else
     *  undo_update_funct wrt complemented decision
     *  remove deicison from solution
     *  return -1; // backtrack.
     */
}

void undo_update_clauses_satisfied(vector<Clause> & clauses, const unordered_set<unsigned> & clauses_satisfied, const vector<unsigned> & units_sat) {
    for (const unsigned & i : clauses_satisfied) {
        clauses[i].is_satisfied = false;
        /*if (clauses[i].unassigned == 1) {
            ++g_Unit_count;
        }*/
    }
    g_Unit_count -= units_sat.size();
    g_Clause_Count += clauses_satisfied.size();
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

int do_update_clauses(vector<Clause> & clauses, const int & literal, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp, unordered_set<unsigned> & clauses_satisfied, vector<unsigned> & units_satisfied) {
    unsigned count = 0; // need for undo, count how many opposite literal clause done so far, in case any get 0'd out, we EXACTLY know how many to un-update
    if (literal > 0) {
        // deal with opposite literal first
        for (const unsigned & i : comp[literal]) {
            if (clauses[i].is_satisfied == false && clauses[i].unassigned == 1) {
                // ERROR !
                goto error_fixing;
            }
            clauses[i].assigned_literals[literal] = true;
            if (--clauses[i].unassigned == 1 && clauses[i].is_satisfied == false) {
                ++g_Unit_count;
            }
            ++count;
        }
        // same
        for (const unsigned & i : uncomp[literal]) {
            --clauses[i].unassigned;
            clauses[i].assigned_literals[literal] = true;
            if (clauses[i].is_satisfied == false) {
                clauses[i].is_satisfied = true;
                if (clauses[i].unassigned == 0) {
                    --g_Unit_count;
                    units_satisfied.push_back(i);
                }
                --g_Clause_Count;
                clauses_satisfied.insert(i);
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
                ++g_Unit_count;
            }
            ++count;
        }
        // same
        for (const unsigned & i : comp[-literal]) {
            --clauses[i].unassigned;
            clauses[i].assigned_literals[-literal] = true;
            if (clauses[i].is_satisfied == false) {
                clauses[i].is_satisfied = true;
                if (clauses[i].unassigned == 0) {
                    --g_Unit_count;
                }
                --g_Clause_Count;
                clauses_satisfied.insert(i);
            }
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
            if (++clauses[i].unassigned == 2 && clauses[i].is_satisfied == false) { // before just the == 2
                --g_Unit_count;
            }
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
                --g_Unit_count;
            }
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
        if (literals[i] != 0 && !bools[i]) { // was just !bools[i]
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



