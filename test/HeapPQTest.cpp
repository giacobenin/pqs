#include "PQueue.h"

#include <stdio.h>
#include <assert.h>

using namespace ADS;

int main (int argc, char *argv[])
{
    #ifdef USE_BINOMIAL_HEAP
        BHeapPQ pq;
    #elif USE_FIBONACCI_HEAP
        FHeapPQ pq;
    #else
        #error Must Define The Type of Heap
    #endif

    assert (pq.isEmpty() == true);

    Node<NodeDistancePairClass*> *pNode1 = pq.add (new NodeDistancePairClass (1, 2));
    assert (pNode1 != NULL);
    assert (pNode1->el != NULL);
    assert (pNode1->el->_key == 1);
    assert (pNode1->el->_cost == 2);
    assert (pq.isEmpty() == false);

    Node<NodeDistancePairClass*> *pNode2 = pq.add (new NodeDistancePairClass (2, 3));
    assert (pq.isEmpty() == false);

    Node<NodeDistancePairClass*> *pNode3 = pq.add (new NodeDistancePairClass (3, 1));
    assert (pq.isEmpty() == false);

    pq.display();

    assert (*(pq.peek()) == *(pNode3->el));
    assert (*(pq.pop()) == *(pNode3->el));

    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    NodeDistancePairClass *pOld = pq.decreaseKey (pNode2, new NodeDistancePairClass (2, 1));
    printf ("*******************\nDECREASE KEY\n");
    pq.display();
    printf ("*******************\n");
    delete pOld;

    Node<NodeDistancePairClass*> *pNode4 = pq.add (new NodeDistancePairClass (4, 6));
    printf ("pNode4 %p\n", pNode4);

    Node<NodeDistancePairClass*> *pNode5 = pq.add (new NodeDistancePairClass (5, 9));
    printf ("pNode5 %p\n", pNode5);

    Node<NodeDistancePairClass*> *pNode6 = pq.add (new NodeDistancePairClass (6, 15));
    printf ("pNode6 %p\n", pNode6);

    Node<NodeDistancePairClass*> *pNode7 = pq.add (new NodeDistancePairClass (7, 2));
    printf ("pNode7 %p\n", pNode7);

    Node<NodeDistancePairClass*> *pNode8 = pq.add (new NodeDistancePairClass (8, 3));
    printf ("pNode8 %p\n", pNode8);

    Node<NodeDistancePairClass*> *pNode9 = pq.add (new NodeDistancePairClass (9, 4));
    printf ("pNode9 %p\n", pNode9);

    Node<NodeDistancePairClass*> *pNode10 = pq.add (new NodeDistancePairClass (10, 2));
    printf ("pNode10 %p\n", pNode10);

    Node<NodeDistancePairClass*> *pNode11 = pq.add (new NodeDistancePairClass (11, 7));
    printf ("pNode11 %p\n", pNode11);

    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (*(pq.pop()) == *(pNode2->el));
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    pOld = pq.decreaseKey (pNode5, new NodeDistancePairClass (5, 1));
    assert (pOld != NULL);
    printf ("*******************\n");
    printf ("DECREASED %p (node of key %u)\n", pNode5, pNode5->el->_key);
    pq.display();
    printf ("*******************\n");
    delete pOld;

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (NULL != pq.pop());
    printf ("*******************\n");
    pq.display();
    printf ("*******************\n");

    assert (pq.isEmpty() == true);

    return 0;
}

