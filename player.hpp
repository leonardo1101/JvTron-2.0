#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"

class Player{
    public:
        Player();
        void moverDireita();
        void moverEsquerda();
        void Parado();
        void reset();
        void setTamanho(sf::Vector2f);
        void setPosicao(sf::Vector2f);
        sf::Sprite getTron();
        Animation walkingAnimationRight;
        Animation walkingAnimationLeft;
        Animation stayAnimation;
    private:
        sf::Sprite tron;
        sf::Texture forma[4];
        int direcao;
        int nDir;
        int nEsq;
        
        
    
};

Player::Player(){
    int i;
    forma[0].loadFromFile("spriteProtagonista/Andando.png");
    walkingAnimationRight.setSpriteSheet(forma[0]);
    for(i=1;i<11;i++){
        walkingAnimationRight.addFrame(sf::IntRect(forma[0].getSize().x/11 * i,forma[0].getSize().y * 0,forma[0].getSize().x / 11,forma[0].getSize().y));
    }
    forma[1].loadFromFile("spriteProtagonista/Parado.png");
    stayAnimation.setSpriteSheet(forma[1]);
    for(i=0;i<6;i++){
        stayAnimation.addFrame(sf::IntRect(forma[1].getSize().x/6 * i,forma[1].getSize().y * 0,forma[1].getSize().x / 6,forma[1].getSize().y));
    }
    forma[2].loadFromFile("spriteProtagonista/AndandoEsq.png");
    walkingAnimationLeft.setSpriteSheet(forma[2]);
    for(i=9;i!=0;i--){
        walkingAnimationLeft.addFrame(sf::IntRect(forma[2].getSize().x/11 * i,forma[2].getSize().y * 0,forma[2].getSize().x / 11,forma[2].getSize().y));
    }
    
}

void Player::setTamanho(sf::Vector2f tamanho){
    tron.setScale(tamanho);
    
}
void Player::setPosicao(sf::Vector2f posicao){
    tron.setPosition(posicao);
}
void Player::reset(){
    direcao=0;
    
}
