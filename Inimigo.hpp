#ifndef INIMIGO_H
#define INIMIGO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Item.hpp"
class Inimigo{
    public:
        int id;
        AnimatedSprite animatedSprite;
        Animation walkingAnimationRight[2];
        Animation walkingAnimationLeft[2];
        Animation stayAnimationDir[2];
        Animation stayAnimationEsq[2];
        Animation ataqueAnimationDir[2];
        Animation ataqueAnimationEsq[3];  
        bool statusDrop;
        void setTipo(int);
        void setDiscoJogado();
        bool getAtacouDisco();
        void setPosicao(sf::Vector2f);
        sf::Vector2f getPosicao();
        void atacar();
        bool temDrop;
        
        Item drop;
        int getDirecao();
        bool procurarHeroi(AnimatedSprite &,sf::Time);
        void procura(AnimatedSprite &,sf::Time);
        bool Bateu(AnimatedSprite &heroi);
        void andar(sf::Time);
        void fakeGravidade(sf::Vector2f gravidade);
        void setVida(int);
        int getVida();
        void tirarVida();
        bool getAtacando();
        void gerarItem();
    private:
        int estado;
        sf::Vector2f sizeEstado[2];
        bool atacando;
        bool atacouDisco;
        sf::Time tempoAtaque;
        sf::Clock ataqueClock;
        Animation* currentAnimation;
        sf::Texture textura[20];
        int vida;
        int direcao;
        int tipo;
        sf::Vector2f movement;
        float speed = 300.5f;
        
        
        sf::Clock batida;
        sf::Time tempoBatida;
        void setSizeEstado();
        void mudarEstado();
};
void Inimigo::gerarItem(){
    int id = rand() % 3 + 1;
    switch(id){
        case 1:
            drop.carregarItem("disco",2.9f);
            drop.setId(1);
            break;
        case 2:
            drop.carregarItem("lanca",3.4f);
            drop.setId(2);
            drop.setQuantidade(6);
            break;
        case 3:
            drop.carregarItem("pocao",4.5f);
            drop.setId(3);
            drop.setQuantidade(6);
            break;
    }
    
}

bool  Inimigo::getAtacando(){
     return atacando;
};
void  Inimigo::tirarVida(){
    tempoBatida= batida.getElapsedTime();
    if(sf::seconds(0.5) < tempoBatida){
        vida--;
        batida.restart();
    }
};
void Inimigo::setVida(int v){
    vida=v;
};
int Inimigo::getVida(){
    return vida;
};
void Inimigo::fakeGravidade(sf::Vector2f gravidade){
        animatedSprite.setPosition(sf::Vector2f(gravidade.x,gravidade.y - 140));//coloca o heroi na posicao
};
void Inimigo::setSizeEstado(){
    sizeEstado[0]= sf::Vector2f(150.f,150.f);
    sizeEstado[1]= sf::Vector2f(300.f,150.f);
    
};
void Inimigo::mudarEstado(){
    sf::Vector2f aux;
    aux=getPosicao();
    if(estado == 0){
        estado = 1;
        setPosicao(aux);
    }else{
        estado = 0;
        setPosicao(aux);
    }
};

int Inimigo::getDirecao(){
    return direcao;
};
void Inimigo::setDiscoJogado(){
    atacouDisco=false;
};
bool Inimigo::getAtacouDisco(){
    return atacouDisco;
};
void Inimigo::setPosicao(sf::Vector2f posicao){
    animatedSprite.setPosition(sf::Vector2f(posicao.x - sizeEstado[estado].x/2 , posicao.y - sizeEstado[estado].y/2));
};
sf::Vector2f Inimigo::getPosicao(){
    return sf::Vector2f(animatedSprite.getPosition().x + sizeEstado[estado].x/2 , animatedSprite.getPosition().y + sizeEstado[estado].y/2 );
    
};
void Inimigo::atacar(){
    movement.x=0;
    movement.y=0;
    if(direcao == -1)
        currentAnimation = &ataqueAnimationEsq[tipo - 1];
    else
        currentAnimation = &ataqueAnimationDir[tipo - 1];
    if(tipo == 2 ){
        if(estado == 0)
            mudarEstado();
        animatedSprite.setFrameTime(sf::seconds(0.04));
        animatedSprite.play(*currentAnimation);
    }else{
        tempoAtaque = ataqueClock.getElapsedTime();
        if(tempoAtaque >= sf::seconds(0.8) || !atacando){
            atacouDisco=true;
            ataqueClock.restart();
            animatedSprite.setFrameTime(sf::seconds(0.01));
            currentAnimation = &stayAnimationEsq[tipo - 1];
            animatedSprite.play(*currentAnimation);
        }else{
            if(tempoAtaque <= sf::seconds(0.315) ){
                animatedSprite.setFrameTime(sf::seconds(0.045));
                animatedSprite.play(*currentAnimation);
            }else{
                animatedSprite.setFrameTime(sf::seconds(0.01));
                currentAnimation = &stayAnimationEsq[tipo - 1];
                animatedSprite.play(*currentAnimation);
            }
        }   
        
    }
    atacando=true;
};

