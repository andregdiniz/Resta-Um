/*
    Kleyton Leite

    Exercicio solicitado, para desenvolver a aplicação resta um

    on 27/04/2019

    make -f makefile

    **Os pinos tem raio 0.45 e tem a distancia de 1.35 entre os buracos no tabuleiro**

*/

#include "menu.h"

#define TITLEWINDOW "Resta Um"
#define positionX 100
#define positionY 100

#define TRANSLATION 0010

int ID_WINDOW;

short int witdh = 1000;
short int height = 1000;

short int angulox  = 90;
short int anguloy  = 0;
short int anguloz  = 0;

//CABECALHOS DE FUNCAO
void glutInit(int *argc, char **argv);
void Reshap(int width, int heigh);
GLfloat* obj_vertex();
GLfloat* obj_normal();
void draw();
void keyboard(unsigned char key, int x, int y);
void principal(int op);
void arquivo(int id);
void selecionar(int id);
void movimento(int id);
void menu_inicial();

//flags para encontrar os pinos e buracos
bool pinox = false;
bool pinoy = false;
bool buracox = false;
bool buracoy = false;
short int xi, yi;
bool sucesso = false;
bool menui = true;
bool selecao[2] = {0,0};


//carrega modelagem do fundo
    Base fundo("../modelo/fundo.obj");
//carrega modelagem da mesa
	Base mesa("../modelo/base_modelagem.obj");
	//carrega modelagem dos pinos
	//inicializa configurações de visualização
	Cam camera;
	//Define os pinos, suas texturas e posições
	Movimento mov;
	//Mensagem
	std::string msg = "Trabalho Final: Resta Um";

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH| GLUT_STENCIL); 
    glutInitWindowSize(witdh, height);
    glutInitWindowPosition(positionX, positionY);
    ID_WINDOW = glutCreateWindow(TITLEWINDOW);
    menu_inicial();
   
        criar_menu();
        mov.load_texture("../modelo/pino.dds");
        if(sucesso)
            fundo.carregar_textura("../modelo/taca_vinho.dds");
        else
            fundo.carregar_textura("../modelo/fundo_musgo.dds");
        mesa.carregar_textura("../modelo/granito.dds");
        mov.gerar_grafo();
        msg = "O JOGO RESTA UM";
        glutReshapeFunc(Reshap);
        glutDisplayFunc(draw);
        glutKeyboardFunc(keyboard);
        if(!sucesso)
        camera.Inicializa();
    //camera.setIlumination();
  
    glutReshapeFunc(Reshap);
    glutMainLoop();
    return EXIT_SUCCESS;
}

void menu_inicial(){

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1,1,1);
    glClearColor(1, 1, 1, 0.4);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    msg = "Ola";



}

void Reshap(GLsizei w, GLsizei h) {
    camera.set_altura(h);
    camera.set_largura(w);
    camera.set_ortho(9);
    camera.set_ortho_txt(2);
    camera.visao();
    //precisa carregar apenas uma vez   
    camera.setCamera();
    glutPostRedisplay();
}

void draw()
{   
    if(!sucesso)
    {
        camera.visao();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(1,1,1);
        glClearColor(1, 1, 1, 0.4);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glScalef(1.5,1.5,1);
        glRotatef(-90, 1 , 0 , 0);
        glTranslatef(0,50,0);
        fundo.render();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,15);
        glRotatef(angulox,1,0,0);
        glRotatef(anguloy, 0, 1, 0);
        glRotatef(anguloz, 0,0,1);
        glColor3f(1,1,1);
        mesa.render();
        mov.render_pins();
        mov.gerar_grafo();

        posicoes_pinos();
        glPopMatrix();

        glPushMatrix();
        //mov.render_pins();
        camera.visao_texto();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        RenderString(-1, 0, GLUT_BITMAP_9_BY_15, msg);
    }
    else
    {
        camera.visao();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(1,1,1);
        glClearColor(1, 1, 1, 0.4);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glScalef(1.5,1.5,1);
        glTranslatef(0,0,-30);
        glRotatef(-90, 1 , 0 , 0);
        fundo.render();
        glPopMatrix();

        glPushMatrix();
        camera.visao_texto();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        RenderString(-1, 0, GLUT_BITMAP_9_BY_15, "\1Parabens voce terminou!!!\nVamos Comemorar!!!\1 ");
    }
    
    camera.setIlumination();
    
    glFinish();
    glutSwapBuffers();
    
}

void keyboard(unsigned char key, int x, int y)
{

    switch(key)
    {
        //Rotação
        case 'X':
            angulox++;
            //std::cout<<angulox<<'\n';
            
            break;
        case 'Y':
            anguloy++;
            
            break;
        case 'Z':
            anguloz++;
            
            break;
        case 'x':
            angulox--;
            
            break;
        case 'y':
            anguloy--;
            
            break;
        case 'z':
            anguloz--;
            
            break;

        //controles de jogabilidade
        case 'P':
        {
            msg.clear();
            msg =  "Entre com a posicao do pino!!!";
            pinox = true;
            pinoy =true;
            break;
        }
        case 'B':
            msg.clear();
            msg = "Entre com a posicao do buraco!!!";
            buracox = true;
            buracoy = true;
            break;
        case 'Q':
            msg.clear();
            if(selecao[0] && selecao[1]){
                msg = "Pino excluido!!!";
                mov.pino_del();
            }
            else
            {
                msg = "Entre com as posições do Pino e Buraco";
            }
            
            break;

        case 'R':
            mov.load_texture("../modelo/3391.dds");

            
        //Seleção dos pinos
    }

    //Seleção das posições
    int n;
    char text[2];
    text[0] = key;
    text[1] = '\0';
    n = atoi(text);
    if(n > 0 && n<8)
    {
        if(pinox)
        {
            xi = n;
            pinox =false;
        }
        else if(pinoy)
        {
            mov.textura_padrao();
            yi = n;
            if(mov.seleciona_pin(xi, yi, "../modelo/azul_select.dds")) 
                std::cout << "OK\n";
            else
                std::cout << "Pino nao encontrado!!!\n";
            pinoy = false;
            msg.clear();
            msg = "Pino selecionado!!!";
            //controle de falaha de segmentacao
            selecao[0] = 1;
        }
        else if(buracox)
        {
            xi = n;
            buracox = false;
        }
        else if(buracoy)
        {
            yi = n;
            if(mov.seleciona_buraco(xi, yi))
                std::cout << "OK\n";
            else
            {
                std::cout << "Buraco Inválido!!!\n";
            }
            
            buracoy = false;
            msg.clear();
            msg = "Buraco selecionado!!!";
             selecao[1] = 1;
        }

    }
    glFlush();
    glutPostRedisplay();

}

