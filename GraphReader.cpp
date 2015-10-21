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
        if (pGraph == NULL) {
            return -1;
        }
        if (line.length() <= 0) {
            return 0;
        }
        unsigned int uiSrc, uiDst, uiCost;
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

    int readStream (istream &stream, Graph<unsigned int> *pGraph)
    {
        bool bFoundEndOfFile = false;
        for (std::string line; std::getline (stream, line) && (!bFoundEndOfFile);) {
            if (stream.fail())
                break;
            if (parseLine (line, pGraph, bFoundEndOfFile) < 0)
                return -1;
        }
        return 0;
    }
}

GraphReader::GraphReader (const char *pszFileName)
    : _fileName (pszFileName == NULL ? "" : pszFileName)
{
}

GraphReader::~GraphReader (void)
{
}

bool GraphReader::read (Graph<unsigned int> *pGraph)
{
    if (pGraph == NULL)
        return false;

    int rc = 0;
    if (_fileName.length() <= 0) {
        rc = readStream (std::cin, pGraph);
    }
    else {
        std::ifstream graphFile (_fileName.c_str(), std::ifstream::in);
        rc = readStream (graphFile, pGraph);
        graphFile.close();
    }

    return (rc == 0);
}


