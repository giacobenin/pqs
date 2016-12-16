cmake_minimum_required(VERSION 3.6)
project(pqs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    Algorithms.h
    BHeap.h
    BHeapDegreeTable.h
    Comparator.h
    DArray.h
    Defs.h
    FHeap.h
    Graph.h
    GraphReader.cpp
    GraphReader.h
    GraphUtils.cpp
    GraphUtils.h
    LChain.h
    MovingMean.h
    Node.h
    PQueue.cpp
    PQueue.h
    RandomGraphGenerator.cpp
    RandomGraphGenerator.h
    StopWatch.cpp
    StopWatch.h
    Utils.cpp
    Utils.h)

add_library (pqs ${SOURCE_FILES})
target_include_directories (pqs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(ssp ssp.cpp)
add_executable(graphgen graphgen.cpp)
target_link_libraries (ssp LINK_PUBLIC pqs)
target_link_libraries (graphgen LINK_PUBLIC pqs)
