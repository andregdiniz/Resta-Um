/*
    Kleyton Leite

    Implementar cabecalho do menu

    on 17/05/2019

*/

#ifndef MENU_H
#define MENU_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string>
#include <iostream>
#include <locale.h>

#include "base.h"
#include "cam.h"
#include "pin.h"
#include "moviment.h"

    void criar_menu();
    void RenderString(float x, float y, void *font, 
    std::string texto);
    void  posicoes_pinos();

    void sobre(int id);

#endif