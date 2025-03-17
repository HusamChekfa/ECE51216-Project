//
// Created by Husam Study on 3/14/2025.
//

#include "Heuristics.h"



int unit(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses) {
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


int unit_handle_duplicates(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses) {

    return 0;
}


int unit_prune_nonunit_clauses(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses, int literal, size_t clause_size) {

    return  0;
}


int unit_prune_handle_duplicates(std::unordered_map<unsigned int, std::vector<Clause>> map_clauses, int literal) {

    return 0;
}
