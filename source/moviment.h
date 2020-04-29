/*
    Kleyton Leite

    Implementar cabecalho da organização e dos movimentos das peçaçs do resta um

    on 07/05/2019

*/


#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>

#include "pin.h"

class Movimento
{
    protected:
        std::vector < std::vector < short int > > pins_comuns;
        std::vector<Pin>::iterator buraco;
        std::vector<Pin>::iterator pino_sel;
    private:
        std::string textura;
        std::vector<Pin> pinos;

        short int linha, coluna;

    public:
        Movimento();
        ~Movimento();
        //carrega os modelos em cada pino
        void load_models_pins();
        //define as posições dos pinos
        void positions_pins();
        //carrega a textura nos pinos,
        //caminho desejado
        void load_texture(std::string filename);
        //Recarrega textura padrao
        void textura_padrao();
        //renderiza os pinos
        void render_pins();
        //carrega os vertices vizinhos no grafo de
        //pinos
        void gerar_grafo();
	    bool seleciona_pin(short int x, short int y,  
        std::string);
        bool seleciona_buraco(short int x, short int y);
        int obter_ID(std::vector<Pin>::iterator);
        //pino vizinho que precisa ser apagado
        bool pino_comum(int posicao, int buraco);
        bool pino_del();

};

#endif