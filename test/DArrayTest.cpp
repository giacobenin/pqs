#include <stdio.h>
#include <assert.h>

#include "DArray.h"

using namespace ADS;

int main (int argc, char *argv[])
{

    DArray<unsigned int> a (0, 5, true);

    assert (a.add (5, 1) == 0);
    a.display();
    assert (a.add (5, 5) == 1);
    a.display();
    assert (a.add (7, 1) == 0);
    a.display();
    assert (a.add (8, 3) == 0);
    a.display();

    return 0;
}

