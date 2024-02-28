#include <main.h>
#include <fornitore.h>

#define READ_STREAM "customer2fornitore"
#define WRITE_STREAM "fornitore2trasportatore"
#define DEBUG 1000


// Funzione per generare un nome casuale
string generateRandomObjName() {
    vector<string> objNames = {"Mouse", "Monitor", "Tastiera", "Cuffie", "Alimentatore", "Televisore"};
    return objNames[rand() % objNames.size()];
}

// Funzione per generare un cognome casuale
string generateRandomBarCode() {
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 9);

    std::string number;
    for (int i = 0; i < 13; ++i) {
        number += std::to_string(distribution(generator));
    }

    return number;

}

string generateEmail(const char *nome, const char *cognome) { 
    string nomes = nome;
    string surnames = cognome;
    int num = rand() %100;
    string nums = to_string(num);
    string email = nomes + surnames + nums + "@gmail.com";
    return email;
}


float generatePrice(){
    int num = rand() %300;
    float numf = static_cast<float>(num) + 0.99f;
    return numf;
}

int main(){
    redisContext *c2r;
    redisReply *reply;

    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");


    int pid;
    char const *username = "fornitore@gmail.com";;
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
    password = PQgetvalue(res, 0, PQfnumber(res, "passwordU"));
    purchType = "PayPal";
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    Fornitore fornitore(name, cognome, email, password, purchType);

    srand(time(nullptr)); // Inizializza il generatore di numeri casuali

    int numPeople = 5; // Numero di persone da generare

    cout << "Generated Products:\n";
    for (int i = 0; i < numPeople; ++i) {
        const char *nomeOgg = generateRandomObjName().c_str();
        const char *descrizioneOgg = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
        const char* barCodeOgg = generateRandomBarCode().c_str();
        char const *categoriaOgg = "Elettronica";
        float price = generatePrice();
        int quantity = (rand() %20)+1;
        cout << nomeOgg << endl;
        cout << barCodeOgg << endl;
        Oggetto oggetto(nomeOgg, descrizioneOgg, barCodeOgg, categoriaOgg);
        oggetto.addOggetto(oggetto, db);
        fornitore.addInventario(oggetto, fornitore, db, price, quantity);
        fornitore.addQuantity(oggetto, fornitore, db, 10);
    }

#if (DEBUG > 0)
    printf("Prova");

#endif
    /*
    pid = getpid();
    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, username);

    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);

    fval = readMsg(c2r, reply, READ_STREAM, username);
    printf("result fval : %s\n", fval);
    sendMsg(c2r, reply, WRITE_STREAM, key, value);

    redisFree(c2r);
    
    */
    return 0;
};