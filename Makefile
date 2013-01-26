###########################################################################
# Makefile for hamming encode/decode programs
#
#   $Id: Makefile,v 1.2 2007/07/16 02:10:24 michael Exp $
#   $Log: Makefile,v $
#   Revision 1.2  2007/07/16 02:10:24  michael
#   Use -pedantic option when compiling.
#
#   Revision 1.1.1.1  2005/01/02 05:06:45  michael
#   Initial version
#
############################################################################

CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Wextra -pedantic -ansi -c
LDFLAGS = -O3 -o

# libraries
LIBS = -L. -lhamming

# Treat NT and non-NT windows the same
ifeq ($(OS),Windows_NT)
	OS = Windows
endif

ifeq ($(OS),Windows)
	EXE = .exe
	DEL = del
else	#assume Linux/Unix
	EXE =
	DEL = rm
endif

all:		testall$(EXE)

testall$(EXE):	testall.o libhamming.a
		$(LD) $< $(LIBS) $(LDFLAGS) $@

testall.o:	testall.c hamming.h
		$(CC) $(CFLAGS) $<

libhamming.a:	hamming.o
		ar crv $@ $<
		ranlib $@

hamming.o:	hamming.c hamming.h
		$(CC) $(CFLAGS) $<

clean:
		$(DEL) *.o
		$(DEL) *.a
		$(DEL) testall$(EXE)
