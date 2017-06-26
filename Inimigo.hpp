#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
class Inimigo{
    public:
        AnimatedSprite animatedSprite;
        Animation walkingAnimationRight[2];
        Animation walkingAnimationLeft[2];
        Animation stayAnimationDir[2];
        Animation stayAnimationEsq[2];
        Animation ataqueAnimationDir[2];
        Animation ataqueAnimationEsq[3];     
        void setTipo(int);
        void setPosicao(sf::Vector2f);
        void atacar();
        void procurarHeroi(AnimatedSprite &,sf::Time);
        void andar(int, sf::Time);
    private:
        Animation* currentAnimation;
        sf::Texture textura[20];
        int vida;
        int tipo;
        sf::Vector2f movement;
        float speed = 2.5f;
};
void Inimigo::setPosicao(sf::Vector2f posicao){
    animatedSprite.setPosition(posicao);
};
void Inimigo::atacar(){
    movement.x=0;
    movement.y=0;
    currentAnimation = &ataqueAnimationEsq[tipo - 1];
    if(tipo == 1 ){
        animatedSprite.setFrameTime(sf::seconds(0.04));
        animatedSprite.play(*currentAnimation);
    }else{
        animatedSprite.setFrameTime(sf::seconds(0.045));
        animatedSprite.play(*currentAnimation);
    }
};

void Inimigo::setTipo(int t){
    int i;
    tipo=t;
    
    //se o inimigo for do tipo 1 ele irá utilizar o disco
    if(tipo == 1){
        
        textura[0].loadFromFile("antagonista/andandoDir.png");
        walkingAnimationRight[0].setSpriteSheet(textura[0]);
        for(i=1;i<11;i++){
            walkingAnimationRight[0].addFrame(sf::IntRect(textura[0].getSize().x/11 * i,textura[0].getSize().y * 0,textura[0].getSize().x / 11,textura[0].getSize().y));
        }
        
        textura[1].loadFromFile("antagonista/andandoEsq.png");
        walkingAnimationLeft[0].setSpriteSheet(textura[1]);
        for(i=10;i>0;i--){
            walkingAnimationLeft[0].addFrame(sf::IntRect(textura[1].getSize().x/11 * i,textura[1].getSize().y * 0,textura[1].getSize().x / 11,textura[1].getSize().y));
        }
        
        textura[2].loadFromFile("antagonista/ParadoDir.png");
        stayAnimationDir[0].setSpriteSheet(textura[2]);
        stayAnimationDir[0].addFrame(sf::IntRect(textura[2].getSize().x * 0,textura[2].getSize().y * 0,textura[2].getSize().x,textura[2].getSize().y));
        
        textura[3].loadFromFile("antagonista/ParadoEsq.png");
        stayAnimationEsq[0].setSpriteSheet(textura[3]);
        stayAnimationEsq[0].addFrame(sf::IntRect(textura[3].getSize().x * 0,textura[3].getSize().y * 0,textura[3].getSize().x,textura[3].getSize().y));
        
        textura[4].loadFromFile("antagonista/atacandoDiscoDir.png");
        ataqueAnimationDir[0].setSpriteSheet(textura[4]);
        for(i=0;i<7;i++){
            ataqueAnimationDir[0].addFrame(sf::IntRect(textura[4].getSize().x/7 * i,textura[4].getSize().y * 0,textura[4].getSize().x /7,textura[4].getSize().y));
        }
        
        textura[5].loadFromFile("antagonista/atacandoDiscoEsq.png");
        ataqueAnimationEsq[0].setSpriteSheet(textura[5]);
        for(i=6;i>=0;i--){
            ataqueAnimationEsq[0].addFrame(sf::IntRect(textura[5].getSize().x/7 * i,textura[5].getSize().y * 0,textura[5].getSize().x /7,textura[5].getSize().y));
        }
    }else{
        textura[6].loadFromFile("antagonista/andandoDir1.png");
        walkingAnimationRight[1].setSpriteSheet(textura[6]);
        for(i=1;i<11;i++){
            walkingAnimationRight[1].addFrame(sf::IntRect(textura[6].getSize().x/11 * i,textura[6].getSize().y * 0,textura[6].getSize().x / 11,textura[6].getSize().y));
        }
        
        textura[7].loadFromFile("antagonista/andandoEsq1.png");
        walkingAnimationLeft[1].setSpriteSheet(textura[7]);
        for(i=9;i>0;i--){
            walkingAnimationLeft[1].addFrame(sf::IntRect(textura[7].getSize().x/10 * i,textura[7].getSize().y * 0,textura[7].getSize().x / 10,textura[7].getSize().y));
        }
        
        textura[8].loadFromFile("antagonista/ParadoDir.png");
        stayAnimationDir[1].setSpriteSheet(textura[8]);
        stayAnimationDir[1].addFrame(sf::IntRect(textura[8].getSize().x * 0,textura[8].getSize().y * 0,textura[8].getSize().x,textura[8].getSize().y));
        
        textura[9].loadFromFile("antagonista/ParadoEsq.png");
        stayAnimationEsq[1].setSpriteSheet(textura[9]);
        stayAnimationEsq[1].addFrame(sf::IntRect(textura[9].getSize().x * 0,textura[9].getSize().y * 0,textura[9].getSize().x,textura[9].getSize().y));
        
        textura[10].loadFromFile("antagonista/atacandoLancaDir.png");
        ataqueAnimationDir[1].setSpriteSheet(textura[10]);
        for(i=0;i<7;i++){
            ataqueAnimationDir[1].addFrame(sf::IntRect(textura[10].getSize().x/7 * i,textura[10].getSize().y * 0,textura[10].getSize().x /7,textura[10].getSize().y));
        }
        
        textura[11].loadFromFile("antagonista/atacandoLancaEsq.png");
        ataqueAnimationEsq[1].setSpriteSheet(textura[11]);
        for(i=6;i>=0;i--){
            ataqueAnimationEsq[1].addFrame(sf::IntRect(textura[11].getSize().x/7 * i,textura[11].getSize().y * 0,textura[11].getSize().x /7,textura[11].getSize().y));
        }
    }
    animatedSprite.setFrameTime(sf::seconds(0.1));
    animatedSprite.pause();
    animatedSprite.setLooped(false);
    currentAnimation = &stayAnimationEsq[tipo - 1];
    animatedSprite.play(*currentAnimation);
};
void Inimigo::procurarHeroi(AnimatedSprite &heroi, sf::Time frameTime){
    sf::RectangleShape campoVisao(sf::Vector2f(heroi.getPosition().x - 175.f , heroi.getPosition().y ));
    campoVisao.setSize(sf::Vector2f(200.f, 2.f ));
    if(!campoVisao.getGlobalBounds().intersects(heroi.getGlobalBounds())){
        if(animatedSprite.getGlobalBounds().intersects(heroi.getGlobalBounds())){
            atacar();
        }else{
            andar(1,frameTime);
        }
    }
    
};
void Inimigo::andar(int direcao, sf::Time frameTime){
    animatedSprite.setFrameTime(sf::seconds(0.1));
    currentAnimation = &walkingAnimationLeft[tipo - 1];
    movement.x -= speed;
    animatedSprite.play(*currentAnimation );
    animatedSprite.move(movement * frameTime.asSeconds());
}
