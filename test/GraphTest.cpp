#include <stdio.h>
#include <assert.h>

#include "Algorithms.h"
#include "Graph.h"
#include "GraphReader.h"

using namespace ADS;

int main (int argc, char *argv[])
{
    const char *pszWeakelyConnGraph = "../test/weakely_connected_graph.gr";
    const char *pszStronglyConnGraph = "../test/connected_graph.gr";

    GraphReader wreader (pszWeakelyConnGraph);
    Graph<unsigned int> *pGraph = new Graph<unsigned int> (true,  /* directed */
                                                           false);/* allows multiple edges */

    /* Test Weakly Connected Graph */
    assert (wreader.read (pGraph));
    pGraph->display();
    assert (pGraph->isDirected());
    assert (pGraph->getEdgeCount() == 4);
    assert (pGraph->getVertexCount() == 4);
    assert (false == pGraph->isConnected (true /* bStronglyConnected */));
    Graph<unsigned int> *pUndirected = pGraph->getUndirectedGraph();
    assert (pUndirected != NULL);
    pUndirected->display();
    delete pUndirected;
    assert (true == pGraph->isConnected (false /* bStronglyConnected */));

    PQueue *pQueue = new SimplePQ();
    unsigned int *pDistances = Algorithms<unsigned int>::dijskstra (pGraph, 0, pQueue);
    assert (pDistances != NULL);
    printf ("*** dijskstra ***\n");
    for (unsigned int i = 0; i < pGraph->getVertexCount(); i++)
        printf ("[%d] cost: %d\n", i, pDistances[i]); 
    printf ("*** ********* ***\n");

    deallocate ((void**)&pDistances);

    pGraph->empty();
    assert (pGraph->getEdgeCount() == 0);
    assert (pGraph->getVertexCount() == 0);

    /* Test Strongly Connected Graph */

    GraphReader sreader (pszStronglyConnGraph);
    assert (sreader.read (pGraph));
    pGraph->display();
    assert (pGraph->isDirected());
    assert (pGraph->getEdgeCount() == 7);
    assert (pGraph->getVertexCount() == 4);
    assert (true == pGraph->isConnected (true /* bStronglyConnected */));
    pUndirected = pGraph->getUndirectedGraph();
    assert (pUndirected != NULL);
    pUndirected->display();
    delete pUndirected;
    assert (true == pGraph->isConnected (false /* bStronglyConnected */));

    pQueue = new SimplePQ();
    pDistances = Algorithms<unsigned int>::dijskstra (pGraph, 2, pQueue);
    assert (pDistances != NULL);
    printf ("*** dijskstra ***\n");
    for (unsigned int i = 0; i < pGraph->getVertexCount(); i++)
        printf ("[%d] cost: %d\n", i, pDistances[i]); 
    printf ("*** ********* ***\n");

    delete pGraph;

    return 0;
}