void criar_menu()
{

    int menu1,submenu1,submenu2,submenu3,submenu4;

    submenu1 = glutCreateMenu(arquivo);
    glutAddMenuEntry("Carregar textura para fundo",0);
    glutAddMenuEntry("Carregar textura para base",1);
    glutAddMenuEntry("Carregar textura para pinos",2);

    submenu2 = glutCreateMenu(selecionar);
    glutAddMenuEntry("Pino (P)",0);
    glutAddMenuEntry("Buraco (B)",1);


    submenu3 = glutCreateMenu(movimento);
    glutAddMenuEntry("Retira Comum (Q)",0); 

    submenu4 = glutCreateMenu(sobre);
    glutAddMenuEntry("Motivo",0); 
    glutAddMenuEntry("Desenvolvimento",1);
	glutAddMenuEntry("Licensa",2);

    menu1 = glutCreateMenu(principal);
    glutAddSubMenu("Arquivo",submenu1);
    glutAddSubMenu("Seleção",submenu2);
    glutAddSubMenu("Movimento",submenu3);
	glutAddSubMenu("Sobre",submenu4);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void principal(int op)
{
    camera.visao_texto();
}

void arquivo(int id)
{
    glPushMatrix();

	std::string local;
    
    switch(id)
    {
        case   0:
			//imprime que deve entrar com o local da
			//no terminal - fundo
			std::cout << "Entre com os valores: \n";
            msg = "Entre com os valores no terminal!!!";
            draw();
			std::cin >> local;
			fundo.carregar_textura(local);
			break;
		case 1: 
			//imprime que deve entrar com o local da
			//no terminal - base
			std::cout << "Entre com os valores: \n";
            msg = "Entre com os valores no terminal!!!";
            draw();
			std::cin >> local;
			mesa.carregar_textura(local);
			break;
		case 2:
			//imprime que deve entrar com o local da
			//no terminal - base
			std::cout << "Entre com os valores: \n";
            msg = "Entre com os valores no terminal!!!";
            draw();
			std::cin >> local;
			mov.load_texture(local);
			break;
    }

    glPopMatrix();
    glutPostRedisplay();
}


void sobre(int id)
{
	short int x, y;
    glPushMatrix();
	switch(id)
    {
        case   0:
			//imprime que deve entrar com o local da
			//no terminal - fundo
            msg = "Veja nossa descrição no terminal!!!";
            std::cout << "Trabalho desenvolvido para aprimorar nossas capacidades no uso do opengl.\n ";
            std::cout << "Conseguimos o sucesso por conta dos materiais disponibilizados pelo Prof: Adailton José da Cruz.\n";
            std::cout << "Assim nossas capacidades de POO e engenharia de software foram usadas.";

			break;
		case 1: 
			//imprime que deve entrar com o local da
			//no terminal - base
            msg = "Equipe: Andre G. Diniz & Kleyton";
			break;
        case 2: 
			//imprime que deve entrar com o local da
			//no terminal - base
            msg = "Mozilla Public License 2.0";
			break;
    }
    glLoadIdentity();

    glPopMatrix();
    glutPostRedisplay();
} 
void selecionar(int id)
{
	short int x, y;
    glPushMatrix();
	switch(id)
    {
        case   0:
			//imprime que deve entrar com o local da
			//no terminal - fundo
			std::cout << "Entre com os valores: \n";
			std::cin >> x >> y;
            msg = "Entre com os valores no terminal!!!";
            draw();
			mov.seleciona_pin(x,y, "../modelo/azul_select.dds");

			break;
		case 1: 
			//imprime que deve entrar com o local da
			//no terminal - base
            msg = "Entre com os valores no terminal!!!";
            draw();
			std::cout << "Entre com os valores: \n";
			std::cin >> x >> y;
            mov.seleciona_buraco(x,y);
			break;
    }
    glLoadIdentity();

    glPopMatrix();
    glutPostRedisplay();
}

void movimento(int id)
{
    glPushMatrix();
	switch(id)
    {
        case   0:
            if(selecao[0]&&selecao[1])
            {
			    if(mov.pino_del())
                    std::cout << "Pino excluido!!!\n";
                else{
                    std::cout << 
                    "Sem pino comum entre buraco e pino selecionado!!!\n";
                    msg = "Sem pino comum!!!";
                }
            }
            else 
                msg = "Entre com a posicao dos pinos e buracos";
			break;
		
    }
    glLoadIdentity();

    glPopMatrix();
    glutPostRedisplay();
}
