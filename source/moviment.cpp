/*
    Kleyton Leite

    Implementar funções cabecalho da organização e dos movimentos das peças do resta um

    on 07/05/2019

*/

#define TRANSLATION 0010

#include "moviment.h"

Movimento::Movimento()
{
    load_models_pins();
    positions_pins();
}

Movimento::~Movimento()
{
    pinos.clear();
    pins_comuns.clear();
}

//carregar apenas uma vez
void Movimento::load_models_pins()
{
    pinos.clear();
    for(int i = 0; i < 33; i++)
    {
        Pin aux("../modelo/pino_modelagem.obj", true);
        if(i==23)
            aux.disable();
        pinos.push_back(aux);
    }

}

/*
    ATENCAO: Cada pino depende da posição
        do anterior
*/
void Movimento::positions_pins()
{
    pinos[0].set_translation(-1.35, 1,0);
    pinos[0].set_linha_coluna(4,3);
    pinos[1].set_translation(-1.35, 0,0);    
    pinos[1].set_linha_coluna(4,2);
    pinos[2].set_translation(-1.35, 0,0);
    pinos[2].set_linha_coluna(4, 1);

    pinos[3].set_translation(0, 0, 1.1);
    pinos[3].set_linha_coluna(5, 1);
    pinos[4].set_translation(1.35, 0,0);
    pinos[4].set_linha_coluna(5,2);
    pinos[5].set_translation(1.35, 0,0);
    pinos[5].set_linha_coluna(5,3);
    pinos[6].set_translation(1.35, 0,0);
    pinos[6].set_linha_coluna(5,4);
    pinos[7].set_translation(1.35, 0,0);
    pinos[7].set_linha_coluna(5,5);
    pinos[8].set_translation(1.35, 0,0);
    pinos[8].set_linha_coluna(5,6);
    pinos[9].set_translation(1.35, 0,0);
    pinos[9].set_linha_coluna(5,7);
    
    //CORRIGIDO
    pinos[10].set_translation(0, 0, -2.20);
    pinos[10].set_linha_coluna(3,7);
    pinos[11].set_translation(-1.35, 0,0);    
    pinos[11].set_linha_coluna(3,6);
    pinos[12].set_translation(-1.35, 0,0);
    pinos[12].set_linha_coluna(3,5);
    pinos[13].set_translation(-1.35, 0, 0);
    pinos[13].set_linha_coluna(3,4);
    pinos[14].set_translation(-1.35, 0,0);
    pinos[14].set_linha_coluna(3,3);
    pinos[15].set_translation(-1.35, 0,0);
    pinos[15].set_linha_coluna(3,2);
    pinos[16].set_translation(-1.35, 0,0);
    pinos[16].set_linha_coluna(3,1);
    //CORRIGIDO
    pinos[17].set_translation(2.7, 0,-1.1);
    pinos[17].set_linha_coluna(2,3);
    pinos[18].set_translation(1.35, 0,0);
    pinos[18].set_linha_coluna(2,4);
    pinos[19].set_translation(1.35, 0,0);
    pinos[19].set_linha_coluna(2,5);
    
    pinos[20].set_translation(0, 0,-1.1);
    pinos[20].set_linha_coluna(1,5);
    pinos[21].set_translation(-1.35, 0,0);    
    pinos[21].set_linha_coluna(1,4);
    pinos[22].set_translation(-1.35, 0,0);
    pinos[22].set_linha_coluna(1,3);
    //CORRIGIDO
    pinos[23].set_translation(1.35, 0, 3.3);
    pinos[23].set_linha_coluna(4,4);
    pinos[24].set_translation(1.35, 0,0);
    pinos[24].set_linha_coluna(4,5);
    pinos[25].set_translation(1.35, 0,0);
    pinos[25].set_linha_coluna(4,6);
    pinos[26].set_translation(1.35, 0,0);
    pinos[26].set_linha_coluna(4,7);
    //CORRIGIDO
    pinos[27].set_translation(-2.7, 0,2.25);
    pinos[27].set_linha_coluna(6,5);
    pinos[28].set_translation(-1.35, 0,0);
    pinos[28].set_linha_coluna(6,4);
    pinos[29].set_translation(-1.35, 0,0);
    pinos[29].set_linha_coluna(6,3);
    //CORRIGIDO
    pinos[30].set_translation(0, 0,1.1);
    pinos[30].set_linha_coluna(7,3);
    pinos[31].set_translation(1.35, 0,0);
    pinos[31].set_linha_coluna(7,4);
    pinos[32].set_translation(1.35, 0,0);
    pinos[32].set_linha_coluna(7,5);
}

