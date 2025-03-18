//
// Created by Husam Study on 3/14/2025.
//

#include "Heuristics.h"



int DPLL(unordered_map<unsigned, vector<Clause>> map, vector<int> & solution, const unsigned & max, int curr_max, bool & done, bool & sat, unsigned num_clauses) {

    if (num_clauses == 0) {
        done = sat = true;
        return 0;
    }
    while (!map.at(1).empty()) {
        // deal with unit clauses
    }
    if (num_clauses == 0) {
        done = sat = true;

        return 0;
    }

    // Choose next variable/literal to branch on
    // Add to sol
    // Branch
    // Success:

    // Fail:
    // Choose next variable/literal to branch on
    // Add to sol
    // Branch
    // Success:

    // Fail:




    // int retVal = 0;
    //
    // if (num_clauses == 0) {
    //     done = sat = true;
    //     return 0;
    // }
    // if (curr_max == 1) {
    //     retVal = unit_handle_duplicates(map);
    //     if (retVal == -1) {
    //         sat = false;
    //         return -1;
    //     }
    //     else {
    //         retVal = unit_add_solution(map, solution, curr_max);
    //         sat = true;
    //         return 0;
    //     }
    //     done = true;
    // }
    //
    // while(map.at(1).size() != 0) {
    //     retVal = unit_handle_duplicates(map);
    //     if (retVal == -1) {
    //         return -1;
    //     }
    //     else if (retVal == 1) {
    //         retVal = unit_add_solution(map, solution, curr_max);
    //         retVal = updat
    //     }
    // }
    //
    // retVal = unit_add_solution(map, solution, curr_max);



    return 0;
}



int unit(unordered_map<unsigned, vector<Clause>> map_clauses) {
    int ret = unit_handle_duplicates(map_clauses);
    if (ret == 0) { // no duplicates found.
        return 0;
    }
    // duplicate(s) found!
    for (const auto& val : map_clauses.at(0)) {
        unit_prune_nonunit_clauses(map_clauses, val, )
    }

    return 0;
}


int unit_handle_duplicates(unordered_map<unsigned, vector<Clause>> map_clauses) {

    return 0;
}


int unit_prune_nonunit_clauses(unordered_map<unsigned, vector<Clause>> map_clauses, int literal, size_t clause_size) {

    return  0;
}


int unit_prune_handle_duplicates(unordered_map<unsigned, vector<Clause>> map_clauses, int literal) {

    return 0;
}

int unit_add_solution(unordered_map<unsigned, vector<Clause>> map, vector<int> & solution, const int & curr_max) {

    return 0;
}