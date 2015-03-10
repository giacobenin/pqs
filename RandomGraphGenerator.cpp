#include "RandomGraphGenerator.h"

#include "Defs.h"
#include "GraphUtils.h"

using namespace ADS;

RandomGraphGenerator::RandomGraphGenerator (void)
{
}

RandomGraphGenerator::~RandomGraphGenerator (void)
{
}

bool RandomGraphGenerator::generate (Graph<unsigned int> *pGraph,
                                     unsigned int uiNVerteces,
                                     unsigned int uiDensity, bool bConnected,
                                     bool bPreGenerateVerticies)
{
    if (pGraph == NULL)
        return false;

    if (bPreGenerateVerticies)
        for (unsigned int uiSrc = 0; uiSrc < uiNVerteces; uiSrc++)
            pGraph->addVertex (uiSrc);

    unsigned int uiNEdges = GraphUtils::getNumberOfEdges (uiNVerteces, uiDensity,
                                                          pGraph->isDirected());
    log ("Creating graph of %u edges\n", uiNEdges);

    if (!addEdges (pGraph, uiNVerteces, uiNEdges))
        return false;

    while (bConnected && !pGraph->isConnected())
        /* add edges one-by-one until the graph is connected */
        addEdges (pGraph, uiNVerteces, 1);

    return true;
}

bool RandomGraphGenerator::addEdges (Graph<unsigned int> *pGraph,
                                     unsigned int uiNVerteces,
                                     unsigned int uiNEdges)
{
    if (pGraph == NULL)
        return false;

    while (pGraph->getEdgeCount() < uiNEdges) {
        unsigned int uiSrc = random (uiNVerteces);
        unsigned int uiDst = random (uiNVerteces);
        
        if (uiSrc == uiDst) {
            /* do not add edges to itself */
            continue;
        }

        unsigned int uiCost = random (EDGE_MIN_COST, EDGE_MAX_COST);

        if (!pGraph->hasEdge (uiSrc, uiDst))
            pGraph-> addEdge (uiSrc, uiDst, uiCost);
    }

    return true;
}

