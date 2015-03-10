#ifndef ADS_LINKED_CHAIN_H
#define ADS_LINKED_CHAIN_H

#include "Node.h"

/**
 * LChain.h
 *
 * Generic template that implements a linked chain.
 *
 * author: Giacomo Benincasa    (giacomo@cise.ufl.edu)
 */

namespace ADS
{
    template<class T, class Comparator>
    class LChain
    {
        public:
            LChain (bool bSorted=true, bool bAscendentOrder=false);
            virtual ~LChain (void);

            /* Calls insert and returns the created node */
            Node<T> * add (T element);

            /* Inserts the element at the last position
               (it does not ensure the order condition) */
            int append (T element);

            /* Change pNode's element */
            T changeElement (Node<T> *pNode, T newElement);

            /* Inserts the element at the right position */
            int insert (T element);

            /* Inserts the element at the root position
               (it does not ensure the order condition) */
            int prepend (T element);

            /* Returns the fist element of the LChain if any, NULL otherwise.
               If bResetCurrElemet is set on true, the pointer to the next
               element will be re-set to the first element _before_ returning
               the first element. After returning the first element, the pointer
               to the next element will point to the second one.*/
            T getFirst (bool bResetCurrElement=false);

            /* Returns the next element in the list */
            T getNext (void);

            /* Returns and remove the head of the chain */
            T peek (void);

            /* Returns and remove the head of the chain */
            T pop (void);

            /* Removes element from the list and returns it if it was
               found, returns NULL otherwise */
            T remove (T element);

            /* Removes the max if the queue is not ascending, the min if the queue
               is ascending and returns it. (If the list is sorted, this is
               equivalent to calling pop) */
            T removeMaxMin (void);

            /* Reset the pointer to the current element in the list */
            void resetGet (void);

            /* Returns true if the list is empty, false otherwise */
            bool isEmpty (void);

            /* Iterates through the list until the element is found.
               Returns true if it is found, false otherwise */
            bool seach (T element);

            void display (void);

        private:
            /* creates a new node that contains element and adds it as the
               next node of pPrev */
            int insert (Node<T> *pNode);
            int insert (Node<T> *pPrev, T element);
            int insert (Node<T> *pPrev, Node<T> *pNewNode);
            int prepend (Node<T> *pNode);

        private:
            bool _bSorted;
            bool _bAscendentOrder;

            Node<T> *_pRoot;
            Node<T> *_pGetNext;
    };

    template<class T, class Comparator>
    LChain<T, Comparator>::LChain (bool bSorted, bool bAscendentOrder)
    {
        _bSorted = bSorted;
        _bAscendentOrder = bAscendentOrder;
        _pRoot = _pGetNext = NULL;
    }

    template<class T, class Comparator>
    LChain<T, Comparator>::~LChain()
    {
    }

    template<class T, class Comparator>
    Node<T> * LChain<T, Comparator>::add (T element)
    {
        Node<T> *pNode = new Node<T> (element);
        
        int rc = insert (pNode);

        if (rc < 0) {
            /* the node was not inserted */
            delete pNode;
            return NULL;
        }
        return pNode;
    }

    template<class T, class Comparator>
    int LChain<T, Comparator>::append (T element)
    {
        if (_pRoot == NULL)
            _pRoot = new Node<T> (element);
        else {
            Node<T> *pTmp = _pRoot;
            /* Go to the end of the list */
            while (pTmp->pRightSibling != NULL)
                pTmp = pTmp->pRightSibling;

            pTmp->pRightSibling = new Node<T> (element);
        }

        return 0;
    }

    template<class T, class Comparator>
    T LChain<T, Comparator>::changeElement (Node<T> *pNode, T newElement)
    {
        if (_pRoot == NULL)
            return NULL;

        if (!_bSorted) {
            T oldElement = pNode->el;
            pNode->el = newElement;
            return oldElement;
        }

        Node<T> *pTmp = NULL;
        if (Comparator::equals (pNode->el, _pRoot->el)) {
            pTmp = _pRoot;
            _pRoot = _pRoot->pRightSibling;
        }
        else {
            Node<T> *pCurrNode = _pRoot;
            while (pCurrNode != NULL) {
                if (pCurrNode->pRightSibling == NULL)
                    break;

                if (Comparator::equals (pNode->el, pCurrNode->pRightSibling->el)) {
                    pTmp = pCurrNode->pRightSibling;
                    pCurrNode->pRightSibling = pCurrNode->pRightSibling->pRightSibling;
                    break;
                }

                pCurrNode = pCurrNode->pRightSibling;
            }
        }

        if (pTmp == NULL)
            /* element was not found */
            return NULL;

        T oldElement = pTmp->el;
        pTmp->el = newElement;

        /* insert it back! */
        insert (pTmp);

        return oldElement;
    }

    template<class T, class Comparator>
    int  LChain<T, Comparator>::insert (T element)
    {
        return insert (new Node<T> (element));
    }

    template<class T, class Comparator>
    int  LChain<T, Comparator>::prepend (T element)
    {
        return prepend (new Node<T> (element));
    }

    template<class T, class Comparator>
    T LChain<T, Comparator>::getFirst (bool bResetCurrElement)
    {
        if (bResetCurrElement) {
            resetGet();
            return getNext();
        }
        else if (_pRoot == NULL)
            return NULL;

        return _pRoot->el;
    }

    template<class T, class Comparator>
    T LChain<T, Comparator>::getNext()
    {
        if (_pGetNext == NULL)
            return NULL;

        T tmpEl = _pGetNext->el;
        _pGetNext = _pGetNext->pRightSibling;
        return tmpEl;
    }

    template<class T, class Comparator>
    T LChain<T, Comparator>::peek()
    {
        if (_pRoot == NULL)
            return NULL;

        return _pRoot->el;
    }

