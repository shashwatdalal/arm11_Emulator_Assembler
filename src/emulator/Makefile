CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: clean

../emulate: emulate.o pipeline.o branch.o multiply.o data_processing.o single_data_transfer.o io.o util.o
	$(CC) $(CFLAGS) -o $@ $^

emulate.o: pipeline.h

pipeline.o: pipeline.h branch.h multiply.h data_processing.h single_data_transfer.h

branch.o: branch.h io.h

multiply.o: multiply.h io.h

data_processing.o: data_processing.h io.h

single_data_transfer.o: single_data_transfer.h io.h

io.o: io.h definitions.h util.h

util.o: util.h

clean:
	rm -f $(wildcard *.o)
	rm -f emulate
