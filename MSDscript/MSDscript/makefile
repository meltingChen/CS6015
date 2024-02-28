CXX=c++
CXXFLAGS= --std=c++14 -O2
HEADERS=cmdline.hpp expr.hpp catch.h parse.hpp
OBJS=main.o cmdline.o expr.o parse.o


msdscript:$(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)
	
main.o:main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
	
cmdline.o:cmdline.cpp cmdline.hpp catch.h
	$(CXX) $(CXXFLAGS) -c  cmdline.cpp
	
expr.o:expr.cpp expr.hpp catch.h
	$(CXX) $(CXXFLAGS) -c  expr.cpp
	
parse.o:parse.cpp parse.hpp catch.h
	$(CXX) $(CXXFLAGS) -c  parse.cpp
	
.PHONY:test_msdscript
test_msdscript: exec.o test_msdscript.o
	$(CXX) $(CXXFLAGS) exec.o test_msdscript.o -o test_msdscript

test_msdscript.o: test_msdscript.cpp test_msdscript.hpp expr.hpp exec.h exec.cpp
	$(CXX) $(CXXFLAGS) -c test_msdscript.cpp

#exec.o: exec.cpp exec.h
#	$(CXX) $(CXXFLAGS) -c exec.cpp
	
clean:
	rm -f *.o msdscript.out

.PHONY:clean

test:msdscript
	
doc: msdscript
	cd documentation && doxygen
