CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: clean

../assemble: assemble.o linked_list.o map.o util.o io.o tokenizer.o branch.o data_processing.o single_data_transfer.o special.o multiply.o
	$(CC) $(CFLAGS) -o $@ $^

assemble.o: definitions.h linked_list.h map.h util.h io.h tokenizer.h

branch.o: branch.h definitions.h map.h

data_processing.o: data_processing.h definitions.h util.h

io.o: io.h definitions.h linked_list.h map.h util.h

linked_list.o: definitions.h linked_list.h

map.o: map.h definitions.h

multiply.o: definitions.h util.h multiply.h

single_data_transfer.o: single_data_transfer.h data_processing.h linked_list.h

special.o: definitions.h data_processing.h special.h

tokenizer.o: tokenizer.h map.h linked_list.h

util.o: util.h definitions.h data_processing.h branch.h multiply.h single_data_transfer.h special.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
