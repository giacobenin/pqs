#ifndef ADS_GRAPH_H
#define ADS_GRAPH_H

#include "Comparator.h"
#include "DArray.h"
#include "GraphUtils.h"
#include "LChain.h"
#include <stdio.h>
#include <math.h>
#include <ios>
#include <ostream>

/**
 * Graph.h
 *
 * author: Giacomo Benincasa    (giacomo@cise.ufl.edu)
 */

namespace ADS
{
    template<class T>
    struct Edge
    {
         Edge (unsigned int uiDstKey, T cost);
         ~Edge (void);

         bool operator == (const Edge &other) const;

         unsigned int uiAdjVertext;
         T edgeCost;
    };

    template<class T>
    struct Vertex
    {
        Vertex (unsigned int uiKey);
        ~Vertex (void);

        unsigned int uiVertexKey;

        LChain<Edge<T>*, ObjPointerComparator<Edge<T> > > edges;
    };

    template<class T>
    class Graph
    {
        public:
            /* bDirected is set on true if the graph is directed
             * - If bAllowMultipleEdges is set on true, an edge is added
             *   only if an edge from src to dst does not exist
             */
            Graph (bool bDirected=true, bool bAllowMultipleEdges=false);
            virtual ~Graph (void);

            /* Returns true if the vertex was added, false otherwise */
            bool addVertex (unsigned int uiKey);

            /* If the graph is directed, the method returns true if the edge was
               added, false otherwise.
               If the graph is undirected, the method returns true if all the two
               edges (src -> dst and dst -> src) were added, false otherwise */
            bool addEdge (unsigned int uiSrcKey, unsigned int uiDstKey, T cost);

            /* Removes all the vertices and edges from the graph */
            void empty (void);

            /* Returns the edge density of the graph. The returned value is a
               percentage expressed in decimal notation in the range [0, 1] */
            double getDensity (void);

            /* Returns the edge density of the graph. The returned value is a
               percentage expressed in integer notation in the range [0, 100] */
            unsigned int getDensityAsInt (void);

            /* Returns the total number of edges */
            unsigned int getEdgeCount (void);

            /* Returns the i-th Vertex */
            Vertex<T> * getVertex (unsigned int uiIndex);

            /* Returns the total number of vertices */
            unsigned int getVertexCount (void);

            /* If the graph is not bDirected it returns NULL, otherwise it returns
               the graph's underlying undirected graph */
            Graph * getUndirectedGraph (void);

            /* Returns true if at least one edge from uiSrcKey to uiDstKey
               exists, returns false otherwise */
            bool hasEdge (unsigned int uiSrcKey, unsigned int uiDstKey);

            /* If bStronglyConnected is set on true, the method returns true
               if the graph is strongly connected, false otherwise.
               If bStronglyConnected is set on false, the method returns false
               if the graph is not even weakly connected, true otherwise */
            bool isConnected (bool bStronglyConnected=false);

            bool isDirected (void);

            void dump (std::ostream &out, bool bPrintColumnNames);

        private:
            /* Performs a depth-first traverse of the graph */
            void traverse (Vertex<T> *pVertex, bool *pVisited);

        private:
            bool _bDirected;
            bool _bAllowMultipleEdges;
            unsigned int _uiNVertexes;
            unsigned int _uiNEdges;
            DArray<Vertex<T>* > _vertices;
    };

    template<class T>
    Graph<T>::Graph (bool bDirected, bool bAllowMultipleEdges)
        : _vertices (0, 0, true)
    {
        _bDirected = bDirected;
        _bAllowMultipleEdges = bAllowMultipleEdges;
        _uiNVertexes = 0;
        _uiNEdges = 0;
    }

    template<class T>
    Graph<T>::~Graph()
    {
        empty();
    }

    template<class T>
    bool Graph<T>::addVertex (unsigned int uiKey)
    {
        Vertex<T> *pVertex = _vertices.get (uiKey);
        if (pVertex == NULL) {
            pVertex = new Vertex<T> (uiKey);
            _vertices.add (uiKey, pVertex);
            _uiNVertexes++;
            return true;
        }
        return false;
    }

