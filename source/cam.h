/*
    Kleyton Leite

    On 27/04/2019

    Cabeçalho dos objetos: cam.h
*/

#ifndef CAM_H
#define CAM_H

#include <GL/glut.h>
#include <string>

class Cam
{
    
    private:
        GLsizei height;
        GLsizei width;
        int ortho;
        int ortho_txt;

    public:

    Cam();

    void Inicializa();

    void setPerspective();

    void setIlumination();

    void setCamera();

    void visao();

    void visao_texto();


    void set_altura(GLsizei height);

    void set_largura(GLsizei weight);

    void set_ortho(int tam);

    void set_ortho_txt(int tam);

    ~Cam();
};

#endif