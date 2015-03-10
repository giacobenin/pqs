#ifndef ADS_RANDOM_GRAPH_GENERATOR_H
#define ADS_RANDOM_GRAPH_GENERATOR_H

#include <stddef.h>

#include "Graph.h"

/**
 * RandomGraphGenerator.h
 *
 *
 * author: Giacomo Benincasa    (giacomo@cise.ufl.edu)
 */

namespace ADS
{
    class RandomGraphGenerator
    {
        public:
            /* If pszFileName is NULL, it reads from stdin */
            RandomGraphGenerator (void);
            virtual ~RandomGraphGenerator (void);

            /* Generates a random graph of uiNVerteces and dDensity density.
               If bConnected is set on true, the generated graph will certainly
               be connected, but the density may actually be higher than the one
               that was specified, if set on false it may be (or it may be not)
               connected.
               If bPreGenerateVerticies is set on true, it adds all the vertices
               before adding the graph (it makes sure that there are all the
               vertices from 0 to uiNVerteces-1 */
            bool generate (Graph<unsigned int> *pGraph, unsigned int uiNVerteces,
                           unsigned int uiDensity, bool bConnected=true,
                           bool bPreGenerateVerticies=true);

        private:
            bool addEdges (Graph<unsigned int> *pGraph, unsigned int uiNVerteces,
                           unsigned int uiNEdges);
    };
}

#endif /* ADS_RANDOM_GRAPH_GENERATOR_H */
