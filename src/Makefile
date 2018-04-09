CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -O2
INCL = -I ../include
IP = ../include
.PHONY: clean

DIST=FALSE

ifeq ($(DIST),TRUE) # chang DIST to TRUE to build a static library to distribute on Windows
	CXXFLAGS += -static-libgcc
	CXXFLAGS += -static-libstdc++
	CXXFLAGS += -Wl,-Bstatic,--whole-archive
	CXXFLAGS += -lwinpthread
	CXXFLAGS += -Wl,--no-whole-archive
endif


default: astronomer

astronomer: cli.o elements.o parseMap.o main.o parseMap.o StarMap.o
	$(CXX) $(CXXFLAGS) $(INCL) -o astronomer cli.o elements.o main.o parseMap.o StarMap.o

cli.o: cli.cpp $(IP)/cli.h $(IP)/StarMap.h StarMap.o
	$(CXX) $(CXXFLAGS) $(INCL) -c cli.cpp

elements.o: elements.cpp $(IP)/elements.h
	$(CXX) $(CXXFLAGS) $(INCL) -c elements.cpp

parseMap.o: parseMap.cpp $(IP)/elements.h
	$(CXX) $(CXXFLAGS) $(INCL) -c parseMap.cpp

StarMap.o: $(IP)/elements.h $(IP)/parseMap.h $(IP)/StarMap.h StarMap.cpp
	$(CXX) $(CXXFLAGS) $(INCL) -c StarMap.cpp

main.o: main.cpp $(IP)/StarMap.h $(IP)/cli.h
	$(CXX) $(CXXFLAGS) $(INCL) -c main.cpp

clean:
	$(RM) *.o astronomer
