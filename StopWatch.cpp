#include "StopWatch.h"

using namespace ADS;

StopWatch::StopWatch()
{
    _start = 0;
}

StopWatch::~StopWatch()
{
}

void StopWatch::startWatch()
{
    _start = clock();
}

long long int StopWatch::stopWatch()
{
    return ((clock() - _start)/ (CLOCKS_PER_SEC / 1000));
}


