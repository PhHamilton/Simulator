CC = g++
CFLAGS = -g -w -Wall

test_unit: test_unit.o util.o
	$(CC) $(CFLAGS) test_unit.o util.o -o test_unit

output: main.o util.o
	$(CC) $(CFLAGS) main.o util.o -o output

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

util.o: util.h util.c
	$(CC) $(CFLAGS) -c util.c 

clean: 
	rm *.o output 
