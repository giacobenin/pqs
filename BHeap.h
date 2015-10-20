#ifndef ADS_BINOMIAL_HEAP_H
#define ADS_BINOMIAL_HEAP_H

#include "BHeapDegreeTable.h"
#include "Node.h"

/**
 * BHeap.h
 *
 * Generic template that implements a Binomial Heap.
 *
 * author: Giacomo Benincasa    (giacomo@cise.ufl.edu)
 */

namespace ADS
{
    template<class T, class Comparator>
    class BHeap
    {
        public:
            BHeap (bool bIsMinHeap=true);
            virtual ~BHeap (void);

            /* Adds an element into the heap */
            BNode<T> * add (T element);

            /* Change pNode's element */
            T changeElement (BNode<T> *pNode, T newElement);

            /* Returns true if the BHeap is empty */
            bool isEmpty (void);

            bool isMinHeap (void);

            /* Melds pBHeap into the BTree */
            void meld (BHeap *pBHeap);

            /* Returns the head of the heap, NULL otherwise. If NULL is
               a legit element, isEmpty() should be used to check whether
               the returned element is valid or not */
            T peek (void);

            /* Returns and remove the head of the heap. If NULL is
               a legit element, isEmpty() should be used to check whether
               the returned element is valid or not */
            T pop (void);

            void display (void);

        protected:
            void add (BNode<T> *pNode);

            /* Removes pNode as a sibling from pNodeLeftSibling. it is some
               node's first child, it is updated too */
            void detach (BNode<T> *pNode, BNode<T> *pNodeLeftSibling);

            /* Returns true if the first node should be the head
               of the meld of the two nodes */
            bool isHead (BNode<T> *pNode1, BNode<T> *pNode2);

            /* Melds pRootNode1 and pRootNode2 and returns
               head (pRootNode1, pRootNode2 */
            BNode<T> * meld (BNode<T> *pRootNode1, BNode<T> *pRootNode2);

        protected:
            BNode<T> *_pHead;

        private:
            /* Add pChild to pRoot's children list and increments
               pRoot's degree */
            void addChild (BNode<T> *pRoot, BNode<T> *pChild);

            void bubbleDown (BNode<T> *pNode);
            void bubbleUp (BNode<T> *pNode);

            /* Combines pNode1 and pNode2 in a single tree, updates the
               degreeTable with the newly created tree and returns the
               node that has to be detached from the list of the roots */
            BNode<T> * combine (BNode<T> *pNode1, BNode<T> *pNode2);
            void combineInternal (BNode<T> *pNode1, BNode<T> *pNode2);

            /* Returns pNode's left sibling */
            BNode<T> * getLeftSibling (BNode<T> *pNode);

            /* Melds pNodeToMeld with _pHead */
            void meld (BNode<T> *pNodeToMeld);

            /* performs the pair merge that melds trees the root
               elements with the same degree */
            void pairMerge (BNode<T> *pNodeToDetach);

            /* swaps the content of the two nodes */
            void swap (BNode<T> *pRoot1, BNode<T> *pRoot2);
            void swap (BNode<T> *pNode1, BNode<T> *pNode1Prev,
                       BNode<T> *pNode2, BNode<T> *pNode2Prev);

            /* Set pParent as parent node of pFirstChild and its siblings */
            void updateParent (BNode<T> *pFirstChild, BNode<T> *pParent);

            void display (BNode<T> *pNode); 
            unsigned int getLevel (BNode<T> *pNode);
            void printTabs (unsigned int uiLevel);

        private:
            bool _bIsMinHeap;

            DegreeTable<T> _degreeTable;
    };

    template<class T, class Comparator>
    BHeap<T, Comparator>::BHeap (bool bIsMinHeap)
    {
        _pHead = NULL;
        _bIsMinHeap = bIsMinHeap;
    }

    template<class T, class Comparator>
    BHeap<T, Comparator>::~BHeap()
    {
    }