void Inimigo::setTipo(int t){
    int i;
    batida.restart();
    setVida(3);
    tipo=t;
    direcao=-1;
    atacouDisco=false;
    atacando=false;
    estado=0;
    setSizeEstado();
    gerarItem();
    statusDrop=false;
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
        for(i=1;i<8;i++){
            ataqueAnimationDir[0].addFrame(sf::IntRect(textura[4].getSize().x/8 * i,textura[4].getSize().y * 0,textura[4].getSize().x /8,textura[4].getSize().y));
        }
        
        textura[5].loadFromFile("antagonista/atacandoDiscoEsq.png");
        ataqueAnimationEsq[0].setSpriteSheet(textura[5]);
        for(i=6;i>=0;i--){
            ataqueAnimationEsq[0].addFrame(sf::IntRect(textura[5].getSize().x/8 * i,textura[5].getSize().y * 0,textura[5].getSize().x /8,textura[5].getSize().y));
        }
    }else{
        textura[6].loadFromFile("antagonista/andandoDir1.png");
        walkingAnimationRight[1].setSpriteSheet(textura[6]);
        for(i=0;i<10;i++){
            walkingAnimationRight[1].addFrame(sf::IntRect(textura[6].getSize().x/10 * i,textura[6].getSize().y * 0,textura[6].getSize().x / 10,textura[6].getSize().y));
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
bool Inimigo::procurarHeroi(AnimatedSprite &heroi, sf::Time frameTime){
     bool achou=false;
    sf::RectangleShape campoVisao(sf::Vector2f(getPosicao().x - 600.f , getPosicao().y ));
    campoVisao.setPosition(getPosicao().x  - 600.f , getPosicao().y);
    campoVisao.setFillColor(sf::Color(32, 210, 212));
    campoVisao.setSize(sf::Vector2f(1200.f, 20.f ));
    if(heroi.getPosition().x - animatedSprite.getPosition().x < 0 ){
        direcao=-1;
    }else{
        direcao=1;
    }
    if(campoVisao.getGlobalBounds().intersects(heroi.getGlobalBounds()) || heroi.getGlobalBounds().intersects(animatedSprite.getGlobalBounds())){
        if(heroi.getGlobalBounds().intersects(animatedSprite.getGlobalBounds()) || tipo == 1 ){
            atacar();
        }else{
            if(estado == 1)
                mudarEstado();
            andar(frameTime);
            
        }
        achou=true;
    }else{
        if(estado == 1)
                mudarEstado();
        animatedSprite.setFrameTime(sf::seconds(0.1));
        currentAnimation = &stayAnimationEsq[tipo - 1];
        animatedSprite.play(*currentAnimation);
    }
    return achou;
};
void Inimigo::procura(AnimatedSprite &heroi, sf::Time frameTime){

    if(heroi.getPosition().x - animatedSprite.getPosition().x < 0 ){
        direcao=-1;
    }else{
        direcao=1;
    }
    andar(frameTime);
};
void Inimigo::andar(sf::Time frameTime){
    animatedSprite.setFrameTime(sf::seconds(0.1));
    movement.x = 0;
    if(direcao == -1){
        currentAnimation = &walkingAnimationLeft[tipo - 1];
        movement.x = - speed;
    }else{
        currentAnimation = &walkingAnimationRight[tipo - 1];
        movement.x = speed;
    }
    animatedSprite.play(*currentAnimation );
    animatedSprite.move(movement * frameTime.asSeconds());
}
bool Inimigo::Bateu(AnimatedSprite &heroi){
    sf::RectangleShape range(sf::Vector2f(getPosicao().x, getPosicao().y ));
    range.setFillColor(sf::Color(32, 210, 212));
    range.setSize(sf::Vector2f(150.f, 180.f));
    if(direcao == -1){
        range.setPosition(animatedSprite.getPosition().x - 150  , animatedSprite.getPosition().y - 75 );
            if( 75.f + heroi.getPosition().x >= range.getPosition().x  && heroi.getPosition().x + 75.f < range.getPosition().x + 150.f
            && heroi.getPosition().y >= range.getPosition().y  && heroi.getPosition().y < range.getPosition().y + 140.f
        ){
            return true;
        }
    }else{
        range.setPosition(animatedSprite.getPosition().x + 150  , animatedSprite.getPosition().y - 75 );
        if( heroi.getPosition().x >= range.getPosition().x  && heroi.getPosition().x < range.getPosition().x + 150.f
        && heroi.getPosition().y >= range.getPosition().y  && heroi.getPosition().y < range.getPosition().y + 140.f
        ){
            return true;
        }
    }
    
    return false;
}
#endif
