CC = gcc

test: multitable_tests.o multitable.o
	$(CC) -o tests.out multitable_tests.o multitable.o hashset.o vector.o

clean:
	rm -f multitable_tests.o multitable.o tests.out