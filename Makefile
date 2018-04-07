CC = g++
CFLAGS=-g


all: difmain.o diffunc.o difparserfunc.o  
	g++ $(CFLAGS) -o difp.exe difmain.o  diffunc.o difparserfunc.o -static
difmain.o: difmain.c 
	g++ $(CFLAGS) -c difmain.c
diffunc.o: diffunc.c 
	g++ $(CFLAGS) -c diffunc.c
diffparserfunc: difparserfunc.c 
	g++ $(CFLAGS) -c difparserfunc.c

