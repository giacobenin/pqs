pqs (Priority QueueS)
=====================
[![Build Status](https://travis-ci.org/giacobenin/pqs.svg?branch=master)](https://travis-ci.org/giacobenin/pqs) [![Analysis Status](https://scan.coverity.com/projects/6719/badge.svg)](https://scan.coverity.com/projects/giacobenin-pqs)

Code implemented for the 2011 Advanced Data Structures (COP5536) class project at UF.

The project asked to implement [Dijkstra's Single Source Shortest Path algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) for directed graphs using different priotity queues (notably [Fibonacci](https://en.wikipedia.org/wiki/Fibonacci_heap) and [Binomial](https://en.wikipedia.org/wiki/Binomial_heap) Heaps).

# Build

The `make` folder contains a `Makefile` to build on Linux.
The `vs` folder contains a Visual Studio solution to build on Windows.

The generated program is `ssp` (`ssp.exe` on Windows).

# Run

`ssp` can be used either to generate the shortest route from every source to every destination on a given graph, or to test the performance of the different queues on random graphs of different densities.

    ./ssp -is file_name

runs Dijkstra's Single Source Shortest Path algorithm using an unsorted queue as priority queue.

    ./ssp -ib file_name

runs Dijkstra's Single Source Shortest Path algorithm using a Binomial Heap as priority queue.

    ./ssp -if file_name

runs Dijkstra's Single Source Shortest Path algorithm using a Fibonacci Heap as priority queue.

Alternatively

    ./ssp -r

runs Dijkstra's Single Source Shortest Path algorithm on a set of random graphs with different densities using for each priority queue and outputs the performance of each.
The output looks something like as follows:

    Number of vertices    Density	Simple scheme(msec)    F-heap scheme (msec)    B-heap scheme(msec)
    1001                  10%       	69464.000000           50349.000000            45607.000000
    1001                  20%       	94291.000000           74725.000000            70161.000000
    1001                  30%       	114225.000000          97229.000000            90580.000000
    1001                  40%       	141640.000000          130986.000000           120526.000000