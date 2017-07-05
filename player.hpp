#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Pilha.hpp"

class Player{
    public:
        Player(int=6); // inicialmente tem 10 vidas
        void moverDireita();
        void moverEsquerda();
        int getDirecao();
        void Parado();
        void reset();
        void setTamanho(sf::Vector2f);
        void setPosicao(sf::Vector2f);
        void setIdItem(int);
        sf::Sprite getTron();
        int idDisco;
        
        
        AnimatedSprite animatedSprite;   
        Animation* currentAnimation;
        
        //Animacao para cada estado possivel do heroi
        //utilizado vetor para ficar mais facil saber qual animação utilizar para tal item
        Animation walkingAnimationRight[5];
        Animation levandoDano[2];
        Animation walkingAnimationLeft[5];
        Animation stayAnimation[5];
        Animation stayAnimationEsq[5];
        Animation ataqueAnimation[5];
        Animation ataqueAnimationEsq[5];
        Animation pulandoDir[5];
        Animation descendoDir[5];
        Animation pulandoEsq[5];
        Animation descendoEsq[5];
// // <<<<<<< HEAD
//         void perdeVida();
//         void ganhaVida();
        void setTimeFrame(sf::Time);
//         int getVidaAtual() const;
        void fakeGravidade(sf::Vector2f);
        void atacar();
        void setTimeAtaque();
        bool adicionarDisco();
        bool getAtacando();
        void resetDisco();
        void parado();
        void setTimePulo();
        void pular();
        bool getPulando();
        bool getAndando();
        sf::Sprite barraVida;
        
        sf::Vector2f getCameraGround();
        sf::Vector2f getCameraBackground();
        
        void estadoPulo();

         bool perdeVida();
         bool ganhaVida();
    private:
        sf::Sprite tron;

        sf::Texture forma[30];
        sf::Texture vida[6];
        int direcao;
        int nDir;
        int nEsq;
        int idItem;
        int vidaQuant;
        const int nVidas;
        bool lanca;
        
        bool adicionaDisco;
        
        void setCameraGround(sf::Vector2f);
        void setCameraBackground(sf::Vector2f);
        
          //times para o tempo de ataque e pulo
        sf::Time tempoAtaque;
        sf::Time tempoPulo;
        sf::Time frameTime;
        sf::Clock ataqueClock, puloClock;
        
        //variaveis para verificar se o heroi está se movendo para utilizar com o pulo
        bool andandoDir;
        bool andandoEsq;

        //variaveis para ver qual estado do pulo está
        bool pulando;
        bool descendo;
   
        sf::Vector2f cameraGround;
        sf::Vector2f cameraBackground;
        
        //velocidade dos frames para os casos de direita e esquerda
        float speedDir;
        float speedEsq;
        bool gravidadeTrocarPulo;
        
        bool paradoBool;
        bool gravidadeMudada;
        bool atacando;
        sf::Clock batida;
        sf::Time tempoBatida;
        
        sf::Vector2f movement;
        float speed = 250.5f;
        int contPulo;
        int contPulo2;
};

bool Player::getAndando(){
    return andandoDir || andandoEsq;
};

