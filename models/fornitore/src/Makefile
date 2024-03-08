#IDIR=../hdr
IDIR=.
ODIR=../obj
BDIR=../bin

CC=g++
# Aggiungi -I$(IDIR) per includere la directory corrente e qualsiasi altra directory specificata in IDIR
# -lpq e -lm sono aggiunti alle LDFLAGS invece che alle CFLAGS perché sono necessari per il linking, non per la compilazione
CFLAGS=-std=c++20 -I$(IDIR) -I/usr/include/postgresql
LDFLAGS=-lpq -lm -lhiredis # Aggiungi le librerie necessarie per il linking qui

DEPS = $(wildcard $(IDIR)/*.h)
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,$(ODIR)/%.o,$(SRC))

con2db_OBJ=$(wildcard ../../../con2db/*.o)
con2redis_OBJ=$(wildcard ../../../con2redis/obj/*.o)
test_OBJ=$(wildcard ../../../test/obj/*.o)

# Aggiorna il target 'all' per costruire l'eseguibile specificando il target corretto
all: con2db con2redis test $(BDIR)/main

con2db:
	$(MAKE) -C ../../../con2db

con2redis:
	$(MAKE) -C ../../../con2redis/src

test:
	$(MAKE) -C ../../../test/src

# Utilizza le CFLAGS per la compilazione e specifica le directory degli header
$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Utilizza $(LDFLAGS) per il processo di linkaggio per includere le librerie necessarie
$(BDIR)/main: $(OBJ) $(con2db_OBJ) $(con2redis_OBJ) $(test_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ core 
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
