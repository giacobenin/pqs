#include "GraphReader.h"

#include "Graph.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace ADS;

GraphReader::GraphReader (const char *pszFileName)
{
    _pszFileName = pszFileName;
}

GraphReader::~GraphReader (void)
{
}

bool GraphReader::read (Graph<unsigned int> *pGraph)
{
    if (pGraph == NULL)
        return false;

    FILE *pFile = (_pszFileName == NULL ? stdin : fopen (_pszFileName, "r"));
    if (pFile == NULL)
        return false;

    bool bFoundEndOfFile = false;
    char *pszLine = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline (&pszLine, &len, pFile)) != -1) {

        unsigned int uiSrc, uiDst, uiCost;
        char str[1];

        if (sscanf (pszLine, "%d %d %d", &uiSrc, &uiDst, &uiCost) == 3) {
            /* srcVertex dstVertex edgeCost */
            if (!pGraph->addEdge (uiSrc, uiDst, uiCost))
                break;
        }
        else if (sscanf (pszLine, "%s", str) > 0 && (strcmp (str, "*") == 0)) {
            /* end of input */
            bFoundEndOfFile = true;
            break;
        }
        else {
            printf ("Invalid: %s\n", pszLine);
        }
    }

    if (pszLine)
        free (pszLine);

    return bFoundEndOfFile;
}


