/*
    André Gomes Diniz

    On 03/05/2019

    Implementação do cabecalho pin.cpp

*/


#include "pin.h"

Pin::Pin(std::string nomeArquivo){
    carregar_objeto(nomeArquivo);
}

Pin::Pin(std::string nomeArquivo, bool activate){
    carregar_objeto(nomeArquivo);
    this->flag = activate;
}

void Pin::set_models(std::string nomeArquivo,
                             bool activate)
{

    carregar_objeto(nomeArquivo);
    this->flag = activate;
}

void Pin::set_translation(GLfloat x, GLfloat y, GLfloat z)
{
    translacao.clear();
    translacao.push_back(x);
    translacao.push_back(y);
    translacao.push_back(z);
}
   
void Pin::set_rotation(GLfloat graus, GLfloat x, GLfloat y, GLfloat  z)
{
    rotacao.clear();
    rotacao.push_back(graus);
    rotacao.push_back(x);
    rotacao.push_back(y);
    rotacao.push_back(z);
}

void Pin::set_translation(std::vector<GLfloat> vetor)
{
    translacao.clear();
    std::vector<GLfloat>::iterator it = translacao.begin();
    translacao.insert(it, vetor.begin(), vetor.end());
}

void Pin::set_rotation(std::vector<GLfloat> vetor)
{
    translacao.clear();
    std::vector<GLfloat>::iterator it = rotacao.begin();
    rotacao.insert(it, vetor.begin(), vetor.end());
}

/*
    flags:
        0001: rotacao
        0010: translacao
*/
void Pin::renderw(short int flag)
{
    glCallList(list);
    if(flag == 0001)
        glRotatef(rotacao[0], rotacao[1], rotacao[2], rotacao[3]);
    if(flag == 0010)
        glTranslatef(translacao[0], translacao[1], translacao[2]);
    else
    {
        glRotatef(rotacao[0], rotacao[1], rotacao[2], rotacao[3]);
        glTranslatef(translacao[0], translacao[1], translacao[2]);
    }
    
	if(this->flag)
        render();
    //glPopMatrix();
}

void Pin::set_linha_coluna(short int x, short int y)
{
    linha = x;
    coluna = y;
}

short int Pin::get_linha()
{
    return linha;
}

short int Pin::get_coluna()
{
    return coluna;
}

bool Pin::operator==(Pin comp)
{
    return (this->linha == comp.linha &&
         this->coluna == comp.coluna);
}

void Pin::enable()
{
    this->flag = true;
}

void Pin::disable()
{
    this->flag = false;
}

bool Pin::status()
{
    return this->flag;
}