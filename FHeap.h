#ifndef ADS_FIBONACCI_HEAP_H
#define ADS_FIBONACCI_HEAP_H

#include "BHeap.h"

/**
 * BHeap.h
 *
 * Generic template that implements a Fibonacci Heap.
 *
 * author: Giacomo Benincasa    (me@gbenin.casa)
 */

namespace ADS
{
    template<class T, class Comparator>
    class FHeap : public BHeap<T, Comparator>
    {
        public:
            FHeap (bool bIsMinHeap=true);
            virtual ~FHeap (void);

            /* Adds an element into the heap */
            FNode<T> * add (T element);

            /* Change pNode's element */
            T changeElement (BNode<T> *pNode, T newElement);

        private:
            /* Performs the cascading cut starting from node pNode. All the
               nodes with bCut set on true on pNode's path to the root until the
               first node with BCut set on false will be removed from their current
               doubly linked list and meld with the doubly linked list of the roots */
            void cascadingCut (FNode<T> *pNode);
    };

    template<class T, class Comparator>
    FHeap<T, Comparator>::FHeap (bool bIsMinHeap)
        : BHeap<T, Comparator> (bIsMinHeap)
    {
    }

    template<class T, class Comparator>
    FHeap<T, Comparator>::~FHeap()
    {
    }

    template<class T, class Comparator>
    FNode<T> * FHeap<T, Comparator>::add (T element)
    {
        FNode<T> *pNode = new FNode<T> (element);
        BHeap<T, Comparator>::add (pNode);
        return pNode;
    }

    template<class T, class Comparator>
    T FHeap<T, Comparator>::changeElement (BNode<T> *pNode, T newElement)
    {
        T oldElement = pNode->el;
        pNode->el = newElement;
        FNode<T> *pParent = NULL;
        if (Comparator::greaterThan (newElement, oldElement)) {
            if (BHeap<T, Comparator>::isMinHeap()) {
                /* remove it and re-insert it */
            }
            else {
                
            }
        }
        else if (Comparator::lessThan (newElement, oldElement))
            if (BHeap<T, Comparator>::isMinHeap()) {
                if (pNode->pParent != NULL) {
                    /* it's not a min tree root, check the min heap property */
                    if (Comparator::lessThan (newElement, pNode->pParent->el)) {
                        /* the min-heap property is violated, removed the node and re-instert it
                           as a min tree */
                        pParent = (FNode<T>*) pNode->pParent;
                        BHeap<T, Comparator>::detach (pNode, ((FNode<T>*)pNode)->pLeftSibling);
                        BHeap<T, Comparator>::_pHead = BHeap<T, Comparator>::meld (BHeap<T, Comparator>::_pHead, pNode);
                    }
                }
                else if (BHeap<T, Comparator>::isHead (pNode, BHeap<T, Comparator>::_pHead)) {
                    BHeap<T, Comparator>::_pHead = pNode;
                }
            }

        cascadingCut (pParent);

        return oldElement;
    }

    template<class T, class Comparator>
    void FHeap<T, Comparator>::cascadingCut (FNode<T> *pNode)
    {
        if ((pNode == NULL) || (pNode->pParent == NULL))
            return;

        if (!pNode->bCut) {
            pNode->bCut = true;
            return;
        }

        FNode<T> *pParent = (FNode<T>*) pNode->pParent;

        BHeap<T, Comparator>::detach (pNode, pNode->pLeftSibling);
        BHeap<T, Comparator>::meld (BHeap<T, Comparator>::_pHead, pNode);

        cascadingCut (pParent);
    }
}

#endif /* ADS_FIBONACCI_HEAP_H */


