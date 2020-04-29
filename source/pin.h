/*
    André Gomes Diniz

    On 03/05/2019

    Cabeçalho dos pinos: pin.h

*/

#ifndef PIN_H
#define PIN_H

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <string>

#include "obj.h"

class Pin :  public cObj
{
    private:
        std::vector<GLfloat> translacao;
        std::vector<GLfloat> rotacao;
        short int linha = -1;
        short int coluna = -1;
        bool flag = true;        
    public:
        Pin(){};
        Pin(std::string nomeArquivo);
        Pin(std::string nomeArquivo, 
                            bool activate);
        void set_models(std::string nomeArquivo,
                            bool activate);
        void set_translation(GLfloat x, GLfloat y, GLfloat z);
        void set_rotation(GLfloat graus, GLfloat x, GLfloat y, GLfloat  z);
        void set_translation(std::vector<GLfloat> vetor);
        void set_rotation(std::vector<GLfloat> vetor);
        void renderw(short int flag);
        void set_linha_coluna(short int x, short int y);
        short int get_linha();
        short int get_coluna();
        bool operator==(Pin comp);
        void enable();
        void disable();
        bool status();
};


#endif