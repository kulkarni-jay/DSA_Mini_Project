project: test.o math.o
	cc test.o math.o -o project
test.o: test.c
	cc -c test.c -Wall
math.o: math.c
	cc -c math.c 
clean: 
	rm *.o
