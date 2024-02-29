#include <main.h>

void Costumer::ricerca(char const * nomeOg, int quantita, string result[30][4], Con2DB db1){
    PGresult *res;
    char sqlcmd[1000];
    int idOgg;
    int row;

    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idO FROM Oggetto WHERE (nameO = \'%s\')", nomeOg);
    res = db1.ExecSQLtuples(sqlcmd);
    idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idInv, prezzo, QuantitaAtt, fornitore FROM Inventario WHERE (oggetto = \'%d\' AND QuantitaAtt >= \'%d\')", idOgg, quantita);
    res = db1.ExecSQLtuples(sqlcmd);
    row = PQntuples(res);
    for (int i = 0; i < row; i++){
        char * idInv = PQgetvalue(res, i, PQfnumber(res, "idInv"));
        char * prezzo = PQgetvalue(res, i, PQfnumber(res, "prezzo"));
        char * quantitaAtt = PQgetvalue(res, i, PQfnumber(res, "QuantitaAtt"));
        char * fornitore = PQgetvalue(res, i, PQfnumber(res, "fornitore"));

        result[i][0] = idInv;
        result[i][1] = prezzo;
        result[i][2] = quantitaAtt;
        result[i][3] = fornitore;
    };

    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};
