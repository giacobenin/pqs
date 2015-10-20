#ifndef ADS_VERTEX_PRIORITY_QUEUES_H
#define ADS_VERTEX_PRIORITY_QUEUES_H

#include "BHeap.h"
#include "Comparator.h"
#include "Defs.h"
#include "FHeap.h"
#include "LChain.h"

/**
 * PQueue.h
 *
 * Generic interface for a priority queue of vertexes
 * and its implementations.
 *
 * author: Giacomo Benincasa    (giacomo@cise.ufl.edu)
 */

namespace ADS
{
    template<class KEY_TYPE, class COST_TYPE>
    struct NodeDistancePair
    {
        NodeDistancePair (KEY_TYPE key, COST_TYPE cost);
        virtual ~NodeDistancePair (void);

        /* Returns true if the two objects have the same _key */
        bool operator == (const NodeDistancePair &other) const;

        /* Returns true if the object has higher cost of "other" */
        bool operator > (const NodeDistancePair &other) const;

        /* Returns true if the object has lower cost of "other" */
        bool operator < (const NodeDistancePair &other) const;

        KEY_TYPE _key;
        COST_TYPE _cost;
    };

    class NodeDistancePairClass : public NodeDistancePair<key_type, cost_type>
    {
        public:
            NodeDistancePairClass (key_type key, cost_type cost);
            virtual ~NodeDistancePairClass (void);

            void display (void);
    };

    class NDPObjPointerComparator : public ObjPointerComparator<NodeDistancePairClass>
    {
        public:
            NDPObjPointerComparator (void);
            virtual ~NDPObjPointerComparator (void);
    };

    class PQueue
    {
        public:
            PQueue (void);
            virtual ~PQueue (void);

            /* Adds an element into the priority queue */
            virtual Node<NodeDistancePairClass*> * add (NodeDistancePairClass *pNode) = 0;

            /* Returns true if the priority queue is empty */
            virtual bool isEmpty (void) = 0;

            /* Returns the head of the priority queue.
               Returns NULL if the priority queue is empty.*/
            virtual NodeDistancePairClass * peek (void) = 0;

            /* Returns and remove the head of the priority queue.
               Returns NULL if the priority queue is empty. */
            virtual NodeDistancePairClass * pop (void) = 0;

            virtual NodeDistancePairClass * decreaseKey (Node<NodeDistancePairClass*> *pNode,
                                                         NodeDistancePairClass *pNewElement) = 0;

            virtual void display (void) = 0;
    };

    /*
     * Implementation of the priority queue using a binomial heap
     */
    class SimplePQ : public PQueue, LChain<NodeDistancePairClass*, NDPObjPointerComparator>
    {
        public:
            SimplePQ (bool bIsMinHeap=true);
            virtual ~SimplePQ (void);

            Node<NodeDistancePairClass*> * add (NodeDistancePairClass *pNode);
            bool isEmpty (void);
            NodeDistancePairClass * peek (void);
            NodeDistancePairClass * pop (void);
            NodeDistancePairClass * decreaseKey (Node<NodeDistancePairClass*> *pNode,
                                                 NodeDistancePairClass *pNewElement);

            void display (void);
    };

    /*
     * Implementation of the priority queue using a binomial heap
     */
    class BHeapPQ : public PQueue, BHeap<NodeDistancePairClass*, NDPObjPointerComparator>
    {
        public:
            BHeapPQ (bool bIsMinHeap=true);
            virtual ~BHeapPQ (void);

            Node<NodeDistancePairClass*> * add (NodeDistancePairClass *pNode);
            bool isEmpty (void);
            NodeDistancePairClass * peek (void);
            NodeDistancePairClass * pop (void);
            NodeDistancePairClass * decreaseKey (Node<NodeDistancePairClass*> *pNode,
                                                 NodeDistancePairClass *pNewElement);

            void display (void);
    };

    /*
     * Implementation of the priority queue using a Fibonacci heap
     */
    class FHeapPQ : public PQueue, FHeap<NodeDistancePairClass*, NDPObjPointerComparator>
    {
        public:
            FHeapPQ (bool bIsMinHeap=true);
            virtual ~FHeapPQ (void);

            Node<NodeDistancePairClass*> * add (NodeDistancePairClass *pNode);
            bool isEmpty (void);
            NodeDistancePairClass * peek (void);
            NodeDistancePairClass * pop (void);
            NodeDistancePairClass * decreaseKey (Node<NodeDistancePairClass*> *pNode, NodeDistancePairClass *pNewElement);

            void display (void);
    };

    template<class KEY_TYPE, class COST_TYPE>
    NodeDistancePair<KEY_TYPE, COST_TYPE>::NodeDistancePair (KEY_TYPE key, COST_TYPE cost)
    {
        _key = key;
        _cost = cost;
    }

    template<class KEY_TYPE, class COST_TYPE>
    NodeDistancePair<KEY_TYPE, COST_TYPE>::~NodeDistancePair()
    {
    }

    template<class KEY_TYPE, class COST_TYPE>
    bool NodeDistancePair<KEY_TYPE, COST_TYPE>::operator == (const NodeDistancePair &other) const
    {
        return _key == other._key;
    }

    template<class KEY_TYPE, class COST_TYPE>
    bool NodeDistancePair<KEY_TYPE, COST_TYPE>::operator > (const NodeDistancePair &other) const
    {
        return _cost > other._cost;
    }

    template<class KEY_TYPE, class COST_TYPE>
    bool NodeDistancePair<KEY_TYPE, COST_TYPE>::operator < (const NodeDistancePair &other) const
    {
        return _cost < other._cost;
    }
}

#endif /* ADS_VERTEX_PRIORITY_QUEUES_H */