    template<class T, class Comparator>
    BNode<T> * BHeap<T, Comparator>::add (T element)
    {
        BNode<T> *pNode = new BNode<T> (element);
        if (pNode == NULL) {
            log ("Memory Exhausted\n");
            exit (1);
        }
        add (pNode);
        return pNode;
    }

    template<class T, class Comparator>
    T BHeap<T, Comparator>::changeElement (BNode<T> *pNode, T newElement)
    {
        T oldElement = pNode->el;
        pNode->el = newElement;
        if (Comparator::greaterThan (newElement, oldElement))
            _bIsMinHeap ?  bubbleDown (pNode) : bubbleUp (pNode);
        else if (Comparator::lessThan (newElement, oldElement))
            _bIsMinHeap ? bubbleUp (pNode) : bubbleDown (pNode);

        return oldElement;
    }

    template<class T, class Comparator>
    bool BHeap<T, Comparator>::isEmpty()
    {
        return (_pHead == NULL);
    }

    template<class T, class Comparator>
    bool BHeap<T, Comparator>::isMinHeap()
    {
        return _bIsMinHeap;
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::meld (BHeap *pBHeap)
    {
        if ((pBHeap == NULL))
            return;

        if (_pHead == NULL) {
            _pHead = pBHeap->_pHead;
            return;
        }

        meld (pBHeap->_pHead);
    }

    template<class T, class Comparator>
    T BHeap<T, Comparator>::peek()
    {
        if (isEmpty())
            return NULL;

        return _pHead->el;
    }

    template<class T, class Comparator>
    T BHeap<T, Comparator>::pop()
    {
        if (isEmpty())
            return NULL;

        /* meld() may updated the root (in case _pHead has a child with the same
           key, any of the two could be selected as new root. Furthermore
           pairMerge() will detach _pHead thus its reference will be lost */
        BNode<T> *pOldHead = _pHead;

        /* add former head's children into the root element list */
        meld (_pHead->pFirstChild);

        pOldHead->pFirstChild = NULL;
        pairMerge (pOldHead);

        /* Deallocate the memory for the node and return the wrapped
           element */
        T element = pOldHead->el;
        pOldHead->reset();
        delete pOldHead;
        return element;
    }

    template<class T, class Comparator>
    BNode<T> * BHeap<T, Comparator>::getLeftSibling (BNode<T> *pNode)
    {
        if (pNode == NULL)
            return NULL;

        if (pNode->getType() == FibonacciHeap) {
            return ((FNode<T>*) pNode)->pLeftSibling;
        }

        if (pNode->pRightSibling == NULL) {
            display();
        }
        
        BNode<T> *pLeftSibling = pNode;
        while (pLeftSibling->pRightSibling != pNode)
            pLeftSibling = pLeftSibling->getSibling();

        return pLeftSibling;
    }

    template<class T, class Comparator>
    bool BHeap<T, Comparator>::isHead (BNode<T> *pNode1, BNode<T> *pNode2)
    {
        if (pNode1 == NULL)
            return false;

        if (pNode2 == NULL)
            return true;

        if (_bIsMinHeap)
            return Comparator::lessThan (pNode1->el, pNode2->el);
        else
            return Comparator::greaterThan (pNode1->el, pNode2->el);
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::meld (BNode<T> *pNodeToMeld)
    {
        if (pNodeToMeld == NULL)
            return;

        if (_pHead == NULL) {
            _pHead = pNodeToMeld;
            return;
        }

        _pHead = meld (_pHead, pNodeToMeld);
    }

    template<class T, class Comparator>
    BNode<T> * BHeap<T, Comparator>::meld (BNode<T> *pRootNode1, BNode<T> *pRootNode2)
    {
        if (pRootNode1 == NULL)
            return pRootNode2;

        if (pRootNode2 == NULL)
            return pRootNode1;

        if ((pRootNode1->getType() == FibonacciHeap) &&
            (pRootNode2->getType() == FibonacciHeap)) {

            /* Update the pointers to the left sibling */
            FNode<T> *pNode1RightSibling = (FNode<T> *) pRootNode1->pRightSibling;
            FNode<T> *pNode2RightSibling = (FNode<T> *) pRootNode2->pRightSibling;

            pNode1RightSibling->pLeftSibling = (FNode<T> *) pRootNode2;
            pNode2RightSibling->pLeftSibling = (FNode<T> *) pRootNode1;
        }

        BNode<T> *pTmp = pRootNode1->getSibling();
        pRootNode1->setSibling (pRootNode2->getSibling());
        pRootNode2->setSibling (pTmp);

        /* return the head root */
        if (isHead (pRootNode1, pRootNode2))
            return pRootNode1;
        else
            return pRootNode2;
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::add (BNode<T> *pNode)
    {
        meld (pNode);
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::addChild (BNode<T> *pRoot, BNode<T> *pChild)
    {
        if (Comparator::equals (pRoot->el, pChild->el)) {
            log ("Adding a node as child of itself. Quitting\n");
            exit (-1);
        }

        pChild->resetSibling();
        if (pRoot->getType() == FibonacciHeap)
            /* If it's a Fibonacci Heap Node, reset left pointer as well */
            ((FNode<T>*) pChild)->pLeftSibling = (FNode<T>*)pChild;

        pChild->pParent = pRoot;
        pRoot->pFirstChild = meld (pRoot->pFirstChild, pChild);
        pRoot->uiDegree++;
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::bubbleDown (BNode<T> *pNode)
    {
        BNode<T> *pHeadNode = pNode;
        while (pNode->getSibling() != pNode) {
            BNode<T> *pSibling, *pFirstSibling;
            pSibling = pFirstSibling = pNode->getSibling();
            do {
                if (isHead (pSibling, pHeadNode))
                    pHeadNode = pSibling;
            } while (pSibling != pFirstSibling);

            if (pHeadNode != pNode)
                swap (pHeadNode, pNode);
            else
                break;
            pNode = pHeadNode;
        }
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::bubbleUp (BNode<T> *pNode)
    {
        while (pNode->pParent != NULL) {
            if (isHead (pNode, pNode->pParent))
                swap (pNode, pNode->pParent);
            else
                break;
        }

        if (pNode->pParent == NULL)
            /* it made it to the root - it may be the new head */
            if (isHead (pNode, _pHead))
                _pHead = pNode;
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::pairMerge (BNode<T> *pNodeToDetach)
    {
        if ((isEmpty()) || (pNodeToDetach == NULL))
            return;

        if (pNodeToDetach == _pHead)
            _pHead = NULL;

        BNode<T> *pPrevNode = pNodeToDetach;
        BNode<T> *pCurrNode = pNodeToDetach->getSibling();
        BNode<T> *pNextNode;

        while (pCurrNode != pNodeToDetach) {

            /* Update node if necessary */
            if (isHead (pCurrNode, _pHead))
                /* update the head */
                _pHead = pCurrNode;
            if (pCurrNode->pParent != NULL)
                /* pNodeToDetach's children's parent pointer needs to be reset */
                pCurrNode->pParent = NULL;

            /* Combine same degree min trees */
            pNextNode = pCurrNode->getSibling();
            detach (pCurrNode, pPrevNode);

            if (_degreeTable.used (pCurrNode->uiDegree)) {
                BNode<T> *pSameDegreeNode;
                _degreeTable.remove (pCurrNode->uiDegree, pSameDegreeNode);
                combine (pCurrNode, pSameDegreeNode);
            }
            else
                _degreeTable.add (pCurrNode->uiDegree, pCurrNode);

            pCurrNode = pNextNode;
        }

        /* Add the min trees that are in the degree table to the root circular list */
        for (unsigned int i = 0; i < _degreeTable.size(); i++) {
            if (_degreeTable.used (i)) {
                BNode<T> *pNewSameDegreeNode;
                _degreeTable.remove (i, pNewSameDegreeNode);

                meld (pNewSameDegreeNode);
            }
        }
    }

    template<class T, class Comparator>
    BNode<T> * BHeap<T, Comparator>::combine (BNode<T> *pCurrNode, BNode<T> *pSameDegreeNode)
    {
        BNode<T> *pNewNode;
        if (isHead (pCurrNode, pSameDegreeNode)) {
            addChild (pCurrNode, pSameDegreeNode);
            if (pCurrNode->getType() == FibonacciHeap)
                ((FNode<T>*)pCurrNode)->bCut = false;
            pNewNode = pCurrNode;
        }
        else {
            addChild (pSameDegreeNode, pCurrNode);
            if (pSameDegreeNode->getType() == FibonacciHeap)
                ((FNode<T>*)pSameDegreeNode)->bCut = false;
            pNewNode = pSameDegreeNode;
        }

        if (_degreeTable.used (pNewNode->uiDegree)) {
            BNode<T> *pNewSameDegreeNode;
            _degreeTable.remove (pNewNode->uiDegree, pNewSameDegreeNode);
            combineInternal (pNewNode, pNewSameDegreeNode);
        }
        else
            _degreeTable.add (pNewNode->uiDegree, pNewNode);
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::combineInternal (BNode<T> *pNode1, BNode<T> *pNode2)
    {
        /* These nodes have already been detached */
        BNode<T> *pNewNode;
        if (isHead (pNode1, pNode2)) {
            addChild (pNode1, pNode2);
            pNewNode = pNode1;
            if (pNode2->getType() == FibonacciHeap)
                ((FNode<T>*)pNode2)->bCut = false;
        }
        else {
            addChild (pNode2, pNode1);
            pNewNode = pNode2;
            if (pNode1->getType() == FibonacciHeap)
                ((FNode<T>*)pNode1)->bCut = false;
        }

        if (_degreeTable.used (pNewNode->uiDegree)) {
            BNode<T> *pNewSameDegreeNode;
            _degreeTable.remove (pNewNode->uiDegree, pNewSameDegreeNode);
            combineInternal (pNewNode, pNewSameDegreeNode);
        }
        else
            _degreeTable.add (pNewNode->uiDegree, pNewNode);
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::detach (BNode<T> *pNode, BNode<T> *pNodeLeftSibling)
    {
        pNodeLeftSibling->setSibling (pNode->getSibling());

        if ((pNode->pParent != NULL) && (pNode->pParent->pFirstChild == pNode)) {
            /* pNode was the first child of pNode->pParent, update
               pNode->pParent->pFirstChild */
            if (pNodeLeftSibling != pNode)
                pNode->pParent->pFirstChild = pNodeLeftSibling;
            else
                pNode->pParent->pFirstChild = NULL;
        }
        if (_pHead == pNode)
            _pHead = NULL;

        if (pNode->getType() == FibonacciHeap) {
            /* if it's a Fibonacci heap node, it is necessary to update right
               sibling's pointer to the node */
            FNode<T> *pFNode = (FNode<T> *) pNode;
            ((FNode<T> *) pFNode->pRightSibling)->pLeftSibling = (FNode<T> *) pNodeLeftSibling;
            pFNode->pLeftSibling = pFNode;
            pFNode->pParent = NULL;
        }

        /* Reset the node's sibling pointers */
        pNode->resetSibling();
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::swap (BNode<T> *pNode1, BNode<T> *pNode2)
    {
        if ((pNode1 == NULL) || (pNode2 == NULL))
            return;

        if ((pNode1->pParent != pNode2) && (pNode2->pParent != pNode1)) {
            log ("Error! Only parent/child nodes can be swapped\n");
            exit (1);
        }

        swap (pNode1, getLeftSibling (pNode1), pNode2, getLeftSibling (pNode2));
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::swap (BNode<T> *pNode1, BNode<T> *pNode1Prev,
                                     BNode<T> *pNode2, BNode<T> *pNode2Prev)
    {
        if ((pNode1->pParent != pNode2) && (pNode2->pParent != pNode1)) {
            log ("Error! Only parent/child nodes can be swapped\n");
            exit (1);
        }

        /* Update parent/child links */
        BNode<T> *pParent, *pChild;
        if (pNode1->pParent == pNode2) {
            pParent = pNode2;
            pChild = pNode1;
        }
        else {
            pParent = pNode1;
            pChild = pNode2;
        }

        updateParent (pChild->pFirstChild, pParent);
        updateParent ((BNode<T>*)pChild->pRightSibling, pChild);

        pChild->pParent = pParent->pParent;
        pParent->pParent = pChild;
        pParent->pFirstChild = pChild->pFirstChild;
        pChild->pFirstChild = pParent;

        /* update new pChild's parent link to it*/
        if (pChild->pParent != NULL && pChild->pParent->pFirstChild == pParent)
            /* if pChild->pParent->pFirstChild points to one of previous
               pParent's siblings there is not need to update it, otherwise
               make it point to pChild */
            pChild->pParent->pFirstChild = pChild;
        
        unsigned int uiTmpDegree = pNode1->uiDegree;
        pNode1->uiDegree = pNode2->uiDegree;
        pNode2->uiDegree = uiTmpDegree;

       /* T elementTmp = pNode1->el;
        pNode1->el = pNode2->el;
        pNode2->el = elementTmp;*/

        /* Update sibling links */
        BNode<T> *pTmp = pNode1->getSibling();
        if (pNode2->getSibling() == pNode2) {
            pNode1->setSibling (pNode1);                
        }
        else {
            pNode1->setSibling (pNode2->getSibling());            
            pNode2Prev->pRightSibling = pNode1;
        }
        
        if (pTmp == pNode1) {
            pNode2->setSibling (pNode2);
        }
        else {
            pNode2->setSibling (pTmp);
            pNode1Prev->pRightSibling = pNode2;
        }
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::updateParent (BNode<T> *pFirstChild, BNode<T> *pParent)
    {
        if (pFirstChild == NULL)
            return;

        if (pFirstChild == pParent)
            return;

        pFirstChild->pParent = pParent;

        BNode<T> *pCurrNode = pFirstChild->getSibling();
        while (pCurrNode != pFirstChild) {
            pCurrNode->pParent = pParent;
            pCurrNode = pCurrNode->getSibling();
        }
    }

    /**************************************************************************/

    template<class T, class Comparator>
    void BHeap<T, Comparator>::display (void)
    {
        display (_pHead);
    }

    template<class T, class Comparator>
    void BHeap<T, Comparator>::display (BNode<T> *pNode)
    {
        if (pNode == NULL)
            return;

        BNode<T> *pFirstNode = pNode;
        BNode<T> *pTmp = pNode;
        do {
            #ifdef BHEAP_TEST
                printf ("%d ", pTmp->el);
            #else
                if (pNode != pTmp)
                    printTabs (getLevel (pTmp));
                printf ("%u (%u, %u)[%p %p]\t\t", pTmp->el->_cost, pTmp->el->_key, pTmp->uiDegree, pTmp, pTmp->getSibling());
                
                display (pTmp->pFirstChild);
                printf ("\n");
            #endif
            pTmp = pTmp->getSibling();
        } while ((pTmp != NULL) && (pFirstNode != pTmp));
    }

    template<class T, class Comparator>
    unsigned int BHeap<T, Comparator>::getLevel (BNode<T> *pNode)
    {
        unsigned int uiLevel = 0;
        for (BNode<T> *pParent = pNode->pParent; pParent != NULL; pParent = pParent->pParent)
            uiLevel++;
        return uiLevel;
    }
    
    template<class T, class Comparator>
    void BHeap<T, Comparator>::printTabs (unsigned int uiLevel)
    {
        for (unsigned int i = 0; i < uiLevel; i++)
            printf ("\t\t\t\t\t");
    }
}

#endif /* ADS_BINOMIAL_HEAP_H */

