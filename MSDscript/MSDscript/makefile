CXX=c++
CXXSOURCE= main.cpp cmdline.cpp expr.cpp
CXXFLAGS= --std=c++14 -O2
HEADERS=cmdline.hpp expr.hpp catch.h
OBJS=main.o cmdline.o expr.o

msdscript:$(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)
main.o:main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
cmdline.o:cmdline.cpp cmdline.hpp catch.h
	$(CXX) $(CXXFLAGS) -c cmdline.cpp
expr.o:expr.cpp expr.hpp catch.h
	$(CXX) $(CXXFLAGS) -c expr.cpp

clean:
	rm -f *.o msdscript.out

.PHONY:clean
	
doc: msdscript
	cd documentation && doxygen
