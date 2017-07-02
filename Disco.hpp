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
        bool Bateu(AnimatedSprite &sprite);
        //posicao do disco
        sf::Vector2f getPosicao();
        bool gravidadeTrocar;
        void fakeGravidade(sf::Vector2f gravidade);
        sf::Sprite desenho;
    private:
        sf::Vector2f ponto;
        sf::Vector2f vetor;
        float escalar;
        float outroEscalar;
        sf::Texture img;
};
void Disco::fakeGravidade(sf::Vector2f gravidade){
        desenho.setPosition(sf::Vector2f(desenho.getPosition().x,gravidade.y - 110));//coloca o heroi na posicao
};
sf::Vector2f Disco::getPosicao(){
    return desenho.getPosition();
};
void Disco::mover( bool aumentar, int direcao, bool pulando){
    if(!aumentar){
            if(vetor.x == 1){
                escalar=7.0f;
                if(pulando)
                    escalar=12.0f;
            }else{
                escalar= - 7.0f;
                if(pulando)
                    escalar= - 12.0f;
            }
    }else{
        if(vetor.x == 1){
            if(direcao == 1){
                escalar=7.0f;
                if(pulando)
                    escalar=8.0f;
            }else{
                escalar=9.0f; 
                if(pulando)
                    escalar=12.0f;
            }
        }else{
            if(direcao == 1){
                escalar= - 9.0f;
                if(pulando)
                    escalar= - 12.0f;
            }else{
                escalar= - 7.0f;
                if(pulando)
                    escalar= - 8.0f;
            }
        }
    }
            desenho.move(sf::Vector2f(escalar,0));
    
};
sf::Sprite Disco::getDisco(){
    return desenho;
};
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
