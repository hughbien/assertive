CC=gcc
DEPS=assertive.h
OBJ=assertive.o example_test.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $<

test: a.out
	a.out

a.out: $(OBJ)
	$(CC) $^

libassertive.a: assertive.o
	ar rcs libassertive.a $<

tags:
	ctags -f .tags *.c *.h

clean:
	rm -f *.o *.a a.out
