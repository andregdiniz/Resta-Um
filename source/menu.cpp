/*
    Kleyton Leite

    Implementar cabecalho do menu

    on 17/05/2019

*/

#include "menu.h"



void RenderString(float x, float y, void *font, std::string texto)
{  
	glRasterPos2f(x, y);
	for ( int i = 0; i < texto.size(); ++i ) {
		glutBitmapCharacter(font, texto[i]);
		//glutStrokeCharacter(font, texto[i]);
		}
}

void posicoes_pinos()
{
	glPushMatrix();
	
	glColor3f(0,0,0);
	glTranslatef(0,0,-3.2);

	glPushMatrix();

	RenderString(-2.5, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
		"L1");
	glTranslatef(0,0,1);
	RenderString(-2.5, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"L2");
	glTranslatef(0,0,1.2);
	RenderString(-5.3, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"L3");
	glTranslatef(0,0,1.1);
	RenderString(-5.3, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"L4");
	glTranslatef(0,0,1.1);
	RenderString(-5.3, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"L5");
	glTranslatef(0,0,1.1);
	RenderString(-2.5, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"L6");
	glTranslatef(0,0,1.1);
	RenderString(-2.5, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"L7");

	glPopMatrix();

	glTranslatef(0,0,-3.2);
	glPushMatrix();
	glTranslatef(0,0,4.3);
	RenderString(-4, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
		"C1");
	RenderString(-3, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"C2");
	glTranslatef(0,0,-2);
	RenderString(-1.5, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"C3");
	RenderString(-0.3, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"C4");
	RenderString(1, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"C5");
	glTranslatef(0,0,2);
	RenderString(2.5, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"C6");
	RenderString(3.8, 0, GLUT_BITMAP_TIMES_ROMAN_24, 
	"C7");
	glPopMatrix();
	glPopMatrix();
}