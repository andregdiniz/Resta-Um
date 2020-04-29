/*
    Kleyton leite

    On 2/05/2019

    Implementação do cabeçalho cam.h

*/

#include "cam.h"

Cam::Cam(){};

void Cam::Inicializa()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Cam::setPerspective()
{

}

void Cam::setIlumination()
{



	// Capacidade de brilho do material

	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 

	GLint especMaterial = 100;



	// Define a refletância do material 

	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

	// Define a concentração do brilho

	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);



	// Ativa o uso da luz ambiente 


    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambientLight[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[]  = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[]      = { 0.0f, 0.0f, -15.0f, 1.0f };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void Cam::setCamera()
{
    glMatrixMode(GL_MODELVIEW);
    gluLookAt( 0.0, 0.0, 15.0,
    0.0, 0.0, 0.0, 
    0.0, 1.0, 0.0 );

}

//Espaço para visão padrão do tabuleiro
void Cam::visao()
{

    if (height == 0)
    height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0,    width, 0.9*height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    width >= height?
	glOrtho(-1*ortho * aspect, ortho * aspect, -1*ortho, ortho, -20.0, 100) :
    glOrtho(-1*ortho, ortho, -1*ortho / aspect, ortho / aspect, -20.0, 100);
	//gluPerspective(15, aspect, 20, 50);
}

//Prepara espaço para impressão do texto
void Cam::visao_texto()
{

    if (height == 0)
    height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0.9*height, width, 0.1*height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    width >= height?
    gluOrtho2D(-1*ortho_txt * aspect, ortho_txt * aspect, -1*ortho_txt, ortho_txt) :
    gluOrtho2D(-1*ortho_txt, ortho_txt, -1*ortho_txt / aspect, ortho_txt / aspect);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glLineWidth(3);
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(2,2);
		glVertex2f(-2,2);
		glVertex2f(-2,-2);
		glVertex2f(2,-2);
	glEnd();

}


void Cam::set_altura(GLsizei height)
{
	this->height = height;
}

void Cam::set_largura(GLsizei width)
{
	this->width = width;
}

void Cam::set_ortho(int tam)
{
	this->ortho = tam;
}

void Cam::set_ortho_txt(int tam)
{
	this->ortho_txt = tam;
}

Cam::~Cam(){}