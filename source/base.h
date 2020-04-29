/*
    Kleyton Leite

    On 28/04/2019

    Cabeçalho dos objetos: base.h

*/

#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <GL/glut.h>
#include <string>

#include "obj.h"

class Base :  public cObj
{
    public:
    Base(std::string nomeArquivo) : cObj(nomeArquivo){};
    
    void draw();
};


#endif