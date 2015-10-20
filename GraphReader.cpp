#include "GraphReader.h"

#include "Graph.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace ADS;
using namespace std;

namespace ADS
{
    int parseLine (const string &line, Graph<unsigned int> *pGraph, bool &bFoundEndOfFile)
    {
        unsigned int uiSrc, uiDst, uiCost;
        if (line.length() <= 0 || pGraph == NULL) {
            return -1;
        }
        if (sscanf (line.c_str(), "%d %d %d", &uiSrc, &uiDst, &uiCost) == 3) {
            /* srcVertex dstVertex edgeCost */
            if (!pGraph->addEdge (uiSrc, uiDst, uiCost))
                return -2;
        }
        else if (line.length() == 1 && (strcmp (line.c_str(), "*") == 0)) {
            /* end of input */
            bFoundEndOfFile = true;
            return 0;
        }
        else {
            printf ("Invalid: %s\n", line.c_str());
            return -3;
        }
        return 0;
    }

    int readStream (istream &stream, Graph<unsigned int> *pGraph, bool &bFoundEndOfFile)
    {
        for (std::string line; std::getline (stream, line);)
            if (parseLine (line, pGraph, bFoundEndOfFile) < 0)
                return -1;
        return 0;
    }
}

GraphReader::GraphReader (const char *pszFileName)
    : _fileName (pszFileName)
{
}

GraphReader::~GraphReader (void)
{
}

bool GraphReader::read (Graph<unsigned int> *pGraph)
{
    if (pGraph == NULL)
        return false;

    bool bFoundEndOfFile = false;
    if (_fileName.length() <= 0) {
        readStream (std::cin, pGraph, bFoundEndOfFile);
    }
    else {
        std::ifstream graphFile (_fileName.c_str(), std::ifstream::in);
        readStream (graphFile, pGraph, bFoundEndOfFile);
        graphFile.close();
    }

    return bFoundEndOfFile;
}