void Movimento::load_texture(std::string filename)
{ 
    textura = filename;
    for(int i = 0; i < 33; i++)
    {
        pinos[i].carregar_textura(filename);
    }
}

void Movimento::textura_padrao()
{
    load_texture(textura);
}

void Movimento::render_pins()
{
    glPushMatrix();
    for(int i =0; i < 33; i++)
    {
        pinos[i].renderw(TRANSLATION);
    }
    glPopMatrix();
}

void Movimento::gerar_grafo()
{
    for(int i =0; i<33;i++)
    {
        std::vector < short int > comp;
        if(i == 0)
        {
            comp.push_back(14);
            comp.push_back(1);
            comp.push_back(5);
            comp.push_back(23);
        }
        else if(i == 1)
        {
            comp.push_back(15);
            comp.push_back(2);
            comp.push_back(4);
            comp.push_back(0);
        }
        else if(i == 2)
        {
            comp.push_back(16);
            comp.push_back(3);
            comp.push_back(1);
        }
        else if(i == 3)
        {
            comp.push_back(2);
            comp.push_back(4);
        }
        else if(i == 4)
        {
            comp.push_back(1);
            comp.push_back(3);
            comp.push_back(5);
        }
        else if(i == 5)
        {
            comp.push_back(0);
            comp.push_back(4);
            comp.push_back(29);
            comp.push_back(6);
        }
        else if(i == 6)
        {
            comp.push_back(23);
            comp.push_back(5);
            comp.push_back(28);
            comp.push_back(7);
        }
        else if(i == 7)
        {
            comp.push_back(24);
            comp.push_back(6);
            comp.push_back(27);
            comp.push_back(8);
        }
        else if(i == 8)
        {
            comp.push_back(25);
            comp.push_back(7);
            comp.push_back(9);
        }
        else if(i == 9)
        {
            comp.push_back(26);
            comp.push_back(8);
        }
        else if(i == 10)
        {
            comp.push_back(11);
            comp.push_back(26);
        }
        else if(i == 11)
        {
            comp.push_back(12);
            comp.push_back(25);
            comp.push_back(10);
        }
        else if(i == 12)
        {
            comp.push_back(19);
            comp.push_back(13);
            comp.push_back(24);
            comp.push_back(11);
        }
        else if(i == 13)
        {
            comp.push_back(18);
            comp.push_back(14);
            comp.push_back(23);
            comp.push_back(12);
        }
        else if(i == 14)
        {
            comp.push_back(17);
            comp.push_back(15);
            comp.push_back(0);
            comp.push_back(13);
        }
        else if(i == 15)
        {
            comp.push_back(16);
            comp.push_back(1);
            comp.push_back(14);
        }
        else if(i == 16)
        {
            comp.push_back(2);
            comp.push_back(15);
        }
        else if(i == 17)
        {
            comp.push_back(22);
            comp.push_back(14);
            comp.push_back(18);
        }
        else if(i == 18)
        {
            comp.push_back(21);
            comp.push_back(17);
            comp.push_back(13);
            comp.push_back(19);
        }
        else if(i == 19)
        {
            comp.push_back(20);
            comp.push_back(18);
            comp.push_back(12);
        }
        else if(i == 20)
        {
            comp.push_back(21);
            comp.push_back(19);
        }
        else if(i == 21)
        {
            comp.push_back(22);
            comp.push_back(18);
            comp.push_back(19);
        }
        else if(i == 22)
        {
            comp.push_back(17);
            comp.push_back(21);
        }
        else if(i == 23)
        {
            comp.push_back(13);
            comp.push_back(0);
            comp.push_back(6);
            comp.push_back(24);
        }
        else if(i == 24)
        {
            comp.push_back(12);
            comp.push_back(23);
            comp.push_back(7);
            comp.push_back(25);
        }
        else if(i == 25)
        {
            comp.push_back(11);
            comp.push_back(24);
            comp.push_back(8);
            comp.push_back(26);
        }
        else if(i == 26)
        {
            comp.push_back(10);
            comp.push_back(25);
            comp.push_back(9);
        }
        else if(i == 27)
        {
            comp.push_back(7);
            comp.push_back(28);
            comp.push_back(32);
        }
        else if(i == 28)
        {
            comp.push_back(6);
            comp.push_back(29);
            comp.push_back(31);
            comp.push_back(27);
        }
        else if(i == 29)
        {
            comp.push_back(5);
            comp.push_back(30);
            comp.push_back(28);
        }
        else if(i == 30)
        {
            comp.push_back(29);
            comp.push_back(31);
        }
        else if(i == 31)
        {
            comp.push_back(28);
            comp.push_back(30);
            comp.push_back(32);
        }
        else if(i == 32)
        {
            comp.push_back(27);
            comp.push_back(31);
        }

        pins_comuns.push_back(comp);
    }

}

