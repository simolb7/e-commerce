#pragma once
#include <../../../con2db/pgsql.h>

class Oggetto{
    private:
        char const *nomeO;
        char const *descrizioneO;
        char const *barCodeO;
        char const *categoriaO;
    
    public:
        Oggetto(char const *nome, char const *descrizione, char const *barCode, char const *categoria) : 
        nomeO(nome), descrizioneO(descrizione), barCodeO(barCode), categoriaO(categoria) {}

        char const * getNomeO(){
            return nomeO;
        }

        char const * getDescrizioneO(){
            return descrizioneO;
        }

        char const * getBarCodeO(){
            return barCodeO;
        }

        char const * getCategoriaO(){
            return categoriaO;
        }

        void addOggetto(Oggetto oggetto1, Con2DB db1);
};