    template<class T, class Comparator>
    T LChain<T, Comparator>::pop()
    {
        if (_pRoot == NULL)
            return NULL;

        Node<T> *pTmp = _pRoot;
        _pRoot = _pRoot->pRightSibling;

        if (_pGetNext == pTmp)
            /* Make sure that _pGetNext does not 
               point to the element to be removed */
            _pGetNext = _pRoot;

        T element = pTmp->el;
        delete pTmp;

        return element;
    }

    template<class T, class Comparator>
    T LChain<T, Comparator>::remove (T element)
    {
        if (_pRoot == NULL)
            return NULL;

        if (Comparator::equals (element, _pRoot->el)) {
            T tmp = _pRoot->el;
            Node<T> *pTmp = _pRoot->pRightSibling;
            delete _pRoot;
            _pRoot = pTmp;
            return tmp;
        }

        Node<T> *pNode = _pRoot;
        while (pNode != NULL) {
            Node<T> *pNext = pNode->pRightSibling;
            if (pNext == NULL)
                return NULL;

            if (Comparator::equals (element, pNext->el)) {
                pNode->pRightSibling = pNext->pRightSibling;
                T tmp = pNext->el;
                delete pNext;
                return tmp;
            }

            pNode = pNext;
        }

        return NULL;
    }

    template<class T, class Comparator>
    T LChain<T, Comparator>::removeMaxMin (void)
    {
        if (_pRoot == NULL)
            return NULL;

        if (_bSorted)
            /* if it's sorted the max/min will be at the head of the queue*/
            return pop();

        Node<T> *pPrev, *pCurr, *pPrevMaxMin, *pMaxMin;

        pPrevMaxMin = NULL;
        pPrev = pMaxMin = _pRoot;
        pCurr = _pRoot->pRightSibling;

        while (pCurr != NULL) {
            if (_bAscendentOrder) {
                if (Comparator::lessThan (pCurr->el, pMaxMin->el)) {
                    pPrevMaxMin = pPrev;
                    pMaxMin = pCurr;
                }
            }
            else {
                if (Comparator::greaterThan (pCurr->el, pMaxMin->el)) {
                    pPrevMaxMin = pPrev;
                    pMaxMin = pCurr;
                }
            }
            pPrev = pCurr;
            pCurr = pCurr->pRightSibling;
        }

        if (pPrevMaxMin == NULL)
            /* the pMaxMin is the root */
            return pop();

        /* the node to be removed is not the root - update the pointer to the
           next element of the previous node */
        pPrevMaxMin->pRightSibling = pMaxMin->pRightSibling;
        
        T element = pMaxMin->el;
        delete pMaxMin;

        return element;
    }

    template<class T, class Comparator>
    void LChain<T, Comparator>::resetGet()
    {
        _pGetNext = _pRoot;
    }

    template<class T, class Comparator>
    bool LChain<T, Comparator>::isEmpty (void)
    {
        return (_pRoot == NULL);
    }

    template<class T, class Comparator>
    bool LChain<T, Comparator>::seach (T element)
    {
        Node<T> *pNode = _pRoot;
        while (pNode != NULL) {
            if (Comparator::equals (pNode->el, element))
                return true;
            pNode = pNode->pRightSibling;
        }
        return false;
    }

    template<class T, class Comparator>
    void LChain<T, Comparator>::display()
    {
        for (Node<T> *pNode = _pRoot; pNode != NULL; pNode = pNode->pRightSibling)
            pNode->el->display();
    }

    template<class T, class Comparator>
    int  LChain<T, Comparator>::insert (Node<T> *pNode)
    {
        if (!_bSorted) {
            if (seach (pNode->el))
                return -1;
            /* Add the element only if not already in the list */
            return prepend (pNode);
        }

        if (_pRoot == NULL) {
            _pRoot = pNode;
           return 0;
        }

        if (_bAscendentOrder) {
            /* ascending order */
            if (Comparator::lessThan (pNode->el, _pRoot->el))
                return prepend (pNode);
        }
        else if (pNode->el > _pRoot->el)
            /* descending order */
            return prepend (pNode);

        Node<T> *pCurrNode = _pRoot;
        while (pCurrNode != NULL) {
            if (pCurrNode->pRightSibling == NULL) {
                pCurrNode->pRightSibling = pNode;
                return 0;
            }

            if (_bAscendentOrder) {
                /* ascending order */
                if (Comparator::lessThan (pNode->el, pCurrNode->pRightSibling->el))
                    return insert (pCurrNode, pNode);
            }
            else if (Comparator::greaterThan (pNode->el, pCurrNode->pRightSibling->el))
                /* descending order */
                return insert (pCurrNode, pNode);

            pCurrNode = pCurrNode->pRightSibling;
        }

        /* it should never get here... */
        return -2;
    }

    template<class T, class Comparator>
    int LChain<T, Comparator>::insert (Node<T> *pPrev, T element)
    {
        return insert (pPrev, new Node<T> (element));
    }

    template<class T, class Comparator>
    int LChain<T, Comparator>::insert (Node<T> *pPrev, Node<T> *pNewNode)
    {
        if ((pPrev == NULL) || (pNewNode == NULL))
            return -1;

        Node<T> *pTmp = pPrev->pRightSibling;
        pPrev->pRightSibling = pNewNode;
        pNewNode->pRightSibling = pTmp;

        return 0;
    }

    template<class T, class Comparator>
    int LChain<T, Comparator>::prepend (Node<T> *pNode)
    {
        Node<T> *pTmp = _pRoot;
        _pRoot = pNode;
        _pRoot->pRightSibling = pTmp;

        return 0;
    }
}

#endif /* ADS_LINKED_CHAIN_H */


