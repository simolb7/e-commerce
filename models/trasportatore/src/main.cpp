#include <main.h>

#define READ_STREAM "fornitore2trasportatore"
#define WRITE_STREAM "trasportatore2costumer"

int main(){
    
    redisContext *c2r;
    redisReply *reply;

    int pid;
    char const *key = "key Trasportatore";
    char const *value = "Stato spedizione: ";
    char const *username = "trasportatore@gmail.com";
    char const *fval;
    char *statusAtt;
    char const *statusConsegnato = "consegnato";
    int ordini[10]; //da rivedere
    PGresult *res;
    char sqlcmd[1000];
    int idt;

    // Connessione al database PostgreSQL
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Recupero id del trasportatore
    sprintf(sqlcmd, "SELECT idt FROM trasportatore");
    res = db.ExecSQLtuples(sqlcmd);
    idt = atoi(PQgetvalue(res, 0, PQfnumber(res, "idt")));
    PQclear(res);

    // Recupero delle informazioni sul trasportatore dal database
    sprintf(sqlcmd, "SELECT * FROM Utente WHERE idU = \'%d\'", idt);
    res = db.ExecSQLtuples(sqlcmd);
    char const *name = PQgetvalue(res, 0, PQfnumber(res, "nameU"));
    char const *surname = PQgetvalue(res, 0, PQfnumber(res, "surnameU"));
    char const *email = PQgetvalue(res, 0, PQfnumber(res, "emailU"));
    PQclear(res);

    // Chiudo la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Inizializzazione dell'oggetto Trasportatore
    Trasportatore trasportatore(name, surname, email);
    string emailCopy(email);
    
    // Connessione al server redis
    pid = getpid();
    cout << "main(): pid " << pid << ": user " << emailCopy << ": connecting to redis..." << endl;
    c2r = redisConnect("localhost", 6379);
    cout << "main(): pid " << pid << ": user " << emailCopy << ": connected to redis" << endl;

    // Inizializzazione dei canali di lettura e scrittura per la comunicazione con Redis
    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);

    double ReadElapsedMs = 0.0;

    while(1){

        // Lettura dei messaggi dal server Redis
        fval = readMsg(c2r, reply, READ_STREAM, username, ReadElapsedMs);
        
        for (int i = 0; i < 10; ++i) {
            ordini[i] = -1; // Utilizzando -1 come valore speciale
        }

        // Recupero degli ordini
        trasportatore.getOrders(idt, db, ordini);

        double elasedMs= 0.0;
        

        for (int i = 0; i < 10; i++) {
            if (ordini[i] != -1){
                // Verifica dello stato attuale dell'ordine
                const char *check = trasportatore.getStatus(ordini[i], db);
                if (strcmp(check, statusConsegnato) != 0){
                    // Se l'ordine non è ancora consegnato, aggiorna lo stato e invia le notifiche
                    statusAtt = trasportatore.getStatus(ordini[i], db);
                    cout << "Stato corrente: \n\t" << statusAtt << endl;

                    // Invio della notifica al canale Redis
                    char newValue1[100];
                    strcpy(newValue1, value);
                    strcat(newValue1, statusAtt);
                    sendMsg(c2r, reply, WRITE_STREAM, key, newValue1, elasedMs);
                    sleep(5);

                    // Aggiornamento dello stato dell'ordine nel database
                    trasportatore.updateStatus(ordini[i], db);
                    statusAtt = trasportatore.getStatus(ordini[i], db);
                    cout << "Stato corrente: \n\tin preparazione -> "<< statusAtt << endl;

                    // Invio della notifica al canale Redis
                    char newValue2[100];
                    strcpy(newValue2, value);
                    strcat(newValue2, statusAtt);
                    sendMsg(c2r, reply, WRITE_STREAM, key, newValue2, elasedMs);
                    sleep(5);

                    // Aggiornamento dello stato dell'ordine nel database
                    trasportatore.updateStatus(ordini[i], db);
                    statusAtt = trasportatore.getStatus(ordini[i], db);
                    cout << "Stato corrente: \n\tspedito -> "<< statusAtt << endl;
                    // Invio della notifica al canale Redis
                    char newValue3[100];
                    strcpy(newValue3, value);
                    strcat(newValue3, statusAtt);
                    sendMsg(c2r, reply, WRITE_STREAM, key, newValue3, elasedMs);
                }
            } else {
                break;
            }
        }
    }

    // Chiusura della connessione al server Redis
    redisFree(c2r);
    return 0;
    
}