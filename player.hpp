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
        void setIdItem(int);
        sf::Sprite getTron();
        Animation walkingAnimationRight[4];
        Animation walkingAnimationLeft[4];
        Animation stayAnimation[4];
        Animation discAnimation;
    private:
        sf::Sprite tron;
        sf::Texture forma[8];
        int direcao;
        int nDir;
        int nEsq;
        int idItem;
    
};
void Player::setIdItem(int id){
    idItem = id;   
    
};

Player::Player(){
    int i;
    forma[0].loadFromFile("spriteProtagonista/Andando.png");
    walkingAnimationRight[0].setSpriteSheet(forma[0]);
    for(i=1;i<11;i++){
        walkingAnimationRight[0].addFrame(sf::IntRect(forma[0].getSize().x/11 * i,forma[0].getSize().y * 0,forma[0].getSize().x / 11,forma[0].getSize().y));
    }
    forma[1].loadFromFile("spriteProtagonista/Parado.png");
    stayAnimation[0].setSpriteSheet(forma[1]);
    for(i=0;i<6;i++){
        stayAnimation[0].addFrame(sf::IntRect(forma[1].getSize().x/6 * i,forma[1].getSize().y * 0,forma[1].getSize().x / 6,forma[1].getSize().y));
    }
    forma[2].loadFromFile("spriteProtagonista/AndandoEsq.png");
    walkingAnimationLeft[0].setSpriteSheet(forma[2]);
    for(i=9;i!=0;i--){
        walkingAnimationLeft[0].addFrame(sf::IntRect(forma[2].getSize().x/11 * i,forma[2].getSize().y * 0,forma[2].getSize().x / 11,forma[2].getSize().y));
    }
    forma[3].loadFromFile("spriteProtagonista/Andando0.png");
    walkingAnimationRight[1].setSpriteSheet(forma[3]);
    for(i=1;i<11;i++){
        walkingAnimationRight[1].addFrame(sf::IntRect(forma[3].getSize().x/11 * i,forma[3].getSize().y * 0,forma[3].getSize().x / 11,forma[3].getSize().y));
    }
    forma[4].loadFromFile("spriteProtagonista/AndandoEsq0.png");
    walkingAnimationLeft[1].setSpriteSheet(forma[4]);
    for(i=9;i!=0;i--){
        walkingAnimationLeft[1].addFrame(sf::IntRect(forma[4].getSize().x/11 * i,forma[4].getSize().y * 0,forma[4].getSize().x / 11,forma[4].getSize().y));
    }
    forma[5].loadFromFile("spriteProtagonista/Parado0.png");
    stayAnimation[1].setSpriteSheet(forma[5]);
    for(i=0;i<6;i++){
        stayAnimation[1].addFrame(sf::IntRect(forma[5].getSize().x/6 * i,forma[5].getSize().y * 0,forma[5].getSize().x / 6,forma[5].getSize().y));
    }
    forma[6].loadFromFile("spriteProtagonista/jogandodisco.png");
    discAnimation.setSpriteSheet(forma[6]);
    for(i=1;i<8;i++){
        discAnimation.addFrame(sf::IntRect(forma[6].getSize().x/8 * i,forma[6].getSize().y * 0,forma[6].getSize().x / 8,forma[6].getSize().y));
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
