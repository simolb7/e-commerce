# TecnoMarket

Backend per un sito di e-commerce, sviluppato per il corso "Software engineering"

## Table of Contents

1. [Introduzione](#introduzione)
2. [Installazione e configurazione](#installazione)
3. [Utilizzo](#utilizzo)
4. [Contribuire](#contribuire)
5. [Licenza](#licenza)

## Introduzione
È stato sviluppato un backend per un sito di e-commerce. Ogni attore del sistema avrà un proprio terminale separato e con funzioni dedicate al proprio scopo, la comunicazione fra processi è gestita tramite stream **redis**, che permettono ai vari attori in esecuzione di rimanere in ascolto ed eventualmente scrivere. I dati sono memorizzati in un database tramite **Postgres**.

Per informazioni più dettagliate si consiglia la lettura della relazione del progetto.

## Pre-requisiti

È richiesta la presenza delle librerie:

* hiredis
* libpq


## Installazione e configurazione

Una volta clonata la repo di github, è possibile compilare tutto il codice in automatico eseguendo lo script *make.sh*. È possibile comunque compilare a mano.
Prima di effettuare qualsiasi make, controllare nelle cartelle la presenza della cartella obj oltre ad src:
* con2redis
* hash
* test

Controllare la presenza delle cartelle obj ed bin, oltre ad src, nelle seguente cartelle:
* utente
* costumer
* fornitore
* trasportatore

Per compilare tutto il progetto, inserirsi all'interno della cartella del progetto:

```
cd Documents/Github/e-commerce
./make.sh
```

In alternativa, sarà obbligatorio compilare singolarmente i vari main:
```
cd e-commerce/models/utente/src
make clean
make

cd e-commerce/models/costumer/src
make clean
make

cd e-commerce/models/fornitore/src
make clean
make

cd e-commerce/models/trasportatore/src
make clean
make
```

Una volta compilato il codice, bisogna avviare il server redis e il db.
Per avviare il server redis bisogna lanciare su un terminale apposito (che non va chiuso):

```
redis-server
```

Per avviare il db, bisogna posizionarsi all'interno della cartella db-scripts, presente all'interno del progetto, ed eseguire singolarmente nell'ordine in cui sono presentati i seguenti comandi:

```
cd db-scripts

sudo -u postgres psql postgres -f parameters.sql -f create-db-user.sql  -f schema.sql  -f grant.sql
//crea il database
```

Se si vuole entrare all'interno del database per vedere i dati dopo l'esecuzione del programma bisogna runnare i seguenti comandi ed eseguire le query a proprio piacimento:

```
sudo -i -u postgres

psql

\c ecommercedb //si connette al db creato
```

## Utilizzo
> **DISCLAIMER**: se si vuole disabilitare la generazione dei prodotti da parte del fornitore nel db, modificare la variabile DEBUG con il valore 0.

Una volta compilato tutto il codice, avviato il server redis ed eseguita la creazione del db, si potrà procedere con l'avvio delle varie interfacce. Basterà eseguire in diversi terminali i seguenti codici:

Il modello **utente** è utilizzato per rappresentare un utente che ancora deve essere autenticato (previa registrazione o login).

```
cd e-commerce/models/utente/bin
./main
```

Il modello **fornitore** è utilizzato per rappresentare un fornitore tipico del sistema, una volta avviato si connetterà in automatico alle stream redis. Rimane in ascolto sullo stream in attesa di nuovi ordini, una volta ricevuto, si occuperà di assegnarlo al trasportatore scelto.

```
cd e-commerce/models/fornitore/bin
./main
```

Il modello **trasportatore** è utilizzato per rappresentare un trasportatore tipico del sistema, una volta avviato si connetterà in automatico alle stream redis. Nelle stream si occuperà di apprendere quali ordini gli sono stati assegnati e lavorarli, aggiornandone lo stato.

```
cd e-commerce/models/trasportatore/bin
./main
```

Il modello **costumer** è utilizzato per rappresentare un utente autenticato, si connette alle stream redis predisposte, che gli permettono di inoltrare un ordine al fornitore corrispondente, e di ricevere informazioni sullo stato degli ordini effettuati.

```
cd e-commerce/models/costumer/bin
./main
```
