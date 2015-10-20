#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "DArray.h"

#include "Algorithms.h"
#include "Defs.h"
#include "Graph.h"
#include "GraphReader.h"
#include "MovingMean.h"
#include "RandomGraphGenerator.h"
#include "StopWatch.h"

using namespace ADS;

namespace ADS
{
    enum Mode {
        SIMPLE = 0x00,
        FIBONACCI_HEAP = 0x01,
        BINOMIAL_HEAP = 0x02,
        RANDOM = 0x03,

        UNSUPPORTED = 0x04
    };

    const char * PERFORMANCE_MATRIX_COLUMNS[] = { "Number of vertices", "Density",
        "Simple scheme(msec)",
        "F-heap scheme (msec)", "B-heap scheme(msec)" };

    void displayPerformanceMatrixColumnNames (void)
    {
        for (unsigned int i = 0; i < 5; i++)
            printf ("%s\t", PERFORMANCE_MATRIX_COLUMNS[i]);
        printf ("\n");
    }

    void displayPerformanceMatrix (unsigned int uiNVerteces, unsigned int uiDensity,
        double *pMeanTimeInMSec)
    {
        /* print one row of the performance matrix */
        printf ("%u\t\t\t%u%%\t\t\t%f\t\t\t%f\t\t\t%f\n",
            uiNVerteces, uiDensity, pMeanTimeInMSec[SIMPLE],
            pMeanTimeInMSec[FIBONACCI_HEAP], pMeanTimeInMSec[BINOMIAL_HEAP]);
    }

    void displayDistanceMatrix (cost_type **pDistances, unsigned int uiNNodes)
    {
        /* printf distance matrix columns names */
        printf ("Node");
        for (unsigned int i = 0; i < uiNNodes; i++)
            printf ("\t\t%u", i);
        printf ("\n");

        for (unsigned int i = 0; i < uiNNodes; i++) {
            /* print distance matrix row name */
            printf ("%u", i);
            for (unsigned int j = 0; j < uiNNodes; j++)
                if ((i == j) || (pDistances[i][j] == ADS_INFINITY))
                    printf ("\t\t?");
                else
                    printf ("\t\t%u", pDistances[i][j]);

            printf ("\n");
        }
    }

    Graph<unsigned int> * getGraph (Mode mode, const char *pszFile)
    {
        Graph<unsigned int> *pGraph =
            new Graph<unsigned int> (GRAPH_DIRECTED, GRAPH_ALLOWS_DUPLICATE_EDGES);

        switch (mode) {
            case SIMPLE:
            case BINOMIAL_HEAP:
            case FIBONACCI_HEAP:
            {
                GraphReader reader (pszFile);
                if (reader.read (pGraph))
                    break;
            }

            default:
                return NULL;
        }

        return pGraph;
    }

    Graph<unsigned int> * getRandomGraph (Mode mode, unsigned int uiNVerteces, unsigned int uiDensity)
    {
        Graph<unsigned int> *pGraph =
            new Graph<unsigned int> (GRAPH_DIRECTED, GRAPH_ALLOWS_DUPLICATE_EDGES);

        switch (mode) {
            case RANDOM:
            {
                RandomGraphGenerator graphGen;
                graphGen.generate (pGraph, uiNVerteces, uiDensity, true);
                break;
            }
            default:
                return NULL;
        }

        return pGraph;
    }

    Mode parseMode (const char *pszMode)
    {
        if (NULL == pszMode || 0 == strlen (pszMode))
            return UNSUPPORTED;

        if (0 == strcmp ("-r", pszMode))
            return RANDOM;
        if (0 == strcmp ("-is", pszMode))
            return SIMPLE;
        if (0 == strcmp ("-if", pszMode))
            return FIBONACCI_HEAP;
        if (0 == strcmp ("-ib", pszMode))
            return BINOMIAL_HEAP;

        return UNSUPPORTED;
    }

