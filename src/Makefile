.PHONY: all clean

all:
	+$(MAKE) -C assembler
	+$(MAKE) -C emulator
	+$(MAKE) -C tron

clean:
	rm -f assemble
	rm -f emulate
	rm -f tron
	rm -rf $(wildcard *.o)
