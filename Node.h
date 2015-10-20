#ifndef ADS_NODE_H
#define ADS_NODE_H

#include <stddef.h>

namespace ADS
{
    enum NodeType {
        Simple,
        BinomialHeap,
        FibonacciHeap
    };

    /* Simple node that wraps an element */
    template<class T>
    struct Node
    {
        Node (T element);
        virtual ~Node (void);

        NodeType getType (void);

        T el;
        Node<T> *pRightSibling;

        protected:
            Node (NodeType nodeType, T element);

        private:
            NodeType type;
    };

    /* node for binomial heap */
    template<class T>
    struct BNode : public Node<T>
    {
        /* Creates a Node which is sibling of itself */
        BNode (T element);
        virtual ~BNode (void);

        /* Returns the next sibling of the element */
        unsigned int getChildCount (void);
        BNode<T> * getSibling (void);
        unsigned int getSiblingCount (void);
        void setSibling (BNode<T> *pSibling);

        /* Resets all the pointers to NULL */
        void reset (void);
        void resetSibling (void);

        BNode<T> *pParent;
        BNode<T> *pFirstChild;
        unsigned int uiDegree;

        protected:
            BNode (NodeType nodeType, T element);
    };

    /* node for Fibonacci heap */
    template<class T>
    struct FNode : public BNode<T>
    {
        /* Creates a Node which is sibling of itself */
        FNode (T element);
        ~FNode (void);

        /*
         * Reset all the pointers to NULL
         */
        void reset (void);

        bool bCut;
        FNode<T> *pLeftSibling;
    };

    /*************************************************************************/

    template<class T>
    Node<T>::Node (T element)
    {
        type = Simple;
        el = element;
        pRightSibling = NULL;
    }

    template<class T>
    Node<T>::Node (NodeType nodeType, T element)
    {
        type = nodeType;
        el = element;
        pRightSibling = NULL;
    }

    template<class T>
    Node<T>::~Node()
    {
    }

    template<class T>
    NodeType Node<T>::getType()
    {
        return type;
    }

    /*************************************************************************/

    template<class T>
    BNode<T>::BNode (T element)
        : Node<T> (BinomialHeap, element)
    {
        reset();
    }

    template<class T>
    BNode<T>::BNode (NodeType nodeType, T element)
        : Node<T> (nodeType, element)
    {
        reset();
    }

    template<class T>
    BNode<T>::~BNode()
    {
        Node<T>::pRightSibling = NULL;
    }

    template<class T>
    unsigned int BNode<T>::getChildCount()
    {
        if (pFirstChild == NULL)
            return 0;
        return (1 + pFirstChild->getSiblingCount());
    }

    template<class T>
    BNode<T> * BNode<T>::getSibling()
    {
        return (BNode<T> *) Node<T>::pRightSibling;
    }

    template<class T>
    unsigned int BNode<T>::getSiblingCount()
    {
        unsigned int uiCount = 0;
        for (BNode<T> *pCurrNode = getSibling(); pCurrNode != this;
             pCurrNode = pCurrNode->getSibling())
            uiCount++;
        return uiCount;
    }

    template<class T>
    void BNode<T>::setSibling (BNode<T> *pSibling)
    {
        Node<T>::pRightSibling = pSibling;
    }

    template<class T>
    void BNode<T>::reset()
    {
        pParent = pFirstChild = NULL;
        resetSibling();
        uiDegree = 0;
    }

    template<class T>
    void BNode<T>::resetSibling()
    {
        Node<T>::pRightSibling = this;
    }

    /*************************************************************************/

    template<class T>
    FNode<T>::FNode (T element)
        : BNode<T> (FibonacciHeap, element)
    {
        reset();
    }

    template<class T>
    FNode<T>::~FNode()
    {
        pLeftSibling = NULL;
    }

    template<class T>
    void FNode<T>::reset()
    {
        BNode<T>::reset();
        pLeftSibling = this;
        bCut = false;
    }
}

#endif /* ADS_NODE_H */


