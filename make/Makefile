#
# Author: Giacomo Benincasa     (giacomo@cise.ufl.edu)
#

include Makefile.inc

%.o : ../%.cpp
	$(cpp) -c $(cppflags) $<

%.o : ../test/%.cpp
	$(cpp) -c $(cppflags) $<

all: $(exec)

$(library).a: $(objects)
	ar -rcv $(library).a $(objects)

$(exec): $(library).a
	$(cpp) $(cppflags) $(ld_flags) \
	../main.cpp \
	$(library).a \
	-o $(exec)

log: $(library).a
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT $(ld_flags) \
	../main.cpp \
	$(library).a \
	-o $(exec)-log

DArrayTest:  $(library).a 
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT $(ld_flags) \
	$(test_dir)/DArrayTest.cpp \
	$(library).a \
	-o DArrayTest

BHeapTest:  $(library).a 
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT $(ld_flags) \
	$(test_dir)/BHeapTest.cpp \
	$(library).a \
	-o BHeapTest

GraphReaderTest:  $(library).a 
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT $(ld_flags) \
	$(test_dir)/GraphReaderTest.cpp \
	$(library).a \
	-o GraphReaderTest

GraphTest:  $(library).a 
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT $(ld_flags) \
	$(test_dir)/GraphTest.cpp \
	$(library).a \
	-o GraphTest

GraphGeneratorTest:  $(library).a 
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT $(ld_flags) \
	$(test_dir)/GraphGeneratorTest.cpp \
	$(library).a \
	-o GraphGeneratorTest

SimplePQTest:  $(library).a 
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT $(ld_flags) \
	$(test_dir)/SimplePQTest.cpp \
	$(library).a \
	-o SimplePQTest

BHeapPQTest:  $(library).a 
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT -DUSE_BINOMIAL_HEAP $(ld_flags) \
	$(test_dir)/HeapPQTest.cpp \
	$(library).a \
	-o BHeapPQTest

FHeapPQTest:  $(library).a 
	$(cpp) $(cppflags) -DENABLE_DBG_OUTPUT -DUSE_FIBONACCI_HEAP $(ld_flags) \
	$(test_dir)/HeapPQTest.cpp \
	$(library).a \
	-o FHeapPQTest

tests: $(tests)

clean:
	rm -rf *.o $(library).a $(exec) $(exec)-log $(tests)
