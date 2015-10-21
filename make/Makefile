#
# Author: Giacomo Benincasa     (giacomo@cise.ufl.edu)
#

include Makefile.inc

%.o : ../%.cpp
	$(cpp) -c $(cppflags) $<

%.o : ../test/%.cpp
	$(cpp) -c $(cppflags) $<

all: ssp graphgen

$(library).a: $(objects)
	ar -rcv $(library).a $(objects)

ssp: $(library).a
	$(cpp) $(cppflags) $(ld_flags) \
	../ssp.cpp \
	$(library).a \
	-o ssp

graphgen: $(library).a
	$(cpp) $(cppflags) $(ld_flags) \
	../graphgen.cpp \
	$(library).a \
	-o graphgen

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
	rm -rf *.o $(library).a ssp ssp-log graphgen $(tests)
