#include <stdio.h>
#include <assert.h>

#include "FHeap.h"

using namespace ADS;

int main (int argc, char *argv[])
{
    BHeap<int> bh;

    bh.add (5);
    assert (bh.peek() == 5);
    assert (bh.pop() == 5);
    assert (bh.peek() == 0);
    assert (bh.pop() == 0);

    return 0;
}

