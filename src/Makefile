CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -I../include
INCLUDES=-I ../include
.PHONY: clean

BUILD=TRUE
STATIC=FALSE

ifeq ($(BUILD),TRUE)
	CFLAGS += $(-02)
	ifeq ($(STATIC),TRUE)
		CFLAGS += -static-libgcc
		CFLAGS += -static-libstdc++
		CFLAGS += -Wl,-Bstatic,--whole-archive
		CFLAGS += -lwinpthread
		CFLAGS += -Wl,--no-whole-archive
	endif
endif


default: astronomer

astronomer: cli.o elements.o parseMap.o main.o parseMap.o StarMap.o
	$(CC) $(CFLAGS) -o astronomer cli.o elements.o main.o parseMap.o StarMap.o

cli.o: cli.cpp ../include/cli.h ../include/StarMap.h StarMap.o
	$(CC) $(CFLAGS) -c cli.cpp

elements.o: elements.cpp ../include/elements.h
	$(CC) $(CFLAGS) -c elements.cpp

parseMap.o: parseMap.cpp ../include/elements.h
	$(CC) $(CFLAGS) -c parseMap.cpp

StarMap.o: ../include/elements.h ../include/parseMap.h ../include/StarMap.h StarMap.cpp
	$(CC) $(CFLAGS) -c StarMap.cpp

main.o: main.cpp ../include/StarMap.h ../include/cli.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) *.o astronomer
