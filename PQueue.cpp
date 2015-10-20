#include "PQueue.h"

using namespace ADS;

NodeDistancePairClass::NodeDistancePairClass (key_type key, cost_type cost)
    : NodeDistancePair<key_type, cost_type> (key, cost)
{
}

NodeDistancePairClass::~NodeDistancePairClass()
{
}

void NodeDistancePairClass::display()
{
    printf ("key: %u\tcost: %u\n", _key, _cost);
}

/*****************************************************************************/

NDPObjPointerComparator::NDPObjPointerComparator()
{
}

NDPObjPointerComparator::~NDPObjPointerComparator()
{
}

/*****************************************************************************/

PQueue::PQueue()
{
}

PQueue::~PQueue()
{
}

/*****************************************************************************/

SimplePQ::SimplePQ (bool bIsMinHeap)
    : LChain<NodeDistancePairClass*, NDPObjPointerComparator> (false,  // the list is not sorted!
                                                               bIsMinHeap)
{
}

SimplePQ::~SimplePQ()
{
}

Node<NodeDistancePairClass*> * SimplePQ::add (NodeDistancePairClass *pElement)
{
    return LChain<NodeDistancePairClass*, NDPObjPointerComparator>::add (pElement);
}

bool SimplePQ::isEmpty()
{
    return LChain<NodeDistancePairClass*, NDPObjPointerComparator>::isEmpty();
}

NodeDistancePairClass * SimplePQ::peek()
{
    return LChain<NodeDistancePairClass*, NDPObjPointerComparator>::peek();
}

NodeDistancePairClass * SimplePQ::pop()
{
    return LChain<NodeDistancePairClass*, NDPObjPointerComparator>::removeMaxMin();
}

NodeDistancePairClass * SimplePQ::decreaseKey (Node<NodeDistancePairClass*> *pNode,
                                               NodeDistancePairClass *pNewElement)
{
    return LChain<NodeDistancePairClass*, NDPObjPointerComparator>::changeElement (pNode, pNewElement);
}

void SimplePQ::display (void)
{
    LChain<NodeDistancePairClass*, NDPObjPointerComparator>::display();
}

/*****************************************************************************/

BHeapPQ::BHeapPQ (bool bIsMinHeap)
    : BHeap<NodeDistancePairClass*, NDPObjPointerComparator> (bIsMinHeap)
{
}

BHeapPQ::~BHeapPQ (void)
{
}

Node<NodeDistancePairClass*> * BHeapPQ::add (NodeDistancePairClass *pElement)
{
    return BHeap<NodeDistancePairClass*, NDPObjPointerComparator>::add (pElement);
}

bool BHeapPQ::isEmpty()
{
    return BHeap<NodeDistancePairClass*, NDPObjPointerComparator>::isEmpty();
}

NodeDistancePairClass * BHeapPQ::peek()
{
    return BHeap<NodeDistancePairClass*, NDPObjPointerComparator>::peek();
}

NodeDistancePairClass * BHeapPQ::pop()
{
    return BHeap<NodeDistancePairClass*, NDPObjPointerComparator>::pop();
}

NodeDistancePairClass * BHeapPQ::decreaseKey (Node<NodeDistancePairClass*> *pNode,
                                              NodeDistancePairClass *pNewElement)
{
    //BNode<NodeDistancePairClass*> (BNode<NodeDistancePairClass*>) pNode;
    return BHeap<NodeDistancePairClass*, NDPObjPointerComparator>::changeElement ((BNode<NodeDistancePairClass*>*) pNode, pNewElement);
}

void BHeapPQ::display (void)
{
    BHeap<NodeDistancePairClass*, NDPObjPointerComparator>::display();
}

/*****************************************************************************/

FHeapPQ::FHeapPQ (bool bIsMinHeap)
    : FHeap<NodeDistancePairClass*, NDPObjPointerComparator> (bIsMinHeap)
{
}

FHeapPQ::~FHeapPQ (void)
{
}

Node<NodeDistancePairClass*> * FHeapPQ::add (NodeDistancePairClass *pElement)
{
    return FHeap<NodeDistancePairClass*, NDPObjPointerComparator>::add (pElement);
}

bool FHeapPQ::isEmpty()
{
    return FHeap<NodeDistancePairClass*, NDPObjPointerComparator>::isEmpty();
}

NodeDistancePairClass * FHeapPQ::peek()
{
    return FHeap<NodeDistancePairClass*, NDPObjPointerComparator>::peek();
}

NodeDistancePairClass * FHeapPQ::pop()
{
    return FHeap<NodeDistancePairClass*, NDPObjPointerComparator>::pop();
}

NodeDistancePairClass * FHeapPQ::decreaseKey (Node<NodeDistancePairClass*> *pNode,
                                               NodeDistancePairClass *pNewElement)
{
    return FHeap<NodeDistancePairClass*, NDPObjPointerComparator>::changeElement ((BNode<NodeDistancePairClass*>*) pNode, pNewElement);
}

void FHeapPQ::display (void)
{
    FHeap<NodeDistancePairClass*, NDPObjPointerComparator>::display();
}


