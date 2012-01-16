CC=gcc
DEPS=assertive.h
OBJ=assertive.o example_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

test: a.out
	a.out

a.out: $(OBJ)
	$(CC) $^

tags:
	ctags -f .tags *.c *.h

clean:
	rm -f *.o a.out
