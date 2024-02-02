#include <main.h>
#include <fornitore.h>

int main(){

    int pid;
    unsigned seed;

    #if (DEBUG > 0)
        setvbuf(stdout, (char*) NULL, _IONBF, 0);
        setvbuf(stderr, (char*) NULL, _IONBF, 0);
    #endif

    seed = (unsigned) time(NULL);
    srand(seed);

    pid = getpid();

    char const *nomeOgg = "Monitor LG";
    char const *descrizioneOgg = "grandi palle, bel pisello";
    char const *barCodeOgg = "12345678900987654321";
    char const *categoriaOgg = "Elettronica";

    char const *name = "Marco";
    char const *surname = "Rossi";
    char const *email = "marcorossi69@gmail.com";
    char const *password = "redigotham";
    char const *purchType = "Carta di credito";
    char const *ruolo = "Costumer";

    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    Oggetto oggetto(nomeOgg, descrizioneOgg, barCodeOgg, categoriaOgg);

    oggetto.addOggetto(oggetto, db);

    Fornitore fornitore(name, surname, email, password, purchType);

    fornitore.addInventario(oggetto, fornitore, db);

    return 0;
};