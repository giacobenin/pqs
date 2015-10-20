#include "GraphUtils.h"

#include <math.h>

using namespace ADS;

double GraphUtils::getDensity (unsigned int uiNVertices, unsigned int uiNEdges,
                               bool bDirectedGraph)
{
    return  (static_cast<double>(uiNEdges) /
             static_cast<double>(getMaxNumberOfEdges (uiNVertices, bDirectedGraph)));
}

unsigned int GraphUtils::getMaxNumberOfEdges (unsigned int uiNVertices,
                                              bool bDirectedGraph)
{
    unsigned int uiEdges = uiNVertices * (uiNVertices - 1);
    if (!bDirectedGraph)
        uiEdges = uiEdges / 2;
    return uiEdges;
}

unsigned int GraphUtils::getNumberOfEdges (unsigned int uiNVertices,
                                           unsigned int uiDensity,
                                           bool bDirectedGraph)
{
    if ((uiDensity == 0) || (uiDensity > 100))
        return 0;

    return getNumberOfEdges (uiNVertices, static_cast<double>(uiDensity) / 100.0f,
                             bDirectedGraph);
}

unsigned int GraphUtils::getNumberOfEdges (unsigned int uiNVertices,
                                           double dDensity,
                                           bool bDirectedGraph)
{
    if ((dDensity <= 0.0f) || (dDensity > 1.0f))
        return 0;

    return static_cast<unsigned int>(ceil (dDensity * getMaxNumberOfEdges (uiNVertices, bDirectedGraph)));
}

