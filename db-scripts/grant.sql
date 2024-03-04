
\c :dbname postgres

-- user already exists
GRANT ALL PRIVILEGES ON DATABASE :dbname to :username ;


--ALTER TABLE TimeVar OWNER TO :username ;
--ALTER TABLE LogTable OWNER TO :username ;
ALTER TABLE Utente OWNER TO :username ;
ALTER TABLE Costumer OWNER TO :username ;
ALTER TABLE Fornitore OWNER TO :username ;
ALTER TABLE Trasportatore OWNER TO :username ;
ALTER TABLE MetPag OWNER TO :username ;
ALTER TABLE MPUte OWNER TO :username ;
ALTER TABLE Categoria OWNER TO :username ;
ALTER TABLE Oggetto OWNER TO :username ;
ALTER TABLE Inventario OWNER TO :username ;
ALTER TABLE Acquisto OWNER TO :username ;
ALTER TABLE AcqInv OWNER TO :username ;
ALTER TABLE LogReg OWNER TO :username ;
ALTER TABLE LogLogin OWNER TO :username ;
ALTER TABLE LogAggiunta OWNER TO :username ;
ALTER TABLE LogSender OWNER TO :username;
ALTER TABLE LogReader OWNER TO :username;


-- grant all privileges on all tables in schema public to :username ;
-- grant all privileges on all sequences in schema public to :username ;

GRANT ALL ON SCHEMA public TO :username ;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO :username ;
