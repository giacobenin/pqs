#
# Author: Giacomo Benincasa	(giacomo@cise.ufl.edu)
#

cpp = g++
includes = -I.. -I../test

#cppflags = -g -fPIC -Wall -Wextra -Wno-unused-parameter -DUNIX -DLINUX -DL_ENDIAN -DENABLE_DBG_OUTPUT $(includes)
cppflags = -g -fPIC -Wall -Wextra -Wno-unused-parameter -DUNIX -DLINUX -DL_ENDIAN $(includes)

sources = $(wildcard ../*.cpp)
objects = $(sources:../%.cpp=%.o)

testsources = $(wildcard ../test/*.cpp)
testobjects = $(sources:../test/%.cpp=%.o

library=ads
exec=ssp

test_dir=../test
tests=DArrayTest BHeapTest GraphReaderTest GraphTest GraphGeneratorTest SimplePQTest BHeapPQTest FHeapPQTest
