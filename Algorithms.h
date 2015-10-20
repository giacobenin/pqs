#ifndef ADS_ALGORITHMS_H
#define ADS_ALGORITHMS_H

#include "Graph.h"
#include "PQueue.h"
#include "Utils.h"

namespace ADS
{
    template<class T>
    class Algorithms
    {
        public:
            /* Returns an array containing the minimum cost of the path from every node
               to any other node of the graph */
            static T ** dijskstra (Graph<T> *pGraph, PQueue *pQueue);

            /* Returns an array containing the minimum cost of the path from uiSrc to any
               other node of the graph */
            static T * dijskstra (Graph<T> *pGraph, unsigned int uiSrc, PQueue *pQueue);
    };

    template<class T>
    T ** Algorithms<T>::dijskstra (Graph<T> *pGraph, PQueue *pQueue)
    {
        T **ppDistances = static_cast<T**>(allocateArray (pGraph->getVertexCount(), sizeof (T *)));
        for (unsigned int i = 0; i < pGraph->getVertexCount(); i++)
            ppDistances[i] = dijskstra (pGraph, i, pQueue);
        return ppDistances;
    }
    
    template<class T>
    T * Algorithms<T>::dijskstra (Graph<T> *pGraph, unsigned int uiSrc, PQueue *pQueue)
    {
        if ((pGraph == NULL) || (pQueue == NULL))
            return NULL;

        /* Allocate memory for required data structures */
        Node<NodeDistancePairClass*> **pNodeDistancePairs = (Node<NodeDistancePairClass*> **)
            allocateArray (pGraph->getVertexCount(), sizeof (NodeDistancePairClass*));

        if (pNodeDistancePairs == NULL)
            /* out of memory */
            return NULL;

        bool *pVisited = (bool *) allocateArray (pGraph->getVertexCount(),
                                                 sizeof (bool));
        if (pVisited == NULL) {
            /* out of memory */
            deallocateObjPtrArray<Node<NodeDistancePairClass*> > (&pNodeDistancePairs, pGraph->getVertexCount());
            return NULL;
        }

        T *pDistances = (T*) allocateArray (pGraph->getVertexCount(), sizeof (T*)); /* contains only the distances
                                                                                       to the source */

        /* Initialize required data structures */
        pNodeDistancePairs[uiSrc] = pQueue->add (new NodeDistancePairClass (uiSrc, 0));
        for (unsigned int i = 0; i < pGraph->getVertexCount(); i++) {
            pVisited[i]  = false;
            pDistances[i] = ADS_INFINITY;
        }

        
        for (NodeDistancePairClass *pNode = pQueue->pop() ;
             (pNode != NULL) && (pNode->_cost < ADS_INFINITY);
             pNode = pQueue->pop()) {

            key_type key = pNode->_key;
            pDistances[key] = pNode->_cost;
            pVisited[key] = true;
            delete pNode;
            pNodeDistancePairs[key] = NULL;     /* pop() deallocated the node */

            /* For each neighbor of pNode */
            Vertex<T> *pVertex = pGraph->getVertex (key);
            if (pVertex != NULL) {
                for (Edge<T> *pEdge = pVertex->edges.getFirst (true);
                     pEdge != NULL; pEdge = pVertex->edges.getNext()) {

                    if (!pVisited[pEdge->uiAdjVertext]) {
                        T cost = pEdge->edgeCost;
                        if (cost == ADS_INFINITY)
                            /* being pQueue ordered by cost, if pQueue's cost the next elements
                               costs are INFINITY as well */
                        break;

                        cost += pDistances[key];                        

                        if (pNodeDistancePairs[pEdge->uiAdjVertext] == NULL)
                            pNodeDistancePairs[pEdge->uiAdjVertext] = pQueue->add (new NodeDistancePairClass (pEdge->uiAdjVertext, cost));

                        if (cost < pNodeDistancePairs[pEdge->uiAdjVertext]->el->_cost) {

                            NodeDistancePairClass *pNodeDistancePairClass =
                                new NodeDistancePairClass (pEdge->uiAdjVertext, cost);
                            pNodeDistancePairClass = pQueue->decreaseKey (pNodeDistancePairs[pEdge->uiAdjVertext],
                                                                          pNodeDistancePairClass);
                            delete pNodeDistancePairClass;
                        }
                    }
                }
            }
        }

        for (unsigned int i = 0; i < pGraph->getVertexCount(); i++)
            delete pNodeDistancePairs[i];
        free (pNodeDistancePairs);

        deallocate ((void **)&pVisited);

        //deallocate (&pNodeDistancePairs);
        
        return pDistances;
    }
}

#endif /* ADS_ALGORITHMS_H */