    void printUsageAndExit (const char *pszProgram)
    {
        printf ("Usage:\n%s -r\n%s -is <file>\n%s -ib <file>\n%s -if <file>\n",
            pszProgram, pszProgram, pszProgram, pszProgram);
        exit (1);
    }
}
int main (int argc, char *argv[])
{
    if (argc > 3)
        printUsageAndExit (argv[0]);

    Mode mode = UNSUPPORTED;
    const char *pszFile = NULL;
    for (int i = 1; i < argc; i++) {
        switch (i) {
            case 1:
                mode = parseMode (argv[1]);
                break;

            case 2:
                pszFile = argv[2];
                break;
        }
    }

    if ((mode == UNSUPPORTED) ||
        ((mode == RANDOM) && (pszFile != NULL)))
        printUsageAndExit (argv[0]);

    Graph<unsigned int> *pGraph = NULL;
    switch (mode) {
        case SIMPLE:
        {
            pGraph = getGraph (mode, pszFile);
            SimplePQ *pQueue = new SimplePQ();
            cost_type **pDistances = Algorithms<cost_type>::dijskstra (pGraph, pQueue);
            displayDistanceMatrix (pDistances, pGraph->getVertexCount());
            delete pGraph;
            break;
        }

        case BINOMIAL_HEAP:
        {
            pGraph = getGraph (mode, pszFile);
            BHeapPQ *pQueue = new BHeapPQ();
            cost_type **pDistances = Algorithms<cost_type>::dijskstra (pGraph, pQueue);
            displayDistanceMatrix (pDistances, pGraph->getVertexCount());
            delete pGraph;
            break;
        }
        case FIBONACCI_HEAP:
        {
            pGraph = getGraph (mode, pszFile);
            FHeapPQ *pQueue = new FHeapPQ();
            cost_type **pDistances = Algorithms<cost_type>::dijskstra (pGraph, pQueue);
            displayDistanceMatrix (pDistances, pGraph->getVertexCount());
            delete pGraph;
            break;
        }

        case RANDOM:
        {
            displayPerformanceMatrixColumnNames();

            const unsigned int verticesLen = sizeof (N_VERTECES)/ sizeof (unsigned int);
            const unsigned int densitiesLen = sizeof (GRAPH_DENSITIES)/ sizeof (unsigned int);

            MovingMean<long long int> mean;
            StopWatch sw;
            double performances[3];
            for (unsigned int i = 0; i < 3; i++)
                performances[i] = -1.0f;

            for (unsigned int v = 0; v < verticesLen; v++) {
                for (unsigned int d = 0; d < densitiesLen; d++) {
                    /* Generate a graph with N_VERTECES[v] vertices and density
                       GRAPH_DENSITIES[d] */
                    log ("Generating graph of %u vertices with edge density %u...",
                         N_VERTECES[v], GRAPH_DENSITIES[d]);
                    pGraph = getRandomGraph (mode, N_VERTECES[v], GRAPH_DENSITIES[d]);
                    log ("Graph generated\n");
                    /* For each of the data structures to use*/
                    for (unsigned int queue = 0; queue < 3; queue++) {
                        mean.reset();
                        /* Run Dijskstra's algorithm NUMBER_OF_RUNS times */
                        for (unsigned int r = 0; r < NUMBER_OF_RUNS; r++) {
                            PQueue *pQueue = NULL;
                            switch (queue) {
                                case SIMPLE:
                                {
                                    pQueue = new SimplePQ();
                                    break;
                                }

                                case FIBONACCI_HEAP:
                                {
                                    pQueue = new FHeapPQ();
                                    break;
                                }

                                case BINOMIAL_HEAP:
                                {
                                    pQueue = new BHeapPQ();
                                    break;
                                }
                            }
                            if (pQueue == NULL)
                                printf ("Weirdness happend\n");

                            /* start timer and execute Dijskstra's algorithm */
                            sw.startWatch();
                            cost_type **pDistances = Algorithms<cost_type>::dijskstra (pGraph, pQueue);
                            mean.add (sw.stopWatch());

                            /* deallocate data structures */
                            for (unsigned int i = 0; i < pGraph->getVertexCount(); i++)
                                free (pDistances[i]);
                            free (pDistances);

                            /* just in case there were nodes that were not connected,
                               it should not be the case, but better safe then sorry... */
                            emptyQueue (pQueue);
                            delete pQueue;
                        }
                        /* Record the average of the performance for the scheme*/
                        performances[queue] = mean.getMean();
                    }
                    /* Output the performances of the 3 schemes for the given number
                       of vertices and density */
                    displayPerformanceMatrix (pGraph->getVertexCount(),
                                              pGraph->getDensityAsInt(),
                                              performances);

                    for (unsigned int i = 0; i < 3; i++)
                        performances[i] = -1.0f;
                    delete pGraph;
                }
            }
            break;
        }

        case UNSUPPORTED:
        default:
            printUsageAndExit (argv[0]);
    }
}


