#include <stdio.h>
#include <assert.h>

#include "GraphReader.h"

using namespace ADS;

int main (int argc, char *argv[])
{
    Graph<unsigned int> g;

    switch (argc) {
        case 1:
        {
            GraphReader reader;
            assert (reader.read (&g));
            break;
        }

        case 2:
        {
            GraphReader reader (argv[1]);
            assert (reader.read (&g));
            break;
        }

        default:
            printf ("Usage: %s <graphFile>\n", argv[0]);
            return 1;
    }

    g.display();

    return 0;
}

