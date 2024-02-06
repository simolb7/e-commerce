#pragma once
#include <main.h>
#include <fornitore.h>

void Oggetto::addOggetto(Oggetto oggetto1, Con2DB db1){
    char const *nomeA = oggetto1.getNomeO();
    char const *descrizioneA = oggetto1.getDescrizioneO();
    char const *barCodeA = oggetto1.getBarCodeO();
    char const *categoriaA = oggetto1.getCategoriaO();
    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "INSERT INTO Categoria VALUES (DEFAULT, \'%s\') ON CONFLICT DO NOTHING", categoriaA);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "INSERT INTO Oggetto VALUES (DEFAULT, \'%s\', \'%s\', \'%s\', 1) ON CONFLICT DO NOTHING", nomeA, descrizioneA, barCodeA);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};