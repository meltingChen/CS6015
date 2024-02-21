CXX=c++
CXXSOURCE= cmdline.cpp expr.cpp parse.cpp
CXXFLAGS= --std=c++14 -O2
HEADERS=cmdline.hpp expr.hpp catch.h
OBJS=main.o cmdline.o expr.o

msdscript:main.o libmsdscript.a
	$(CXX) $(CXXFLAGS) main.cpp -L./ -lmsdscript -o msdscript
	
main.o:main.cpp
	$(CXX) $(CXXFLAGS) -c -I./Headers main.cpp
	
cmdline.o:cmdline.cpp Headers/cmdline.hpp Headers/catch.h
	$(CXX) $(CXXFLAGS) -c -I./Headers cmdline.cpp
	
expr.o:expr.cpp Headers/expr.hpp Headers/catch.h
	$(CXX) $(CXXFLAGS) -c -I./Headers expr.cpp
	
parse.o:parse.cpp Headers/parse.hpp
	$(CXX) $(CXXFLAGS) -c -I./Headers parse.cpp

clean:msdscript
	rm -f *.o $(CXXSOURCE) msdscript.out

.PHONY:clean

test:msdscript
	
doc: msdscript
	cd documentation && doxygen
