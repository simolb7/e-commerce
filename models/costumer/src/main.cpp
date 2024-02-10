#include <main.h>

int main(){
    //char const *nomeOgg = "Mouse Logitech";
    char const *nomeOgg = "Monitor LG";
    char const *descrizioneOgg = "grandi palle, bel pisello";
    char const *barCodeOgg = "12345678900987654321";
    //char const *barCodeOgg = "12345678900987654322";
    char const *categoriaOgg = "Elettronica";

    char const *name = "Luigi";
    char const *surname = "Verdi";
    char const *email = "luigiverdi420@gmail.com";
    char const *password = "forzapergolettese";
    char const *purchType = "Carta di credito";
    char const *ruolo = "Costumer";

    char * lista[10][4];

    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    Costumer costumer(name, surname, email, password, purchType);

    costumer.ricerca(nomeOgg, 5, lista, db);

    
    cout << lista[0][0] << endl;
    cout << lista[0][1] << endl;
    cout << lista[0][2] << endl;
    cout << lista[0][3] << endl;

    costumer.acquisto(lista[0][0], costumer, 3, db);


    return 0;
};