    template<class T>
    bool Graph<T>::addEdge (unsigned int uiSrcKey, unsigned int uiDstKey, T cost)
    {
        /* Make sure that the source and destination vertices exist */
        addVertex (uiSrcKey);
        addVertex (uiDstKey);

        bool bRet = true;

        Vertex<T> *pVertex = _vertices.get (uiSrcKey);
        if (_bAllowMultipleEdges || !hasEdge (uiSrcKey, uiDstKey)) {
            /* if multiple edges are allowed (therefore it is not necessary
               to check whether the edge is already contained) or if the
               does not yet exist - add it */
            pVertex->edges.prepend (new Edge<T> (uiDstKey, cost));
            _uiNEdges++;
        }
        else
            bRet = false;

        if (!_bDirected) {
            pVertex = _vertices.get (uiDstKey);
            if (_bAllowMultipleEdges || !hasEdge (uiDstKey, uiSrcKey)) {
                /* if multiple edges are allowed (therefore it is not necessary
                   to check whether the edge is already contained) or if the
                   does not yet exist - add it */
                pVertex->edges.prepend (new Edge<T> (uiSrcKey, cost));
                _uiNEdges++;
            }
            else
                bRet = false;
        }

        return bRet;
    }

    template<class T>
    void Graph<T>::empty()
    {
        for (unsigned int i = 0; i < _vertices.size(); i++) {
            Vertex<T> *pVertex = _vertices.remove (i);
            if (pVertex != NULL) {
                for (Edge<T> *pEdge = pVertex->edges.pop(); pEdge != NULL;
                     pEdge = pVertex->edges.pop())
                    delete pEdge;
            }
            delete pVertex;
        }
        _uiNVertexes = 0;
        _uiNEdges = 0;
    }

    template<class T>
    double Graph<T>::getDensity()
    {
        return GraphUtils::getDensity (getVertexCount(), getEdgeCount(),
                                       isDirected());
    }

    template<class T>
    unsigned int Graph<T>::getDensityAsInt()
    {
        return static_cast<int>(floor ((getDensity() * 100.0) + 0.5));
    }

    template<class T>
    unsigned int Graph<T>::getEdgeCount()
    {
        return _uiNEdges;
    }

    template<class T>
    Vertex<T> * Graph<T>::getVertex (unsigned int uiIndex)
    {
        return _vertices.get (uiIndex);
    }

    template<class T>
    unsigned int Graph<T>::getVertexCount()
    {
        return _uiNVertexes;
    }

    template<class T>
    Graph<T> * Graph<T>::getUndirectedGraph()
    {
        if (!isDirected())
            return NULL;

        /* temporarely set pUndirectedGraph->_bDirected to true in order to
           avoid pUndirectedGraph->addEdge() to add the dst -> src edge */
        Graph<T> *pUndirectedGraph = new Graph<T> (true, _bAllowMultipleEdges);
        for (unsigned int uiSrc = 0; uiSrc < _vertices.size(); uiSrc++) {
            Vertex<T> *pVertex = _vertices.get (uiSrc);
            if (pVertex != NULL) {
                for (Edge<T> *pEdge = pVertex->edges.getFirst (true);
                     pEdge != NULL;
                     pEdge = pVertex->edges.getNext()) {

                    unsigned int uiDst = pEdge->uiAdjVertext;
                    if (!pUndirectedGraph->hasEdge (uiSrc, uiDst)) {
                        pUndirectedGraph->addEdge (uiSrc, uiDst, pEdge->edgeCost);
                    }
                    if (!hasEdge (uiDst, uiSrc) &&
                        !pUndirectedGraph->hasEdge (uiDst, uiSrc)) {
                        pUndirectedGraph->addEdge (uiDst, uiSrc, pEdge->edgeCost);
                    }
                }
            }
        }

        pUndirectedGraph->_bDirected = false;
        return pUndirectedGraph;
    }

