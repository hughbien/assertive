CC=gcc
OUT=assertive
DEPS=assertive.h
OBJ=assertive.o example_pass_test.o example_fail_test.o example_test.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $<

test: $(OUT)
	$(OUT)

$(OUT): $(OBJ)
	$(CC) $^ -o $(OUT)

libassertive.a: assertive.o
	ar rcs libassertive.a $<

tags:
	ctags -f .tags *.c *.h

clean:
	rm -f *.o *.a $(OUT)
