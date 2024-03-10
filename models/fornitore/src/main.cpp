#include <main.h>
#include <fornitore.h>
#include <../../../test/src/test.h>

#define READ_STREAM "customer2fornitore"
#define WRITE_STREAM "fornitore2trasportatore"
#define DEBUG 0




int main(){
    redisContext *c2r;
    redisReply *reply;

    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");


    int pid;
    char const *username = "fornitore";
    char const *fval;
    char const *key = "key fornitore";
    char value[] = "Nuovo spedizione assegnata";
    PGresult *res;
    char sqlcmd[1000];
    int idf;

    const char *name;
    const char *cognome;
    const char *email;
    const char *password;
    const char *purchType;

    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "SELECT idF FROM Fornitore");
    res = db.ExecSQLtuples(sqlcmd);
    idf = atoi(PQgetvalue(res, 0, PQfnumber(res, "idF")));
    PQclear(res);


    sprintf(sqlcmd, "SELECT * FROM Utente WHERE idU = \'%d\'", idf);
    res = db.ExecSQLtuples(sqlcmd);
    name = PQgetvalue(res, 0, PQfnumber(res, "nameU"));
    cognome = PQgetvalue(res, 0, PQfnumber(res, "surnameU"));
    email = PQgetvalue(res, 0, PQfnumber(res, "emailU"));
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    Fornitore fornitore(name, cognome, email);

    

#if (DEBUG > 0)

srand(time(nullptr)); // Inizializza il generatore di numeri casuali

    int numProd = 10; 


    cout << "Aggiunta "<< numProd << " prodotti -->" << endl << endl;
    for (int i = 0; i < numProd; ++i) {
        int checkErr= (rand() %2);
        int checkAdd = (rand() %3);
        const char *nomeOgg = generateRandomObjName().c_str();
        const char *descrizioneOgg = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
        const char* barCodeOgg = generateRandomBarCode().c_str();
        char const *categoriaOgg = "Elettronica";
        float price = generatePrice();
        int quantity = (rand() %10)+40;
        Oggetto oggetto(nomeOgg, descrizioneOgg, barCodeOgg, categoriaOgg);
        if(checkErr == 0){
            oggetto.addOggetto(oggetto, db);
        }
        fornitore.addInventario(oggetto, fornitore, db, price, quantity);
        if (checkAdd == 1) {
            int quantityAdded = (rand() %100)+1;
            fornitore.addQuantity(oggetto, fornitore, db, quantityAdded);
        }
        
        cout << endl;
    }

    cout << "----------------------------------------------------------------" << endl << endl;

#endif
    
    pid = getpid();
    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, email);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, email);

    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);

    double elapsedMs= 0.0;
    double ReadElapsedMs = 0.0;

    while(1){
        fval = readMsg(c2r, reply, READ_STREAM, username, ReadElapsedMs);
        printf("result fval : %s\n", fval);
        sendMsg(c2r, reply, WRITE_STREAM, key, value, elapsedMs);
    }
    redisFree(c2r);
    
    
    return 0;
};