CC=gcc
OUT=assertive
DEPS=assertive.h
OBJ=assertive.o test/pass_test.o test/fail_test.o test/main.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $<

test: $(OUT)
	$(OUT) $(TEST)

$(OUT): $(OBJ)
	$(CC) $^ -o $(OUT)

libassertive.a: assertive.o
	ar rcs libassertive.a $<

tags:
	ctags -f .tags *.c *.h

clean:
	rm -f *.o test/*.o *.a $(OUT)
