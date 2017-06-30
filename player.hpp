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
        
        
        AnimatedSprite animatedSprite;   
        Animation* currentAnimation;
        
        //Animacao para cada estado possivel do heroi
        //utilizado vetor para ficar mais facil saber qual animação utilizar para tal item
        Animation walkingAnimationRight[4];
        Animation walkingAnimationLeft[4];
        Animation stayAnimation[4];
        Animation stayAnimationEsq[4];
        Animation ataqueAnimation[3];
        Animation ataqueAnimationEsq[3];
        Animation pulandoDir[3];
        Animation descendoDir[3];
        Animation pulandoEsq[3];
        Animation descendoEsq[3];
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
        
        sf::Vector2f getCameraGround();
        sf::Vector2f getCameraBackground();
        
        void estadoPulo();
// =======
//         bool perdeVida();
//         bool ganhaVida();
//         int getVidaAtual() const;
//         Pilha getPilha () const;
// >>>>>>> master
    private:
        sf::Sprite tron;
        //texture para subir cada imagem
        sf::Texture forma[25];
        int direcao;
        int nDir;
        int nEsq;
        int idItem;
        Pilha vida;
        const int nVidas;
        
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
        
        bool atacando;
        
        sf::Vector2f movement;
        float speed = 250.5f;
        int contPulo;
        int contPulo2;
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
        animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x,animatedSprite.getPosition().y - 20));
        puloClock.restart();
        pulando = true;
    }
    if(!descendo){
        if(getDirecao() == 1){
            setCameraGround(sf::Vector2f(- 2.f, 2.f));
            setCameraBackground(sf::Vector2f(- 4.f, 2.f));
            animatedSprite.setFrameTime(sf::seconds(0.1));
            currentAnimation = &pulandoDir[idItem];
        }else{
            setCameraGround(sf::Vector2f(2.f,2.f));
            setCameraBackground(sf::Vector2f(4.f,2.f));
            animatedSprite.setFrameTime(sf::seconds(0.1));
            currentAnimation = &pulandoEsq[idItem];
        }
    }else{
        printf("Descendo\n");
        if(getDirecao() == 1){
            setCameraGround(sf::Vector2f(- 2.f, - 2.f));
            setCameraBackground(sf::Vector2f(- 4.f, - 2.f));
            animatedSprite.setFrameTime(sf::seconds(0.1));
            currentAnimation = &descendoDir[idItem];
        }else{
            setCameraGround(sf::Vector2f(2.f, - 2.f));
            setCameraBackground(sf::Vector2f(4.f, - 2.f));
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
                }
            }
        }
        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());
}
void Player::parado(){
    setCameraGround(sf::Vector2f(0.f,0.0f));
    setCameraBackground(sf::Vector2f(0.f,0.0f));
    andandoDir= false;
    andandoEsq=false;
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
            }
        }else{
            currentAnimation = &ataqueAnimationEsq[idItem];
            if(idItem == 1){
                animatedSprite.setFrameTime(sf::seconds(0.04));
                adicionaDisco=true;
            
            }else{
                animatedSprite.setFrameTime(sf::seconds(0.045));
            }   
        }
    }
    animatedSprite.play(*currentAnimation);
};
void Player::setTimeFrame(sf::Time tempo){
    frameTime=tempo;
};
void Player::fakeGravidade(sf::Vector2f gravidade){
        animatedSprite.setPosition(sf::Vector2f(500.0f,gravidade.y - 140));//coloca o heroi na posicao
            movement = sf::Vector2f(animatedSprite.getPosition().x,animatedSprite.getPosition().y);
};
void Player::setIdItem(int id){
    idItem = id;   
    
};
void Player::moverDireita(){
    setCameraGround(sf::Vector2f(- 2.f,0.0f));
    setCameraBackground(sf::Vector2f(- 4.f,0.0f));
    direcao=1;
    animatedSprite.setFrameTime(sf::seconds(0.1));
    andandoDir= true;
    andandoEsq=false;
    movement.x += speedDir;
    currentAnimation = &walkingAnimationRight[idItem];
    animatedSprite.play(*currentAnimation);
    animatedSprite.move(movement * frameTime.asSeconds());
};
void Player::moverEsquerda(){
    setCameraGround(sf::Vector2f(2.f,0.0f));
    setCameraBackground(sf::Vector2f(4.f,0.0f));
    direcao=0;
    animatedSprite.setFrameTime(sf::seconds(0.1));
    andandoDir= false;
    andandoEsq=true;
    movement.x -= speedDir;
    currentAnimation = &walkingAnimationLeft[idItem];
    animatedSprite.play(*currentAnimation);
    animatedSprite.move(movement * frameTime.asSeconds());
};
int Player::getDirecao(){
    
   return direcao; 
}
Player::Player(int v): nVidas(v){
    int i;
    bool DeuCerto;
    
    idItem=1;
    //variavel que eh utilizada para quando atacar terminar o ataque
    atacando = false;  
    //variaveis para verificar se o heroi está se movendo para utilizar com o pulo
     andandoDir = false;
     andandoEsq = false;
     adicionaDisco=false;

    //variaveis para ver qual estado do pulo está
    pulando = false;
	descendo = false;
   
    animatedSprite.setFrameTime(sf::seconds(0.7));
    animatedSprite.pause();
    animatedSprite.setLooped(false);    
    
    contPulo = 75;
    contPulo2=0;
    
    
    //velocidade dos frames para os casos de direita e esquerda
    speedDir = 200.f;
    speedEsq = 200.f;
    direcao =1;
    //subindo imagens e dividindo elas em frames
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
    for(i=9;i>=0;i--){
        walkingAnimationLeft[0].addFrame(sf::IntRect(forma[2].getSize().x/11 * i,forma[2].getSize().y * 0,forma[2].getSize().x / 11,forma[2].getSize().y));
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
     for(i=5;i>=0;i--){
        stayAnimationEsq[0].addFrame(sf::IntRect(forma[7].getSize().x/6 * i,forma[7].getSize().y * 0,forma[7].getSize().x / 6,forma[7].getSize().y));
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
    for(i=0;i<5;i++){
        pulandoDir[0].addFrame(sf::IntRect(forma[16].getSize().x/5 * i,forma[16].getSize().y * 0,forma[16].getSize().x /5,forma[16].getSize().y));
    }
    descendoDir[0].setSpriteSheet(forma[16]);
    for(i=4;i>=0;i--){
        descendoDir[0].addFrame(sf::IntRect(forma[16].getSize().x/5 * i,forma[16].getSize().y * 0,forma[16].getSize().x /5,forma[16].getSize().y));
    }
    forma[17].loadFromFile("spriteProtagonista/PulandoEsq.png");
    pulandoEsq[0].setSpriteSheet(forma[17]);
    for(i=4;i>=0;i--){
        pulandoEsq[0].addFrame(sf::IntRect(forma[17].getSize().x/5 * i,forma[17].getSize().y * 0,forma[17].getSize().x /5,forma[17].getSize().y));
    }
    descendoEsq[0].setSpriteSheet(forma[17]);
    for(i=0;i<5;i++){
        descendoEsq[0].addFrame(sf::IntRect(forma[17].getSize().x/5 * i,forma[17].getSize().y * 0,forma[17].getSize().x /5,forma[17].getSize().y));
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
    // inserir vidas iniciais
//     for(int i = 0; i < nVidas; i++){
//         sf::Texture tAux; // sprite auxiliar pra epilhar
//         switch(i){
//             case 0:
//                 tAux.loadFromFile("Itens/1vida.png");
//                 break;
//             case 1:
//                 tAux.loadFromFile("Itens/2vida.png");
//                 break;
//             case 2:
//                 tAux.loadFromFile("Itens/3vida.png");
//                 break;
//             case 3:
//                 tAux.loadFromFile("Itens/4vida.png");
//                 break;
//             case 4:
//                 tAux.loadFromFile("Itens/5vida.png");
//                 break;
//             case 5:
//                 tAux.loadFromFile("Itens/6vida.png");
//                 break;
//         }
//         vida.Empilha(tAux, DeuCerto);
//     }
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

// bool Player::ganhaVida(){
//     sf::Texture tAux; // Textura auxiliar pra empilhar
//     bool DeuCerto;
//     switch(vida.getNumeroElementos()){
//         case 0:
//             tAux.loadFromFile("Itens/1vida.png");
//             break;
//         case 1:
//             tAux.loadFromFile("Itens/2vida.png");
//             break;
//         case 2:
//             tAux.loadFromFile("Itens/3vida.png");
//             break;
//         case 3:
//             tAux.loadFromFile("Itens/4vida.png");
//             break;
//         case 4:
//             tAux.loadFromFile("Itens/5vida.png");
//             break;
//         case 5:
//             tAux.loadFromFile("Itens/6vida.png");
//             break;
//         case 6:
//             return false;
//             break;
//     }
//     vida.Empilha(tAux, DeuCerto);
//     return DeuCerto;
// }
/*
bool Player::perdeVida(){
    sf::Texture tAux;
    bool DeuCerto;
    if(!vida.Vazia())
        vida.Desempilha(tAux, DeuCerto);
    return DeuCerto;
};

int Player::getVidaAtual() const{
    return vida.getNumeroElementos();
};

Pilha Player::getPilha() const {
    return vida;
};*/
#endif
