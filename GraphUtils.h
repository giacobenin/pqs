#ifndef ADS_GRAPH_UTILS_H
#define ADS_GRAPH_UTILS_H

/**
 * GraphUtils.h
 *
 * Collection of a few Network Theory Functions.
 *
 * author: Giacomo Benincasa    (giacomo@cise.ufl.edu)
 */

namespace ADS
{
    class GraphUtils
    {
        public:
            /* Returns the density of the graph of uiNVertices vertices and
               uiNEdges edges */
            static double getDensity (unsigned int uiNVertices,
                                      unsigned int uiNEdges, bool bDirectedGraph);

            /* Returns the maximus number of edges that a graph of uiNVertexces
               can have */
            static unsigned int getMaxNumberOfEdges (unsigned int uiNVertices,
                                                     bool bDirectedGraph);

            /* Returns the number of edges that a graph of uiNVertexces
               must contain in order to have a density of dDensity
               - uiDensity is a percentage, it must be within [0, 100] */
            static unsigned int getNumberOfEdges (unsigned int uiNVertices,
                                                  unsigned int uiDensity,
                                                  bool bDirectedGraph);

            /* Returns the number of edges that a graph of uiNVertexces
               must contain in order to have a density of dDensity
               - dDensity is a percentage, it must be within [0.0, 1.0] */
            static unsigned int getNumberOfEdges (unsigned int uiNVertices,
                                                  double dDensity,
                                                  bool bDirectedGraph);
    };
}

#endif /* ADS_GRAPH_UTILS_H */


