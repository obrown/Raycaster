IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -pedantic -Werror -Wall -g

ODIR=obj
LDIR =../lib

LIBS=-lm `sdl-config --cflags --libs` 

_DEPS = main.h io.h display.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o io.o display.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS) ; $(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) ; gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean: ; rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
