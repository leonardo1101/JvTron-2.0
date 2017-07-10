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
#ifndef DISCO_H
#define DISCO_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
class Disco{
    public:
        
        //move o disco de acordo com o vetor;
        void mover( bool aumentar = false, int direcao =1 , bool pulando = false);
        int id;
        
        //pega a sprite do disco
        sf::Sprite getDisco();
        
        //faz um reset no disco colocando primeiro o ponto e depois o vetor
        void setReset(sf::Vector2f,sf::Vector2f,bool tipo);
        bool Bateu(AnimatedSprite &sprite); // verifica se bateu
        //posicao do disco
        sf::Vector2f getPosicao();
        bool gravidadeTrocar;
        void fakeGravidade(sf::Vector2f gravidade);
        sf::Sprite desenho;
    private:
        sf::Vector2f ponto; //ponto do disco
        sf::Vector2f vetor; // vetor do disco
        float escalar;  //escalar do disco
        sf::Texture img; //texture do disco
};
//gravidade no disco
void Disco::fakeGravidade(sf::Vector2f gravidade){
        desenho.setPosition(sf::Vector2f(desenho.getPosition().x,gravidade.y - 110));//coloca o heroi na posicao
};
//pega o posicao do disco
sf::Vector2f Disco::getPosicao(){
    return desenho.getPosition();
};
//move o disco
void Disco::mover( bool aumentar, int direcao, bool pulando){
    
            if(vetor.x == 1){
                escalar=10.0f;
            }else{
                escalar= - 10.0f;
            }
    
            desenho.move(sf::Vector2f(escalar,0));
    
};
sf::Sprite Disco::getDisco(){
    return desenho;
};
//verifica se o disco bateu em algo
bool Disco::Bateu(AnimatedSprite &sprite){
    sf::RectangleShape discoNormal(sf::Vector2f(getPosicao().x, getPosicao().y ));
    discoNormal.setPosition(desenho.getPosition().x  , desenho.getPosition().y );
    discoNormal.setSize(sf::Vector2f(50.f, 50.f));
    if(discoNormal.getPosition().x >= sprite.getPosition().x  && discoNormal.getPosition().x < sprite.getPosition().x + 80.f
        && discoNormal.getPosition().y >= sprite.getPosition().y  && discoNormal.getPosition().y < sprite.getPosition().y + 130.f
    )
        return true;
    return false;
}
//reset no disco
void Disco::setReset(sf::Vector2f p,sf::Vector2f v,bool tipo){
    gravidadeTrocar=false;
    if(tipo==0){
        img.loadFromFile("Itens/discoLancado.png");
    }else{
        img.loadFromFile("Itens/discoLancadoInimigo.png");
    }
    desenho.setTexture(img);
    ponto=p;
    vetor=v;
    escalar=0;
    desenho.setPosition(sf::Vector2f(ponto.x + vetor.x * escalar,ponto.y + vetor.y * escalar));
};
#endif
