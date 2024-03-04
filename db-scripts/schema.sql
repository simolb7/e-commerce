
-- database already exists

\c :dbname 


-- Pick the one most appropriate for your application
-- CREATE DOMAIN TimePoint AS date ;
create domain TimePoint as timestamp ;
-- create domain TimePoint as timestamp with time zone;

CREATE DOMAIN  StringS AS VARCHAR(30) ;
CREATE DOMAIN  StringM as VARCHAR(200) ;
CREATE DOMAIN  StringL as VARCHAR(1000) ;
CREATE DOMAIN PIva as VARCHAR(11);
CREATE DOMAIN BarCode as VARCHAR(20);
CREATE DOMAIN IntG0 as INTEGER CHECK (VALUE > 0);
CREATE DOMAIN IntGE0 as INTEGER CHECK (VALUE >= 0);
CREATE DOMAIN saltDomain as VARCHAR(16);
CREATE DOMAIN hashedPsw as VARCHAR(64);

-- Pick the one most appropriate for your application
--CREATE DOMAIN VarType AS real ;
create domain VarType as double precision ;
-- create domain VarType as int ;


CREATE TYPE DomainType AS ENUM ('discrete', 'real', 'double');
CREATE TYPE LogType AS ENUM ('info', 'warn', 'error');
CREATE TYPE UserType AS ENUM ('customer', 'fornitore', 'trasportatore');
CREATE TYPE StatusSpedition AS ENUM ('in preparazione', 'spedito', 'consegnato');

/*
-- Patient data that depend on time
-- Variables within time series (all have the same type)
CREATE TABLE IF NOT EXISTS TimeVar (
        vid serial PRIMARY KEY,     -- serial id for variable
        pid int NOT NULL,           -- pid of process logged
        sysname StringM,            --- system containing logged variable
        varname StringS NOT NULL,     -- variable name
        vardomain DomainType NOT NULL,
        varinfo StringM NOT NULL
);

-- Timescaledb extension for time series
-- Do not forget to create timescaledb extension
-- CREATE EXTENSION timescaledb;

CREATE TABLE IF NOT EXISTS LogTable (
        nanosec bigint NOT NULL,		-- nanseconds after second
        vid int NOT NULL,			-- variable id
        varvalue VarType,                       -- variable value
	loginfo StringM,                        -- extra info
        PRIMARY KEY (nanosec, vid),
        CONSTRAINT vid_ref FOREIGN KEY(vid) REFERENCES TimeVar(vid)
);
*/

CREATE TABLE IF NOT EXISTS Utente (
        idU serial PRIMARY KEY,
        nameU StringS,
        surnameU StringS,
        emailU StringM UNIQUE,
        passwordU hashedPsw,
        salt saltDomain
);

CREATE TABLE IF NOT EXISTS Costumer (
        idC int UNIQUE NOT NULL,
        CONSTRAINT idC_ref FOREIGN KEY(idC) REFERENCES Utente(idU)
);

CREATE TABLE IF NOT EXISTS Fornitore (
        idF int UNIQUE NOT NULL,
        PIvaF PIva,
        CONSTRAINT idF_ref FOREIGN KEY(idF) REFERENCES Utente(idU)
);

CREATE TABLE IF NOT EXISTS Trasportatore (
        idT int UNIQUE NOT NULL,
        azienda StringM,
        CONSTRAINT idT_ref FOREIGN KEY(idT) REFERENCES Utente(idU)
);

CREATE TABLE IF NOT EXISTS MetPag (
        idMP serial PRIMARY KEY,
        nameMP StringM UNIQUE
);

CREATE TABLE IF NOT EXISTS MPUte (
        costumer int NOT NULL,
        metpag int NOT NULL,
        CONSTRAINT costumer_ref1 FOREIGN KEY(costumer) REFERENCES Costumer(idC),
        CONSTRAINT metpag_ref FOREIGN KEY(metpag) REFERENCES MetPag(idMP)
);

CREATE TABLE IF NOT EXISTS Categoria (
        idCat serial PRIMARY KEY,
        nameCat StringS UNIQUE
);

CREATE TABLE IF NOT EXISTS Oggetto (
        idO serial PRIMARY KEY,
        nameO StringS,
        descr StringL,
        CBar BarCode UNIQUE,
        category int NOT NULL,
        CONSTRAINT cat_ref FOREIGN KEY(category) REFERENCES Categoria(idCat)
);
CREATE TABLE IF NOT EXISTS Inventario (
        idInv serial PRIMARY KEY,
        prezzo real,
        QuantitaS IntG0,
        QuantitaAtt IntGE0,
        istante TIMESTAMP,
        fornitore int NOT NULL,
        oggetto int NOT NULL,
        CONSTRAINT fornitore_ref FOREIGN KEY(fornitore) REFERENCES Fornitore(idF),
        CONSTRAINT oggetto_ref FOREIGN KEY(oggetto) REFERENCES Oggetto(idO),
        UNIQUE (fornitore, oggetto)
);

CREATE TABLE IF NOT EXISTS Acquisto (
        idAcq serial PRIMARY KEY,
        statusAcq StatusSpedition,
        istante TIMESTAMP,
        costumer int NOT NULL,
        trasportatore int NOT NULL,
        CONSTRAINT costumer_ref FOREIGN KEY(costumer) REFERENCES Costumer(idC),
        CONSTRAINT trasportatore_ref FOREIGN KEY(trasportatore) REFERENCES Trasportatore(idT)
);

CREATE TABLE IF NOT EXISTS AcqInv (
        inventario int NOT NULL,
        acquisto int NOT NULL,
        quantity IntG0,
        CONSTRAINT inventario_ref FOREIGN KEY(inventario) REFERENCES Inventario(idInv),
        CONSTRAINT acquisto_ref FOREIGN KEY(acquisto) REFERENCES Acquisto(idAcq)
);

CREATE TABLE IF NOT EXISTS LogReg (
        idLR serial PRIMARY KEY,
        istante TIMESTAMP,
        logSeverity LogType,
        pid int NOT NULL,
        emailU StringM,
        ruolo UserType
);

CREATE TABLE IF NOT EXISTS LogLogin (
        idLL serial PRIMARY KEY,
        istante TIMESTAMP,
        logSeverity LogType,
        pid int NOT NULL,
        emailU StringM
);

CREATE TABLE IF NOT EXISTS LogAggiunta (
        idLA serial PRIMARY KEY,
        istante TIMESTAMP,
        pid int NOT NULL,
        inventario int NOT NULL,
        agginv IntG0,
        CONSTRAINT inventario_ref2 FOREIGN KEY(inventario) REFERENCES Inventario(idInv)
);

CREATE TABLE IF NOT EXISTS LogSender (
        idLS serial PRIMARY KEY,
        istante TIMESTAMP,
        pid int NOT NULL,
        sender int NOT NULL,
        receiver int NOT NULL,
        elapsed StringM NOT NULL,
        CONSTRAINT sender_ref FOREIGN KEY(sender) REFERENCES Utente(idU),
        CONSTRAINT receiver_ref FOREIGN KEY(receiver) REFERENCES Utente(idU)
);

CREATE TABLE IF NOT EXISTS LogReader(
        idLRD serial PRIMARY KEY,
        istante TIMESTAMP,
        pid int NOT NULL,
        reader int NOT NULL,
        elapsed StringM NOT NULL,
        CONSTRAINT reader_ref FOREIGN KEY(reader) REFERENCES Utente(idU)
);








