#IDIR=../hdr
IDIR=.
ODIR=../obj
BDIR=../bin

CC=g++
# Aggiungi -I$(IDIR) per includere la directory corrente e qualsiasi altra directory specificata in IDIR
# -lpq e -lm sono aggiunti alle LDFLAGS invece che alle CFLAGS perché sono necessari per il linking, non per la compilazione
CFLAGS=-std=c++20 -I$(IDIR) -I/usr/include/postgresql
LDFLAGS=-lpq -lm -lhiredis -lssl -lcrypto# Aggiungi le librerie necessarie per il linking qui

DEPS = $(wildcard $(IDIR)/*.h)
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,$(ODIR)/%.o,$(SRC))

con2db_OBJ=$(wildcard ../../../con2db/*.o)
test_OBJ=$(wildcard ../../../test/obj/*.o)
hashsalt_OBJ=$(wildcard ../../../hash/obj/*.o)

# Aggiorna il target 'all' per costruire l'eseguibile specificando il target corretto
all: con2db test hash $(BDIR)/main

con2db:
	$(MAKE) -C ../../../con2db

test:
	$(MAKE) -C ../../../test/src

hash:
	$(MAKE) -C ../../../hash/src

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/main: $(OBJ) $(con2db_OBJ) $(test_OBJ) $(hashsalt_OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ core 
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
