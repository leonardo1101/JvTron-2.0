/*
    JvAdventure: Trabalho 2
    Departamento de Computação
    UFSCar Universidade Federal de São Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        João Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523

    Controle de Versão: https://github.com/leonardo1101/JvTron
*/
#ifndef Renderiza_H
#define Renderiza_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Renderiza{
    public:
        void reset();
        void desenha(sf::Sprite& ,sf::Sprite &,sf::RenderWindow & App );
        
    private:
        int cont;
};
void Renderiza::reset(){
    cont=0;
}
void Renderiza::desenha(sf::Sprite & um , sf::Sprite & dois, sf::RenderWindow & App){
    if(cont == 0)
        App.draw(um);
    else
        App.draw(dois);
    
    if(cont >= 1)
        cont=0;
    else
        cont++;
};
#endif
