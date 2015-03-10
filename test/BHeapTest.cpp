#define BHEAP_TEST

#include <stdio.h>
#include <assert.h>

#include "Comparator.h"
#include "BHeap.h"

using namespace ADS;

int main (int argc, char *argv[])
{
    BHeap<int, Comparator<int> > bh;

    bh.add (5);
    assert (bh.peek() == 5);
    bh.display();

    assert (bh.pop() == 5);
    bh.display();

    assert (bh.peek() == 0);
    bh.display();

    assert (bh.pop() == 0);
    bh.display();

    bh.add (30);
    assert (bh.peek() == 30);
    bh.display();

    bh.add (40);
    assert (bh.peek() == 30);
    bh.display();

    bh.add (10);
    assert (bh.peek() == 10);
    bh.display();

    assert (bh.pop() == 10);
    bh.display();

    assert (bh.peek() == 30);
    bh.display();

    assert (bh.pop() == 30);
    bh.display();

    assert (bh.pop() == 40);
    bh.display();

    BNode<int> *pNode30 = bh.add (30);
    BNode<int> *pNode20 = bh.add (20);
    BNode<int> *pNode10 = bh.add (10);
    bh.display();

    assert (bh.pop() == 10);
    bh.display();

    bh.changeElement (pNode30, 5);
    bh.display();

    return 0;
}

