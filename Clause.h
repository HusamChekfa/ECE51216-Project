// Clause.h
#ifndef CLAUSE_H
#define CLAUSE_H

#include <vector>

struct Clause {
    std::vector<int> literals;
    unsigned int unassigned = 0; // count of unassigned variables // might not be useful if we go for the map BCP
};

#endif // CLAUSE_H
