//
// Created by Husam Study on 3/14/2025.
//

#include "Heuristics.h"

unsigned g_rec = 0; // global - # of unresolved clauses
//std::chrono::high_resolution_clock::time_point global_start_time;
//std::chrono::high_resolution_clock::time_point global_end_time;

unsigned g_val(const vector<Clause> & clauses) {
    unsigned ret = 0;
    for (int i = 0; i < clauses.size(); ++i) {
        if (clauses[i].is_satisfied == false) {
            ++ret;
        }
    }
    return ret;
}
unsigned t_val(const vector<Clause> & clauses) {
    unsigned tot = 0;
    for (int x = 0; x < clauses.size(); ++x) {
        if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
            ++tot;
            //cout << "unit clause = " << x << endl;
        }
    }

    return tot;
}

bool total(const vector<Clause> & clauses) {
    int total = 0;
    for (int x = 0; x < clauses.size(); ++x) {
        if (clauses[x].is_satisfied == false && clauses[x].unassigned == 1) {
            ++total;
            //cout << "unit clause = " << x << endl;
        }
    }
    return total == g_Unit_count;
}
int DPLL(vector<Clause> & clauses, vector<int> & solution, const vector<vector<unsigned>> & uncomp, const vector<vector<unsigned>> & comp, bool & sat) {
    int ret = -100;
    //static int recursive = 1;
    //global_end_time = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> duration = global_end_time - global_start_time;
    //cout << "ref time: " << duration.count() << " seconds" << endl;
    ++g_rec;
    //cout << g_rec << endl;
    //static int hey = 0;
    vector<int> units_added_to_solution;
    unordered_set<unsigned> clauses_satisfied; // allow easier undo
    vector<unsigned> while_units_sat;
    vector<unsigned> while_unates_sat;
    int while_unit_count = 0;
    //int total = 0;
    //unsigned og_unit = g_Unit_count;
    unsigned count_added = 0;
    int og = 0;
    unsigned og_w = g_Unit_count;
    vector<int> unates_added_to_solution;


    while ((g_Unit_count != 0) || (!g_Unates.empty())) {
        while(g_Unit_count != 0) {

            if (unit_handle_duplicates(clauses, units_added_to_solution) == -1) {
                // problem .. backtrack .. a * a' = 0

                for (int i = 0; i < count_added; ++i) {
                    undo_update_clauses(clauses, units_added_to_solution[i], uncomp, comp);
                    undo_update_solution(solution, units_added_to_solution[i]);
                }
                undo_update_clauses_satisfied(clauses, clauses_satisfied, og); //while_units_sat);

                g_Unit_count = t_val(clauses);
                --g_rec;
                return -1;
            }

            for (int temp = while_unit_count; temp < units_added_to_solution.size(); ++temp) {//(int val : units_added_to_solution) {
                do_update_solution(solution, units_added_to_solution[temp]); // val instead of u[t]
                if (do_update_clauses(clauses, units_added_to_solution[temp], uncomp, comp, clauses_satisfied, while_units_sat) == -1) { // val instead of u[t]
                    for (int i = 0; i < count_added; ++i) {
                        undo_update_clauses(clauses, units_added_to_solution[i], uncomp, comp);
                        undo_update_solution(solution, units_added_to_solution[i]);
                    }
                    undo_update_solution(solution, units_added_to_solution[temp]);
                    undo_update_clauses_satisfied(clauses, clauses_satisfied, og);//while_units_sat);
                    g_Unit_count = t_val(clauses);
                    --g_rec;
                    return -1;
                }
                og = og + static_cast<int>(g_Unit_count) - static_cast<int>(og_w);
                og_w = g_Unit_count;
                ++count_added;
                ++while_unit_count;
            }
        }
        DLIS_find_unate(solution);


        while ((g_Unit_count == 0) && (!g_Unates.empty())) {
            // same as unit but for unates; break asap when u see there is  a unit that's why == not != for unit count
            // remove from unate
            int val = *g_Unates.begin();
            unates_added_to_solution.push_back(val);
            g_Unates.erase(val);
            do_update_solution(solution, val);
            do_update_clauses(clauses, val, uncomp, comp, clauses_satisfied, while_unates_sat);
            og = og + static_cast<int>(g_Unit_count) - static_cast<int>(og_w);
            og_w = g_Unit_count;
            g_Unit_count = t_val(clauses);
        }

        DLIS_find_unate(solution);
        g_Unit_count = t_val(clauses);
    }



    // check if all clauses are satisfied; if yes -> formula is SAT!
    if (g_Clause_Count == 0) {
        sat = true;
        if (g_val(clauses) == 0) {
            //cout << "yes we're done" << endl;
        }
        else {
            //cout << "nope we're not " << endl;
        }
        --g_rec;
        //cout << "line 118 recursive = " << g_rec << endl;
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

    if (literalChoice == 0) {
        // no more variables without a solution
        //cout << " no literal c hoices !!! " << endl;
        --g_rec;
        //cout << "FFFrecursive = " << g_rec << endl;
        return -1;
    }
    //cout << "AAArecursive = " << g_rec << endl;
    //++g_rec;
    //cout << "BBBrecursive = " << g_rec << endl;
    if (g_rec == 30) {
        //cout << "recursive = 16";
        //exit(1);
    }

    vector<unsigned> dpll_units_sat;

    int og_d = 0;
    unsigned og_d_w = g_Unit_count;
    g_Unit_count = t_val(clauses);

    decision_one:
    // add decision to solution
    do_update_solution(solution, literalChoice);
    // update_function wrt decision
    if (do_update_clauses(clauses, literalChoice, uncomp, comp, clauses_satisfied_dpll, dpll_units_sat) == -1) {
        undo_update_solution(solution, literalChoice);
        goto decision_two;
    }
    og_d = og_d + static_cast<int>(g_Unit_count) - static_cast<int>(og_d_w);
    // call DPLL
    //global_start_time = std::chrono::high_resolution_clock::now();
    if (DPLL(clauses, solution, uncomp, comp, sat) == 0) {
        // sat
        // don't think I need this:
        // sat = true;
        --g_rec;
        //cout << "line 178 recursive = " << g_rec << endl;
        return 0;
    }

    undo_update_clauses(clauses, literalChoice, uncomp, comp);
    undo_update_clauses_satisfied(clauses, clauses_satisfied_dpll, og_d);// dpll_units_sat);
    clauses_satisfied_dpll.clear();
    dpll_units_sat.clear();
    undo_update_solution(solution, literalChoice);

    g_Unit_count = t_val(clauses);

    og_d = 0;
    og_d_w = g_Unit_count;



    decision_two:

    literalChoice *= -1;

    do_update_solution(solution, literalChoice);

    if (do_update_clauses(clauses, literalChoice, uncomp, comp, clauses_satisfied_dpll, dpll_units_sat) == -1) {
        undo_update_solution(solution, literalChoice);
        goto both_fail;
    }
    og_d = og_d + static_cast<int>(g_Unit_count) - static_cast<int>(og_d_w);
    if (DPLL(clauses, solution, uncomp, comp, sat) == 0) {
        // sat
        // don't think I need this:
        // sat = true;
        --g_rec;
        //cout << "line 217 recursive = " << g_rec << endl;
        return 0;
    }

    // for (unsigned x : while_units_sat) {
    //     dpll_units_sat.push_back(x);
    // }

    undo_update_clauses(clauses, literalChoice, uncomp, comp);
    undo_update_clauses_satisfied(clauses, clauses_satisfied_dpll, og_d);// dpll_units_sat);
    //clauses_satisfied_dpll.clear();
    undo_update_solution(solution, literalChoice);
    //cout << literalChoice << endl;


    both_fail:


    for (const int & i : units_added_to_solution) {
        undo_update_clauses(clauses, i, uncomp, comp);
        undo_update_solution(solution, i);
    }
    for (const int & i : unates_added_to_solution) {
        undo_update_clauses(clauses, i, uncomp, comp);
        undo_update_solution(solution, i);
    }
    //undo_update_clauses_satisfied(clauses, clauses_satisfied);
    undo_update_clauses_satisfied(clauses, clauses_satisfied, og);
    --g_rec;
    if (g_rec == 239) {
        //cout << "hi";
    }
    //cout << "CCCrecursive = " << g_rec << endl;
    g_Unit_count = t_val(clauses);

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


/*
 *unordered_set<int> DLIS_find_unate(const vector<int> & curr_sol) {
    unordered_set<int> ret;

    for (int i = 1; i < curr_sol.size(); ++i) {
        // skip if variable is already assigned
        if (curr_sol[i] != 0) continue;

        bool pos_unate = (g_dlis_neg[i] == 0);
        bool neg_unate = (g_dlis_pos[i] == 0);

        // 4 possibilites
        // binate -> skip
        // both 0 -> skip
        // pos unate true, negunate false -> insert i
        // pos unate false, negunate true -> insert -i
        if (pos_unate != neg_unate) {
            ret.insert(pos_unate ? i : -i);
        }
    }
    return ret;
}
*/

void undo_update_clauses_satisfied(vector<Clause> & clauses, const unordered_set<unsigned> & clauses_satisfied, const int & val) { //const vector<unsigned> & units_sat) {
    for (const unsigned & i : clauses_satisfied) {
        clauses[i].is_satisfied = false;

        for (int x : clauses[i].lits) {
            undo_update_DLIS(x);
        }
        /*if (clauses[i].unassigned == 1) {
            ++g_Unit_count;
        }*/
    }
    g_Unit_count -= val; //units_sat.size();
    g_Unit_count = t_val(clauses);
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
                    units_satisfied.push_back(i);
                }
                for (int x : clauses[i].lits) {
                    do_update_DLIS(x);
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
    //cout << "ERROR: UNIT_FIND_FALSE RETURNED -1" << endl;
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


