#include <main.h>
#include <fornitore.h>

void Fornitore::addQuantity(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1, int aggiunta){
    char const *emailF = fornitore1.getEmail();
    char const *BarCodeOg = oggetto1.getBarCodeO();
    int idFor;
    int idOgg;
    int qAtt;
    int idInv;
    int pid;
    char const *controllo;
    char const *t = "t";
    PGresult *res;
    char sqlcmd[1000];

    pid = getpid();

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idU FROM Utente WHERE (emailU = \'%s\')", emailF);
    res = db1.ExecSQLtuples(sqlcmd);
    idFor = atoi(PQgetvalue(res, 0, PQfnumber(res, "idU")));
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idO FROM Oggetto WHERE (CBar = \'%s\')", BarCodeOg);
    res = db1.ExecSQLtuples(sqlcmd);
    idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idInv, quantitaatt FROM Inventario WHERE (Fornitore = \'%d\' AND Oggetto = \'%d\')", idFor, idOgg);
    res = db1.ExecSQLtuples(sqlcmd);
    idInv = atoi(PQgetvalue(res, 0, PQfnumber(res, "idInv")));
    qAtt = atoi(PQgetvalue(res, 0, PQfnumber(res, "quantitaatt")));
    PQclear(res);

    qAtt += aggiunta;
    sprintf(sqlcmd,
    "UPDATE Inventario SET quantitaatt = \'%d\' WHERE (Fornitore = \'%d\' AND Oggetto = \'%d\')", qAtt, idFor, idOgg);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "INSERT INTO LogAggiunta VALUES (DEFAULT, now(), \'%d\', \'%d\', '%d\') ON CONFLICT DO NOTHING", pid, idInv, aggiunta);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};