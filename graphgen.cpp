#include <stdio.h>

#include "GraphUtils.h"
#include "RandomGraphGenerator.h"
#include <iostream>
#include <fstream>
#ifndef WIN
    #include <string.h>
#endif

using namespace ADS;

namespace ADS
{
    struct Options
    {
        Options (void)
            : bVerbose (false), bColomunNames (false),
              density (50.0f), nodes (10),
              pszOutputFile (NULL) {}
        ~Options (void) {}

        bool bVerbose;
        bool bColomunNames;
        float density;
        unsigned int nodes;
        const char *pszOutputFile;
    };

    void help (const char *pszProgramName)
    {
        printf ("Usage:\n-o ,--out outputfile: in addition to printfing the graph on std out, it is also dumped on the specified file\n"
                "-c, --colnames: whether the column names should be displayed. (Not displayed by default)\n"
                "-d, --density: the density of the generated random graph. (Default 0.50).\n"
                "-n, --nodes: the number of nodes in the generated random graph\n"
                "-v, --verbose: it displays info on the generated graph.\n"
                "-h, --help: display this help.\n");
    }

    int parseOptions (int argc, const char *argv[], Options &opts)
    {
        for (int i = 1; i < argc; ++i) {
            if ((strcmp (argv[i], "-o") == 0) || (strcmp (argv[i], "--out") == 0)) {
                if ((++i) < argc)
                    opts.pszOutputFile = argv[i];
                else return -1;
            }
            else if ((strcmp (argv[i], "-c") == 0) || (strcmp (argv[i], "--colnames") == 0)) {
                opts.bColomunNames = true;
            }
            else if ((strcmp (argv[i], "-d") == 0) || (strcmp (argv[i], "--density") == 0)) {
                if ((++i) < argc)
                    opts.density = atof (argv[i]);
                else return -2;
            }
            else if ((strcmp (argv[i], "-n") == 0) || (strcmp (argv[i], "--nodes") == 0)) {
                if ((++i) < argc)
                    opts.nodes = atoi (argv[i]);
                else return -3;
            }
            else if ((strcmp (argv[i], "-v") == 0) || (strcmp (argv[i], "--verbose") == 0)) {
                opts.bVerbose = true;
            }
            else if ((strcmp (argv[i], "-h") == 0) || (strcmp (argv[i], "--help") == 0)) {
                help (argv[0]);
                return 0;
            }
            else {
                return -3;
            }
        }
        return 0;
    }
}

int main (int argc, const char *argv[])
{
    Options opts;
    if (parseOptions (argc, argv, opts) < 0) {
        return -1;
    }

    Graph<unsigned int> g;
    RandomGraphGenerator gen;
    if (!gen.generate (&g, opts.nodes, opts.density, true)) {
        printf ("Graph does not match the requirements\n");
        return -2;
    }

    if (opts.pszOutputFile != NULL) {
        std::ofstream out;
        out.open (opts.pszOutputFile);
        if (out.is_open())
            g.dump (out, opts.bColomunNames);
        out.close();
    }
    else {
        g.dump (std::cout, opts.bColomunNames);
    }

    if (opts.bVerbose) {
        printf ("Generated %s graph of %u vertices and %u edges (density %f)\n",
               (g.isDirected() ? "directed" : "undirected"), g.getVertexCount(), g.getEdgeCount(),
               GraphUtils::getDensity (g.getVertexCount(), g.getEdgeCount(), g.isDirected()));
    }
        
    return 0;
}