bool Movimento::seleciona_pin(short int x, short int y,
    std::string new_texture)
{
    
    linha = x;
    coluna = y;

    Pin aux;
    aux.set_linha_coluna(x,y);

    pino_sel = std::find(pinos.begin(), pinos.end(), aux);

    //mudar textura do objeto selecionados
    if(pino_sel != pinos.end())
    {
        pino_sel->carregar_textura(new_texture);//textura diferente das demais
        return true;
    }
    else
    {
        return false;
    }

}

bool Movimento::seleciona_buraco(short int x, short int y)
{
    linha = x;
    coluna = y;

    Pin aux;
    aux.set_linha_coluna(x,y);

    buraco = std::find(pinos.begin(), pinos.end(), aux);

    //mudar textura do objeto selecionados
    if(buraco != pinos.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Movimento::obter_ID(std::vector<Pin>::iterator search)
{
    for(int i =0; i < 33; i++)
    {
        if(pinos[i].get_coluna() == search->get_coluna())
            if(pinos[i].get_linha() == search->get_linha())
                return i;
    }
    return -1;
}

//exclui o pino comum
bool Movimento::pino_comum(int pino, int buraco_ID)
{
    if(buraco->get_coluna() == pino_sel->get_coluna())
    {
        for(int i = 0; i < 4; i++){
            if(pins_comuns[pino][i] != buraco_ID) 
            {
                if(pinos[pins_comuns[pino][i]].get_coluna() == 
                        pino_sel->get_coluna())
                        {
                            pinos[pins_comuns[pino][i]].disable();
                            return true;
                        }
            }
        }
    }
    if(buraco->get_linha() == pino_sel->get_linha())
    {
        for(int i = 0; i < 4; i++){
            if(pins_comuns[pino][i] != buraco_ID) 
            {
                if(pinos[pins_comuns[pino][i]].get_linha() == 
                        pino_sel->get_linha())
                        {
                            pinos[pins_comuns[pino][i]].disable();
                            return true;
                        }
            }
        }
    }
    return false;

}

bool Movimento::pino_del(){

    short int pino = obter_ID(pino_sel);
    short int buraco_ID = obter_ID(buraco);
    if(pins_comuns[pino].size()> 2)
    {
        std::vector< short int >::iterator area;
        area = std::find(pins_comuns[pino].begin(), 
            pins_comuns[pino].end(), buraco_ID);
        if (area == pins_comuns[pino].end())
        {
           std::cout << "Buraco Invalido\n";
           return false;
        }

        if(pino_comum(pino, buraco_ID))
        {
            pino_sel->disable();
            buraco->enable();
            return true;
        }
        else
        {
            return false;
        }
        

    }
    return false;
}