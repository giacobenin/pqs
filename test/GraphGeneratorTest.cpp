#include <stdio.h>
#include <assert.h>

#include "GraphUtils.h"
#include "RandomGraphGenerator.h"

using namespace ADS;

int main (int argc, char *argv[])
{
    Graph<unsigned int> g;
    RandomGraphGenerator gen;
    if (gen.generate (&g, 10, 50, true))
        printf ("Graph does not match the requirements\n");

    g.display();

    printf ("Generated %s graph of %u vertices and %u edges (density %f)\n",
            (g.isDirected() ? "directed" : "undirected"),
            g.getVertexCount(), g.getEdgeCount(),
            GraphUtils::getDensity (g.getVertexCount(), g.getEdgeCount(), g.isDirected()));
    
    if (argc > 1) {
        FILE *pFile = fopen ((const char *) argv[1], "w");
        if (pFile != NULL) {
            g.dump (pFile);
        }
    }
    
    return 0;
}
