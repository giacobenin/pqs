#include "PQueue.h"

#include <stdio.h>
#include <assert.h>

using namespace ADS;

int main (int argc, char *argv[])
{
    SimplePQ pq;

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

   // assert (*(pq.peek()) == *(pNode3->el));
  //  assert (*(pq.pop()) == *(pNode3->el));

    printf ("*******************\n");
    pq.display();

    NodeDistancePairClass *pOld = pq.decreaseKey (pNode2, new NodeDistancePairClass (2, 1));
    delete pOld;

    printf ("*******************\n");
    pq.display();

    
    /**************************************************************************/
    printf ("Using enw queue\n");
    /**************************************************************************/

    SimplePQ pq2; /* unsorted */

    assert (pq2.isEmpty() == true);

    Node<NodeDistancePairClass*> *pNode4 = pq2.add (new NodeDistancePairClass (1, 2));
    assert (pNode4 != NULL);
    assert (pNode4->el != NULL);
    assert (pNode4->el->_key == 1);
    assert (pNode4->el->_cost == 2);
    assert (pq2.isEmpty() == false);

    Node<NodeDistancePairClass*> *pNode5 = pq2.add (new NodeDistancePairClass (2, 3));
    assert (pq2.isEmpty() == false);

    Node<NodeDistancePairClass*> *pNode6 = pq2.add (new NodeDistancePairClass (3, 1));
    assert (pq2.isEmpty() == false);

    pq2.display();

    assert (*(pq2.pop()) == *(pNode6->el));

    printf ("*******************\n");
    pq2.display();

    pOld = pq2.decreaseKey (pNode5, new NodeDistancePairClass (2, 1));
    delete pOld;

    printf ("*******************\n");
    pq2.display();
    
    return 0;
}