    template<class T>
    bool Graph<T>::hasEdge (unsigned int uiSrcKey, unsigned int uiDstKey)
    {
        Vertex<T> *pVertex = _vertices.get (uiSrcKey);
        if (pVertex == NULL)
            return false;

        for (Edge<T> *pEdge = pVertex->edges.getFirst (true);
             pEdge != NULL;
             pEdge = pVertex->edges.getNext())
            if (pEdge->uiAdjVertext == uiDstKey)
                return true;

        return false;
    }

    template<class T>
    bool Graph<T>::isConnected (bool bStronglyConnected)
    {
        if (!bStronglyConnected && isDirected()) {
            /* Get the underlying undirected graph and checks if
               that is connected */
            Graph *pGraph = getUndirectedGraph();
            bool bRet = pGraph->isConnected (bStronglyConnected);
            delete pGraph;
            return bRet;
        }

        /* Allocated array initializes all the elements to 0x0 */
        bool *pVisited = (bool *) allocateArray (_uiNVertexes, sizeof (bool));

        /* For each vertex */
        Vertex<T> *pVertex = NULL;
        unsigned int uiVertexKey = 0;
        for (; uiVertexKey < _vertices.size(); uiVertexKey++) {
            if ((pVertex = _vertices.get (uiVertexKey)) != NULL) {
                pVisited[uiVertexKey] = true;
                traverse (pVertex, pVisited);

                /* Checks whether all the vertices were visited */
                for (unsigned int i = 0; i < _uiNVertexes; i++)
                    if ((_vertices.get (i) != NULL) && !pVisited[i]) {
                        /* the vertex of key "i" exists and it was not visited */
                        deallocate ((void**)&pVisited);
                        return false;
                    }
            }
            if (!isDirected())
                /* if the graph is undirected, having 1 connected node is
                   a sufficient condition for the graph to be strongly connected
                   (and therefore not to be weakly connected as well */
                break;
            /* Reset array of visited nodes */
            setArray ((int)false, pVisited, _uiNVertexes, sizeof (bool));
        }

        deallocate ((void**)&pVisited);
        return true;
    }

    template<class T>
    bool Graph<T>::isDirected()
    {
        return _bDirected;
    }

    template<class T>
    void Graph<T>::traverse (Vertex<T> *pVertex, bool *pVisited)
    {
        if (pVertex == NULL)
            return;

        for (Edge<T> *pEdge = pVertex->edges.getFirst (true); pEdge != NULL;
             pEdge = pVertex->edges.getNext())
            if ((pEdge != NULL) && !pVisited[pEdge->uiAdjVertext]) {
                /* check whether pEdge->uiAdjVertexthas already been visited
                   to avoid loops */
                pVisited[pEdge->uiAdjVertext] = true;
                traverse (_vertices.get (pEdge->uiAdjVertext), pVisited);
            }
    }

    template<class T>
    void Graph<T>::dump (std::ostream &out, bool bPrintColumnNames)
    {
        if (bPrintColumnNames) {
            printf ("[vertex]\tuiAdjVertex (cost)\tuiAdjVertex (cost) ...\n");
        }
        for (unsigned int i = 0; i < _vertices.size (); i++) {
            Vertex<T> *pVertex = _vertices.get (i);
            if (pVertex != NULL) {
                for (Edge<T> *pEdge = pVertex->edges.getFirst (true);
                    pEdge != NULL; pEdge = pVertex->edges.getNext()) {
                    out << pVertex->uiVertexKey << ' ' << pEdge->uiAdjVertext << ' ' << pEdge->edgeCost << std::endl;
                }
            }
        }
    }

    template<class T>
    Edge<T>::Edge (unsigned int uiDstKey, T cost)
    {
        uiAdjVertext = uiDstKey;
        edgeCost = cost;
    }

    template<class T>
    Edge<T>::~Edge()
    {
    }

    template<class T>
    bool Edge<T>::operator==(const Edge<T> &other) const
    {
        return (uiAdjVertext == other.uiAdjVertext);
    }

    template<class T>
    Vertex<T>::Vertex (unsigned int uiKey)
    {
        uiVertexKey = uiKey;
    }

    template<class T>
    Vertex<T>::~Vertex()
    {
    }
}

#endif /* ADS_GRAPH_H */