void Player::setCameraGround(sf::Vector2f camera){
    cameraGround=camera;
};
void Player::setCameraBackground(sf::Vector2f camera ){
    cameraBackground=camera;
};
sf::Vector2f Player::getCameraGround(){
    return cameraGround;
};
sf::Vector2f Player::getCameraBackground(){
    return cameraBackground;
};
bool Player::getPulando(){
    return pulando || descendo;
};
void Player::setTimePulo(){
    tempoPulo = puloClock.getElapsedTime();
};
void Player::pular(){
    
    if(pulando == false && descendo == false){
        if(!gravidadeTrocarPulo){
            animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x,768 - 2.5f * 64  - 140));
            gravidadeTrocarPulo=true;
        }
        puloClock.restart();
        pulando = true;
    }
    if(pulando){
        if(getDirecao() == 1){
            if(!paradoBool){
                setCameraGround(sf::Vector2f(5.f,0.0f));
                animatedSprite.move(5.f, - 6.5f);
            }else{
                setCameraGround(sf::Vector2f(0.f,0.0f));
                animatedSprite.move(0.f, - 6.5f);
            }
            animatedSprite.setFrameTime(sf::seconds(0.1));
            currentAnimation = &pulandoDir[idItem];
        }else{
            if(!paradoBool){
                setCameraGround(sf::Vector2f(- 5.f,0.0f));
                animatedSprite.move(- 5.f,- 6.5f);
            }else{
                setCameraGround(sf::Vector2f(0.f,0.0f));
                animatedSprite.move(0.f, - 6.5f);
            }
            animatedSprite.setFrameTime(sf::seconds(0.1));
            currentAnimation = &pulandoEsq[idItem];
        }
    }else{
        if(getDirecao() == 1){
            
             if(!paradoBool){
                setCameraGround(sf::Vector2f(5.f,0.0f));
                animatedSprite.move(5.f,6.5f);
             }else{
                setCameraGround(sf::Vector2f(0.f,0.0f));
                animatedSprite.move(0.f, 6.5f);
            }   
            animatedSprite.setFrameTime(sf::seconds(0.1));
            currentAnimation = &descendoDir[idItem];
        }else{
            if(!paradoBool){
                setCameraGround(sf::Vector2f(- 5.f,0.0f));
                animatedSprite.move(- 5.f,6.5f);
            }else{
                setCameraGround(sf::Vector2f(0.f,0.0f));
                animatedSprite.move(0.f, 6.5f);
            }   
            animatedSprite.setFrameTime(sf::seconds(0.1));
            currentAnimation = &descendoEsq[idItem];
        }
    }
};
void Player::estadoPulo(){
    
        if(pulando){
            if(tempoPulo <= sf::seconds(0.5)){
                movement.y -= contPulo * 7.0f;
                contPulo--;                
                contPulo2++;
            }else{
                contPulo++;
                pulando = false;
                descendo = true;
            }
        }else{
            if(descendo){
                if(tempoPulo <= sf::seconds(1)){
                    movement.y += contPulo * 7.0f;
                    contPulo++;
                }else{
                    if(descendo == true)
                        andandoDir=false;
                    pulando = false;
                    descendo = false;
                    contPulo = 75;
                    contPulo2=0;
                    movement=sf::Vector2f(0,0);
                }
            }
        }
        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());
}
void Player::parado(){
    gravidadeTrocarPulo=false;
    paradoBool=true;
    andandoDir= false;
    andandoEsq=false;
    setCameraGround(sf::Vector2f(0.f,0.0f));
    setCameraBackground(sf::Vector2f(0.f,0.0f));
    if(getDirecao() == 1){
	    animatedSprite.setFrameTime(sf::seconds(0.7));
        currentAnimation = &stayAnimation[idItem];
    }else{
        animatedSprite.setFrameTime(sf::seconds(0.7));
        currentAnimation = &stayAnimationEsq[idItem];
	}
    animatedSprite.play(*currentAnimation);
};
bool Player::getAtacando(){
    return atacando;
};
void Player::resetDisco(){
    adicionaDisco=false;
};
void Player::setTimeAtaque(){
    tempoAtaque = ataqueClock.getElapsedTime();
    if(tempoAtaque >= sf::seconds(0.25) ){
            atacando=false;
    }
};
bool Player::adicionarDisco(){
    return adicionaDisco;
};
void Player::atacar(){
    paradoBool=true;
    gravidadeTrocarPulo=false;
    if(atacando == false){
//     sistemaItens.usarItem(nItem);
        atacando = true;
        ataqueClock.restart();
        if(getDirecao() == 1){
            currentAnimation = &ataqueAnimation[idItem];
            if( idItem == 1){
                animatedSprite.setFrameTime(sf::seconds(0.04));
                 //seta o vetor e o ponto do disco a ser lançado
                adicionaDisco=true;
            }else{
                animatedSprite.setFrameTime(sf::seconds(0.045));
                if(idItem == 3)
                    ganhaVida();
            }
        }else{
            currentAnimation = &ataqueAnimationEsq[idItem];
            if(idItem == 1){
                animatedSprite.setFrameTime(sf::seconds(0.04));
                adicionaDisco=true;
            
            }else{
                animatedSprite.setFrameTime(sf::seconds(0.045));
                 if(idItem == 3)
                    ganhaVida();
            }   
        }
    }
    animatedSprite.play(*currentAnimation);
};
void Player::setTimeFrame(sf::Time tempo){
    frameTime=tempo;
};
void Player::fakeGravidade(sf::Vector2f gravidade){
        if(!lanca || paradoBool ){
            if(gravidadeMudada)
                animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x + 80,gravidade.y - 140));
            else
                animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x ,gravidade.y - 140));
            gravidadeMudada=false;
        }else{    //coloca o heroi na posicao
            if(!gravidadeMudada){
                animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x - 80,gravidade.y - 140));
                gravidadeMudada=true;
            }
        }

};
void Player::setIdItem(int id){
    idItem = id;
    if(id == 2)
        lanca = true;
    else
        lanca=false;
};
void Player::moverDireita(){
    paradoBool=false;
    pulando=false;
    descendo=false;
    gravidadeTrocarPulo=false;
    setCameraGround(sf::Vector2f(20.f,0.0f));
    animatedSprite.move(20.f,0.f);
    direcao=1;
    animatedSprite.setFrameTime(sf::seconds(0.1));
    andandoDir= true;
    andandoEsq=false;
    currentAnimation = &walkingAnimationRight[idItem];
    animatedSprite.play(*currentAnimation);
};
void Player::moverEsquerda(){
    paradoBool=false;
    pulando=false;
    gravidadeTrocarPulo=false;
    descendo=false;
    setCameraGround(sf::Vector2f(- 20.f,0.0f));
    animatedSprite.move(- 20.f,0.f);
    direcao=0;
    animatedSprite.setFrameTime(sf::seconds(0.1));
    andandoDir= false;
    andandoEsq=true;
    currentAnimation = &walkingAnimationLeft[idItem];
    animatedSprite.play(*currentAnimation);
};
int Player::getDirecao(){
    
   return direcao; 
}
Player::Player(int v): nVidas(v){
    
    int i;
    bool DeuCerto;
    lanca=false;
    vidaQuant=v;
    idItem=1;
    //variavel que eh utilizada para quando atacar terminar o ataque
    atacando = false;  
    paradoBool=false;
    //variaveis para verificar se o heroi está se movendo para utilizar com o pulo
     andandoDir = false;
     andandoEsq = false;
     adicionaDisco=false;
    animatedSprite.setPosition(sf::Vector2f(500,200 - 140));
    //variaveis para ver qual estado do pulo está
    pulando = false;
	descendo = false;
    gravidadeTrocarPulo=false;
   gravidadeMudada = false;
    setCameraGround(sf::Vector2f(0.f,0.0f));
    animatedSprite.setFrameTime(sf::seconds(0.7));
    animatedSprite.pause();
    animatedSprite.setLooped(false);    
    
    contPulo = 75;
    contPulo2=0;
    
    idDisco=0;
    //velocidade dos frames para os casos de direita e esquerda
    speedDir = 200.f;
    speedEsq = 200.f;
    direcao =1;
    //subindo imagens e dividindo elas em frames
    forma[0].loadFromFile("spriteProtagonista/Andando.png");
    walkingAnimationRight[0].setSpriteSheet(forma[0]);
    walkingAnimationRight[3].setSpriteSheet(forma[0]);
    for(i=1;i<11;i++){
        walkingAnimationRight[0].addFrame(sf::IntRect(forma[0].getSize().x/11 * i,forma[0].getSize().y * 0,forma[0].getSize().x / 11,forma[0].getSize().y));
         walkingAnimationRight[3].addFrame(sf::IntRect(forma[0].getSize().x/11 * i,forma[0].getSize().y * 0,forma[0].getSize().x / 11,forma[0].getSize().y));
    }
    forma[1].loadFromFile("spriteProtagonista/Parado.png");
    stayAnimation[0].setSpriteSheet(forma[1]);
    stayAnimation[3].setSpriteSheet(forma[1]);
    for(i=0;i<6;i++){
        stayAnimation[0].addFrame(sf::IntRect(forma[1].getSize().x/6 * i,forma[1].getSize().y * 0,forma[1].getSize().x / 6,forma[1].getSize().y));
        stayAnimation[3].addFrame(sf::IntRect(forma[1].getSize().x/6 * i,forma[1].getSize().y * 0,forma[1].getSize().x / 6,forma[1].getSize().y));
  
    }
    forma[2].loadFromFile("spriteProtagonista/AndandoEsq.png");
    walkingAnimationLeft[0].setSpriteSheet(forma[2]);
    walkingAnimationLeft[3].setSpriteSheet(forma[2]);
    for(i=9;i>=0;i--){
        walkingAnimationLeft[0].addFrame(sf::IntRect(forma[2].getSize().x/11 * i,forma[2].getSize().y * 0,forma[2].getSize().x / 11,forma[2].getSize().y));
        walkingAnimationLeft[3].addFrame(sf::IntRect(forma[2].getSize().x/11 * i,forma[2].getSize().y * 0,forma[2].getSize().x / 11,forma[2].getSize().y));
    }
    forma[3].loadFromFile("spriteProtagonista/Andando0.png");
    walkingAnimationRight[1].setSpriteSheet(forma[3]);
    for(i=1;i<11;i++){
        walkingAnimationRight[1].addFrame(sf::IntRect(forma[3].getSize().x/11 * i,forma[3].getSize().y * 0,forma[3].getSize().x / 11,forma[3].getSize().y));
    }
    forma[4].loadFromFile("spriteProtagonista/AndandoEsq0.png");
    walkingAnimationLeft[1].setSpriteSheet(forma[4]);
    for(i=9;i>=0;i--){
        walkingAnimationLeft[1].addFrame(sf::IntRect(forma[4].getSize().x/11 * i,forma[4].getSize().y * 0,forma[4].getSize().x / 11,forma[4].getSize().y));
    }
    forma[5].loadFromFile("spriteProtagonista/Parado0.png");
    stayAnimation[1].setSpriteSheet(forma[5]);
    for(i=0;i<6;i++){
        stayAnimation[1].addFrame(sf::IntRect(forma[5].getSize().x/6 * i,forma[5].getSize().y * 0,forma[5].getSize().x / 6,forma[5].getSize().y));
    }
    forma[6].loadFromFile("spriteProtagonista/jogandodisco.png");
    ataqueAnimation[1].setSpriteSheet(forma[6]);
    for(i=1;i<8;i++){
        ataqueAnimation[1].addFrame(sf::IntRect(forma[6].getSize().x/8 * i,forma[6].getSize().y * 0,forma[6].getSize().x / 8,forma[6].getSize().y));
    }
     forma[7].loadFromFile("spriteProtagonista/ParadoEsq.png");
     stayAnimationEsq[0].setSpriteSheet(forma[7]);
      stayAnimationEsq[3].setSpriteSheet(forma[7]);
     for(i=5;i>=0;i--){
        stayAnimationEsq[0].addFrame(sf::IntRect(forma[7].getSize().x/6 * i,forma[7].getSize().y * 0,forma[7].getSize().x / 6,forma[7].getSize().y));
        stayAnimationEsq[3].addFrame(sf::IntRect(forma[7].getSize().x/6 * i,forma[7].getSize().y * 0,forma[7].getSize().x / 6,forma[7].getSize().y));
    }
    forma[8].loadFromFile("spriteProtagonista/ParadoEsq0.png");
    stayAnimationEsq[1].setSpriteSheet(forma[8]);
    for(i=5;i>=0;i--){
        stayAnimationEsq[1].addFrame(sf::IntRect(forma[8].getSize().x/6 * i,forma[8].getSize().y * 0,forma[8].getSize().x / 6,forma[8].getSize().y));
    }
    forma[9].loadFromFile("spriteProtagonista/jogandoDiscoEsq.png");
    ataqueAnimationEsq[1].setSpriteSheet(forma[9]);
    for(i=7;i>=0;i--){
        ataqueAnimationEsq[1].addFrame(sf::IntRect(forma[9].getSize().x/8 * i,forma[9].getSize().y * 0,forma[9].getSize().x / 8,forma[9].getSize().y));
    }
    forma[10].loadFromFile("spriteProtagonista/Andando1.png");
    walkingAnimationRight[2].setSpriteSheet(forma[10]);
     for(i=1;i<10;i++){
        walkingAnimationRight[2].addFrame(sf::IntRect(forma[10].getSize().x/10 * i,forma[10].getSize().y * 0,forma[10].getSize().x /10,forma[10].getSize().y));
    }
    forma[11].loadFromFile("spriteProtagonista/AndandoEsq1.png");
    walkingAnimationLeft[2].setSpriteSheet(forma[11]);
    for(i=9;i>=0;i--){
        walkingAnimationLeft[2].addFrame(sf::IntRect(forma[11].getSize().x/10 * i,forma[11].getSize().y * 0,forma[11].getSize().x / 10,forma[11].getSize().y));
    }
    forma[12].loadFromFile("spriteProtagonista/Parado1.png");
    stayAnimation[2].setSpriteSheet(forma[12]);
    for(i=0;i<6;i++){
        stayAnimation[2].addFrame(sf::IntRect(forma[12].getSize().x/6 * i,forma[12].getSize().y * 0,forma[12].getSize().x / 6,forma[12].getSize().y));
    }
    forma[13].loadFromFile("spriteProtagonista/ParadoEsq1.png");
    stayAnimationEsq[2].setSpriteSheet(forma[13]);
    for(i=5;i>=0;i--){
        stayAnimationEsq[2].addFrame(sf::IntRect(forma[13].getSize().x/6 * i,forma[13].getSize().y * 0,forma[13].getSize().x / 6,forma[13].getSize().y));
    }
    forma[14].loadFromFile("spriteProtagonista/lancaataca.png");
    ataqueAnimation[2].setSpriteSheet(forma[14]);
    for(i=0;i<7;i++){
        ataqueAnimation[2].addFrame(sf::IntRect(forma[14].getSize().x/7 * i,forma[14].getSize().y * 0,forma[14].getSize().x /7,forma[14].getSize().y));
    }
    forma[15].loadFromFile("spriteProtagonista/lancaatacaEsq.png");
    ataqueAnimationEsq[2].setSpriteSheet(forma[15]);
    for(i=6;i>=0;i--){
        ataqueAnimationEsq[2].addFrame(sf::IntRect(forma[15].getSize().x/7 * i,forma[15].getSize().y * 0,forma[15].getSize().x /7,forma[15].getSize().y));
    }
    forma[16].loadFromFile("spriteProtagonista/Pulando.png");
    pulandoDir[0].setSpriteSheet(forma[16]);
    pulandoDir[3].setSpriteSheet(forma[16]);
    for(i=0;i<5;i++){
        pulandoDir[0].addFrame(sf::IntRect(forma[16].getSize().x/5 * i,forma[16].getSize().y * 0,forma[16].getSize().x /5,forma[16].getSize().y));
        pulandoDir[3].addFrame(sf::IntRect(forma[16].getSize().x/5 * i,forma[16].getSize().y * 0,forma[16].getSize().x /5,forma[16].getSize().y));
    }
    descendoDir[0].setSpriteSheet(forma[16]);
    descendoDir[3].setSpriteSheet(forma[16]);
    for(i=4;i>=0;i--){
        descendoDir[0].addFrame(sf::IntRect(forma[16].getSize().x/5 * i,forma[16].getSize().y * 0,forma[16].getSize().x /5,forma[16].getSize().y));
        descendoDir[3].addFrame(sf::IntRect(forma[16].getSize().x/5 * i,forma[16].getSize().y * 0,forma[16].getSize().x /5,forma[16].getSize().y));
    }
    forma[17].loadFromFile("spriteProtagonista/PulandoEsq.png");
    pulandoEsq[0].setSpriteSheet(forma[17]);
    pulandoEsq[3].setSpriteSheet(forma[17]);
    for(i=4;i>=0;i--){
        pulandoEsq[0].addFrame(sf::IntRect(forma[17].getSize().x/5 * i,forma[17].getSize().y * 0,forma[17].getSize().x /5,forma[17].getSize().y));
        pulandoEsq[3].addFrame(sf::IntRect(forma[17].getSize().x/5 * i,forma[17].getSize().y * 0,forma[17].getSize().x /5,forma[17].getSize().y));
    }
    descendoEsq[0].setSpriteSheet(forma[17]);
    descendoEsq[3].setSpriteSheet(forma[17]);
    for(i=0;i<5;i++){
        descendoEsq[0].addFrame(sf::IntRect(forma[17].getSize().x/5 * i,forma[17].getSize().y * 0,forma[17].getSize().x /5,forma[17].getSize().y));
        descendoEsq[3].addFrame(sf::IntRect(forma[17].getSize().x/5 * i,forma[17].getSize().y * 0,forma[17].getSize().x /5,forma[17].getSize().y));
    }
    
    forma[18].loadFromFile("spriteProtagonista/Pulando0.png");
    pulandoDir[1].setSpriteSheet(forma[18]);
    for(i=0;i<5;i++){
        pulandoDir[1].addFrame(sf::IntRect(forma[18].getSize().x/5 * i,forma[18].getSize().y * 0,forma[18].getSize().x /5,forma[18].getSize().y));
    }
    descendoDir[1].setSpriteSheet(forma[18]);
    for(i=3;i>=0;i--){
        descendoDir[1].addFrame(sf::IntRect(forma[18].getSize().x/5 * i,forma[18].getSize().y * 0,forma[18].getSize().x /5,forma[18].getSize().y));
    }
    forma[19].loadFromFile("spriteProtagonista/PulandoEsq0.png");
    pulandoEsq[1].setSpriteSheet(forma[19]);
    for(i=4;i>=0;i--){
        pulandoEsq[1].addFrame(sf::IntRect(forma[19].getSize().x/5 * i,forma[19].getSize().y * 0,forma[19].getSize().x /5,forma[19].getSize().y));
    }
    descendoEsq[1].setSpriteSheet(forma[19]);
    for(i=0;i<5;i++){
        descendoEsq[1].addFrame(sf::IntRect(forma[19].getSize().x/5 * i,forma[19].getSize().y * 0,forma[19].getSize().x /5,forma[19].getSize().y));
    }
    
    forma[20].loadFromFile("spriteProtagonista/Pulando1.png");
    pulandoDir[2].setSpriteSheet(forma[20]);
    for(i=0;i<5;i++){
        pulandoDir[2].addFrame(sf::IntRect(forma[20].getSize().x/5 * i,forma[20].getSize().y * 0,forma[20].getSize().x /5,forma[20].getSize().y));
    }
    descendoDir[2].setSpriteSheet(forma[20]);
    for(i=4;i>=0;i--){
        descendoDir[2].addFrame(sf::IntRect(forma[20].getSize().x/5 * i,forma[20].getSize().y * 0,forma[20].getSize().x /5,forma[20].getSize().y));
    }
    forma[21].loadFromFile("spriteProtagonista/PulandoEsq1.png");
    pulandoEsq[2].setSpriteSheet(forma[21]);
    for(i=4;i>=0;i--){
        pulandoEsq[2].addFrame(sf::IntRect(forma[21].getSize().x/5 * i,forma[21].getSize().y * 0,forma[21].getSize().x /5,forma[21].getSize().y));
    }
    descendoEsq[2].setSpriteSheet(forma[21]);
    for(i=0;i<5;i++){
        descendoEsq[2].addFrame(sf::IntRect(forma[21].getSize().x/5 * i,forma[21].getSize().y * 0,forma[21].getSize().x /5,forma[21].getSize().y));
    }
    forma[22].loadFromFile("spriteProtagonista/soco.png");
    ataqueAnimation[0].setSpriteSheet(forma[22]);
    for(i=0;i<6;i++){
        ataqueAnimation[0].addFrame(sf::IntRect(forma[22].getSize().x/7 * i,forma[22].getSize().y * 0,forma[22].getSize().x /7,forma[22].getSize().y));
    }
    forma[23].loadFromFile("spriteProtagonista/socoEsq.png");
    ataqueAnimationEsq[0].setSpriteSheet(forma[23]);
    for(i=6;i>=0;i--){
        ataqueAnimationEsq[0].addFrame(sf::IntRect(forma[23].getSize().x/7 * i,forma[23].getSize().y * 0,forma[23].getSize().x /7,forma[23].getSize().y));
    }
    forma[24].loadFromFile("spriteProtagonista/usapocao.png");
    ataqueAnimation[3].setSpriteSheet(forma[24]);
    ataqueAnimation[3].addFrame(sf::IntRect(forma[24].getSize().x/7 * 0,forma[24].getSize().y * 0,forma[24].getSize().x ,forma[24].getSize().y));
    
    forma[25].loadFromFile("spriteProtagonista/usapocaoEsq.png");
    ataqueAnimationEsq[3].setSpriteSheet(forma[25]);
    ataqueAnimationEsq[3].addFrame(sf::IntRect(forma[25].getSize().x/7 * 0,forma[25].getSize().y * 0,forma[25].getSize().x ,forma[25].getSize().y));
    
    forma[26].loadFromFile("spriteProtagonista/danoDireita.png");
    levandoDano[0].setSpriteSheet(forma[26]);
    levandoDano[0].addFrame(sf::IntRect(forma[26].getSize().x/7 * 0,forma[26].getSize().y * 0,forma[26].getSize().x/2 ,forma[26].getSize().y));
    levandoDano[0].addFrame(sf::IntRect(forma[26].getSize().x/2 * 1,forma[26].getSize().y * 0,forma[26].getSize().x/2 ,forma[26].getSize().y));
    
    forma[27].loadFromFile("spriteProtagonista/danoEsq.png");
    levandoDano[1].setSpriteSheet(forma[27]);
    levandoDano[1].addFrame(sf::IntRect(forma[27].getSize().x/7 * 1,forma[27].getSize().y * 0,forma[27].getSize().x/2 ,forma[27].getSize().y));
    levandoDano[1].addFrame(sf::IntRect(forma[27].getSize().x/2 * 0,forma[27].getSize().y * 0,forma[27].getSize().x/2 ,forma[27].getSize().y));
    
    
     // sprite auxiliar pra epilhar

    vida[0].loadFromFile("Itens/1vida.png");
    vida[1].loadFromFile("Itens/2vida.png");
    vida[2].loadFromFile("Itens/3vida.png");
    vida[3].loadFromFile("Itens/4vida.png");
    vida[4].loadFromFile("Itens/5vida.png");
    vida[5].loadFromFile("Itens/6vida.png");
    barraVida.setTexture(vida[v - 1]);
    barraVida.setScale(sf::Vector2f(0.85,0.85));
    batida.restart();
    
    parado();
}

void Player::setTamanho(sf::Vector2f tamanho){
    tron.setScale(tamanho);
}

void Player::setPosicao(sf::Vector2f posicao){
    tron.setPosition(posicao);
}

void Player::reset(){
    direcao=1;
}

bool Player::ganhaVida(){
    bool DeuCerto=false;
    if(vidaQuant < 6){
        DeuCerto=true;
        vidaQuant++;
        barraVida.setTexture(vida[vidaQuant - 1]);
    }
    return DeuCerto;
}

bool Player::perdeVida(){
    bool DeuCerto=false;
    tempoBatida= batida.getElapsedTime();
    if(vidaQuant > 1){
        if(sf::seconds(0.5) < tempoBatida){
            DeuCerto=true;
            vidaQuant--;
            barraVida.setTexture(vida[vidaQuant - 1]);
            batida.restart();
            animatedSprite.setFrameTime(sf::seconds(0.8));
            if(direcao == 1)
                currentAnimation = &levandoDano[0];
            else
                currentAnimation = &levandoDano[1];
            animatedSprite.play(*currentAnimation);
        }
    }
    return DeuCerto;
};

#endif
