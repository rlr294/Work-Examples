CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -c $(DEBUG)
LFLAGS = -Wall -std=c99 $(DEBUG)

Sim05 : Sim05.o Structures.o Parser.o Process.o SimpleTimer.o
	$(CC) $(LFLAGS) Sim05.o Structures.o Parser.o Process.o  SimpleTimer.o -lpthread -o Sim05

Sim05.o : Sim05.c Sim05.h Structures.h Parser.h Process.h SimpleTimer.h
	$(CC) $(CFLAGS) Sim05.c

Structures.o : Structures.c Structures.h
	$(CC) $(CFLAGS) Structures.c

Parser.o : Parser.c Parser.h
	$(CC) $(CFLAGS) Parser.c

Process.o : Process.c Process.h
	$(CC) $(CFLAGS) Process.c

SimpleTimer.o : SimpleTimer.c SimpleTimer.h
	$(CC) $(CFLAGS) SimpleTimer.c

clean:
	\rm *.o Sim05
