#ifndef ADS_DEFINITIONS_H
#define ADS_DEFINITIONS_H

#include <limits.h>

namespace ADS
{
    typedef unsigned int cost_type;
    typedef unsigned int key_type;

    static cost_type ADS_INFINITY = UINT_MAX;

    static unsigned int EDGE_MIN_COST = 1;
    static unsigned int EDGE_MAX_COST = 1000;

    static bool GRAPH_DIRECTED = true;

    static bool GRAPH_REQUIRES_STRONG_CONNECTIVITY = false;

    static bool GRAPH_ALLOWS_DUPLICATE_EDGES = false;

    static unsigned int NUMBER_OF_RUNS = 5;

    static unsigned int N_VERTECES [] = {1000/*, 200, 300, 500*/};

    /* Percentages */
    static unsigned int GRAPH_DENSITIES [] = {10, 20, 30, 40, 50, 60,
                                              70, 80, 90, 100};
    
}

#endif /* ADS_DEFINITIONS_H */


