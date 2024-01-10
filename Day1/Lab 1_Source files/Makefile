#
# target entry to build program executable from main.out
# Caps.o Clothing.o Pants.o are the object files
# Target is used to be a file, and if it doesn't exist
# or its timestamp is later than any of its dependencies,
# it will be remaded.
#
CXXSOURCE = main.cpp Caps.cpp Clothing.cpp Pants.cpp
HEADERS = Caps.h Clothing.h Pants.h
OBJS= main.o Caps.o Clothing.o Pants.o

main.out:main.o Caps.o Clothing.o Pants.o
	g++ -o main.out main.o Caps.o Clothing.o Pants.o
main.o:main.cpp
	g++ -c main.cpp
Caps.o:Caps.cpp Caps.h
	g++ -c Caps.cpp
Clothing.o:Clothing.cpp Clothing.h
	g++ -c Clothing.cpp
Pants.o:Pants.cpp Pants.h
	g++ -c Pants.cpp

clean:
	rm -f *.o main.out
	
printM:
	@echo $(CXXSOURCE)
	
.PHONY: clean
#clean:
#	@echo Clean...
#    rm *.o

