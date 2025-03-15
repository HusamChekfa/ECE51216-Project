// Clause.h
#ifndef CLAUSE_H
#define CLAUSE_H

#include <vector>

struct Clause {
    std::vector<int> literals;
    unsigned int unassigned = 0; // count of unassigned variables
};

#endif // CLAUSE_H
