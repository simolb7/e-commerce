#!/bin/bash

cd con2redis/src/
make clean
make
cd ../..
cd hash/src
make clean
make
cd ../..
cd test/src
make clean
make
cd ../..
cd models/utente/src/
make clean
make
cd ../..
cd fornitore/src/
make clean
make 
cd ../..
cd trasportatore/src/
make clean
make
cd ../..
cd costumer/src/
make clean
make
