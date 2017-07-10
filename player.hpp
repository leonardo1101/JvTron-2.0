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
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

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
        
        
        bool Bateu(AnimatedSprite);
        AnimatedSprite animatedSprite;   
        Animation* currentAnimation;
        
        //Animacao para cada estado possivel do heroi
        //utilizado vetor para ficar mais facil saber qual animação utilizar para tal item
        Animation walkingAnimationRight[6];
        Animation levandoDano[2];
        Animation walkingAnimationLeft[6];
        Animation stayAnimation[6];
        Animation stayAnimationEsq[6];
        Animation ataqueAnimation[6];
        Animation ataqueAnimationEsq[6];
        Animation pulandoDir[6];
        Animation descendoDir[6];
        Animation pulandoEsq[6];
        Animation descendoEsq[6];

        void setTimeFrame(sf::Time);
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
        bool pocaoUsando;
        sf::Sprite barraVida;
        
        sf::Vector2f getCameraGround();
        int getIdItem();
        sf::Vector2f getCameraBackground();
        
        void estadoPulo();
        bool getAdicionarDoisDiscos();
         bool perdeVida();
         bool ganhaVida();
         int getVida();
    private:
        sf::Sprite tron;

        sf::Texture forma[32];
        sf::Texture vida[6];
        int direcao;
        int nDir;
        
        bool adicionarDoisDiscos;
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
   
        bool atacouComLanca;
        //variavei para as cameras
        sf::Vector2f cameraGround;
        sf::Vector2f cameraBackground;
        
        //velocidade dos frames para os casos de direita e esquerda
        float speedDir;
        float speedEsq;
        bool gravidadeTrocarPulo;
        //variaveis de estados para pulo e gravidade ou ataque
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
//verifica se o id do item que o heroi está usando
int Player::getIdItem(){
    return idItem;
};
//pga a vida do heroi
int Player::getVida(){
    return vidaQuant;
};
//retorna se o heroi tem que adicionar dois discos
 bool Player::getAdicionarDoisDiscos(){
     return adicionarDoisDiscos;
};
//verifica se o heroi bateu
bool Player::Bateu(AnimatedSprite inimigo){
    sf::RectangleShape range;
    if(idItem == 2){
        range.setFillColor(sf::Color(32, 210, 212));
        range.setSize(sf::Vector2f(150.f, 180.f));
        range.setPosition(sf::Vector2f(animatedSprite.getPosition().x + 150, animatedSprite.getPosition().y ));
        if(direcao == 1){
                if( 300 + inimigo.getPosition().x >= range.getPosition().x  && inimigo.getPosition().x < range.getPosition().x + 150
            ){
                    return true;
            }
        }else{
            if( inimigo.getPosition().x  <= range.getPosition().x  && inimigo.getPosition().x + 300 >= range.getPosition().x - 150){
                return true;
            }
        }
    }else{
        if(idItem == 0){
            range.setFillColor(sf::Color(32, 210, 212));
            range.setSize(sf::Vector2f(70.f, 180.f));
            range.setPosition(sf::Vector2f(animatedSprite.getPosition().x + 75, animatedSprite.getPosition().y ));
            if(direcao == 1){
                    if( 300 + inimigo.getPosition().x >= range.getPosition().x  && inimigo.getPosition().x < range.getPosition().x + 50
                ){
                        return true;
                }
            }else{
                if( inimigo.getPosition().x  <= range.getPosition().x  && inimigo.getPosition().x + 300 >= range.getPosition().x - 50
                ){
                    return true;
                }
            }
        }
    }
    return false;
};
//verifica se o heroi está andando
bool Player::getAndando(){
    return andandoDir || andandoEsq;
};
//seta as cameras do heroi
void Player::setCameraGround(sf::Vector2f camera){
    cameraGround=camera;
};
void Player::setCameraBackground(sf::Vector2f camera ){
    cameraBackground=camera;
};
//pega a camera do heroi
sf::Vector2f Player::getCameraGround(){
    return cameraGround;
};
//pega a camera do heroi
sf::Vector2f Player::getCameraBackground(){
    return cameraBackground;
};
//verifica se o heroi ainda está na ação de pulando
bool Player::getPulando(){
    return pulando || descendo;
};
//seta o time do pulo do heroi
void Player::setTimePulo(){
    tempoPulo = puloClock.getElapsedTime();
};
// faz a ação de pular
void Player::pular(){
    if(atacouComLanca){
        animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x + 80,768 - 2.5f * 64  - 140));
        atacouComLanca=false;
    }
    
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
                animatedSprite.move(5.f, - 7.f);
            }else{
                setCameraGround(sf::Vector2f(0.f,0.0f));
                animatedSprite.move(0.f, - 7.f);
            }
            animatedSprite.setFrameTime(sf::seconds(0.1));
            if(idItem == 4)
                currentAnimation = &pulandoDir[1];
            else
                currentAnimation = &pulandoDir[idItem];
        }else{
            if(!paradoBool){
                setCameraGround(sf::Vector2f(- 5.f,0.0f));
                animatedSprite.move(- 5.f,- 7.f);
            }else{
                setCameraGround(sf::Vector2f(0.f,0.0f));
                animatedSprite.move(0.f, - 7.f);
            }
            if(idItem == 4)
                currentAnimation = &pulandoEsq[1];
            else
                currentAnimation = &pulandoEsq[idItem];
            animatedSprite.setFrameTime(sf::seconds(0.1));
        }
    }else{
        if(getDirecao() == 1){
            
             if(!paradoBool){
                setCameraGround(sf::Vector2f(5.f,0.0f));
                animatedSprite.move(5.f,7.f);
             }else{
                setCameraGround(sf::Vector2f(0.f,0.0f));
                animatedSprite.move(0.f, 7.f);
            }   
            animatedSprite.setFrameTime(sf::seconds(0.1));
             if(idItem == 4)
                currentAnimation = &descendoDir[1];
            else
                currentAnimation = &descendoDir[idItem];
        }else{
            if(!paradoBool){
                setCameraGround(sf::Vector2f(- 5.f,0.0f));
                animatedSprite.move(- 5.f,7.f);
            }else{
                setCameraGround(sf::Vector2f(0.f,0.0f));
                animatedSprite.move(0.f, 7.f);
            }   
            animatedSprite.setFrameTime(sf::seconds(0.1));
            if(idItem == 4)
                currentAnimation = &descendoEsq[1];
            else
            currentAnimation = &descendoEsq[idItem];
        }
    }
};
// seta o estado do pulo do heroi
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
//player está parado
void Player::parado(){
    if(atacouComLanca){
        animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x + 80,768 - 2.5f * 64  - 140));
        atacouComLanca=false;
    }
    gravidadeTrocarPulo=false;
    paradoBool=true;
    andandoDir= false;
    andandoEsq=false;
    setCameraGround(sf::Vector2f(0.f,0.0f));
    setCameraBackground(sf::Vector2f(0.f,0.0f));
    if(getDirecao() == 1){
	    animatedSprite.setFrameTime(sf::seconds(0.7));
         if(idItem == 4)
        currentAnimation = &stayAnimation[1];
        else
        currentAnimation = &stayAnimation[idItem];
    }else{
        animatedSprite.setFrameTime(sf::seconds(0.7));
        if(idItem == 4)
        currentAnimation = &stayAnimationEsq[1];
        else
        currentAnimation = &stayAnimationEsq[idItem];
	}
    animatedSprite.play(*currentAnimation);
};
bool Player::getAtacando(){
    return atacando;
};
//da um reset no disco
void Player::resetDisco(){
    adicionaDisco=false;
    adicionarDoisDiscos=false;
};
//set o tempo de ataque do heroi
void Player::setTimeAtaque(){
    tempoAtaque = ataqueClock.getElapsedTime();
    if(tempoAtaque >= sf::seconds(0.25) ){
            atacando=false;
    }
};
//pega se o tem que adicionar um disco na lista de discos do heroi
bool Player::adicionarDisco(){
    return adicionaDisco;
};
// faz o heroi  utiliza o item correspoendente
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
                pocaoUsando = false;
            }else{
                animatedSprite.setFrameTime(sf::seconds(0.045));
                if(idItem == 3){
                    ganhaVida();
                    pocaoUsando = true;
                    
                }else{
                    pocaoUsando=false;
                    if(idItem == 2){
                        if(!atacouComLanca){
                            animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x - 80,768 - 2.5f * 64  - 140));
                            atacouComLanca=true;
                        }
                    }else{
                        if(idItem == 4){
                            animatedSprite.setFrameTime(sf::seconds(0.045));
                            adicionarDoisDiscos=true;
                        }else{
                            animatedSprite.setFrameTime(sf::seconds(0.045));
                        }
                    }
                }
            }
        }else{
            currentAnimation = &ataqueAnimationEsq[idItem];
            if(idItem == 1){
                animatedSprite.setFrameTime(sf::seconds(0.04));
                adicionaDisco=true;
                pocaoUsando = false;
            }else{
                animatedSprite.setFrameTime(sf::seconds(0.045));
                 if(idItem == 3){
                    ganhaVida();                    
                    pocaoUsando = true;
                 }else{
                     pocaoUsando=false;
                     if(idItem == 2){
                        if(!atacouComLanca){
                            animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x - 80,768 - 2.5f * 64  - 140));
                            atacouComLanca=true;
                        }
                    }else{
                        if(idItem == 4){
                            animatedSprite.setFrameTime(sf::seconds(0.045));
                            adicionarDoisDiscos=true;
                        }else{
                            animatedSprite.setFrameTime(sf::seconds(0.045));
                        }
                    }
                }
            }   
        }
    }
    animatedSprite.play(*currentAnimation);
};
//set frame do heroi
void Player::setTimeFrame(sf::Time tempo){
    frameTime=tempo;
};
//fake gravidade do heroi
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
//seta o id do item que o player está carregando
void Player::setIdItem(int id){
    idItem = id;
    if(id == 2)
        lanca = true;
    else
        lanca=false;
};
//pega o heroi para direita
void Player::moverDireita(){
    if(atacouComLanca){
        animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x + 80,768 - 2.5f * 64  - 140));
        atacouComLanca=false;
    }
    paradoBool=false;
    pulando=false;
    descendo=false;
    gravidadeTrocarPulo=false;
    setCameraGround(sf::Vector2f(9.f,0.0f));
    animatedSprite.move(9.f,0.f);
    direcao=1;
    animatedSprite.setFrameTime(sf::seconds(0.1));
    andandoDir= true;
    andandoEsq=false;
    if(idItem == 4)
        currentAnimation = &walkingAnimationRight[1];
    else
    currentAnimation = &walkingAnimationRight[idItem];
    animatedSprite.play(*currentAnimation);
};
//move o heroi para esquerda
void Player::moverEsquerda(){
    if(atacouComLanca){
        animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x + 80,768 - 2.5f * 64  - 140));
        atacouComLanca=false;
    }
    paradoBool=false;
    pulando=false;
    gravidadeTrocarPulo=false;
    descendo=false;
    setCameraGround(sf::Vector2f(- 9.f,0.0f));
    animatedSprite.move(- 9.f,0.f);
    direcao=0;
    animatedSprite.setFrameTime(sf::seconds(0.1));
    andandoDir= false;
    andandoEsq=true;
    if(idItem == 4)
        currentAnimation = &walkingAnimationLeft[1];
    else
    currentAnimation = &walkingAnimationLeft[idItem];
    animatedSprite.play(*currentAnimation);
};
// pega a direção do heroi
int Player::getDirecao(){
    
   return direcao; 
}
//seta os estados do heroi, como correndo, pulando, atacando - também eh setado vida e variaveis de estado
Player::Player(int v): nVidas(v){
    pocaoUsando=false;
    int i;
    bool DeuCerto;
    lanca=false;
    vidaQuant=v;
    idItem=1;
    //variavel que eh utilizada para quando atacar terminar o ataque
    atacando = false;  
    paradoBool=false;
    adicionarDoisDiscos=false;
    atacouComLanca=false;
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
        ataqueAnimation[4].addFrame(sf::IntRect(forma[6].getSize().x/8 * i,forma[6].getSize().y * 0,forma[6].getSize().x / 8,forma[6].getSize().y));
        
    }
    forma[28].loadFromFile("spriteProtagonista/atacadoisdiscos.png");
    ataqueAnimation[4].setSpriteSheet(forma[28]);
    for(i=0;i<3;i++){
        ataqueAnimation[4].addFrame(sf::IntRect(forma[28].getSize().x/3 * i,forma[28].getSize().y * 0,forma[28].getSize().x / 3,forma[28].getSize().y));
        
    }
    forma[29].loadFromFile("spriteProtagonista/atacadoisdiscosEsq.png");
    ataqueAnimationEsq[4].setSpriteSheet(forma[29]);
    for(i=2;i>=0;i--){
        ataqueAnimationEsq[4].addFrame(sf::IntRect(forma[29].getSize().x/3 * i,forma[29].getSize().y * 0,forma[29].getSize().x / 3,forma[29].getSize().y));
        
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
    pulandoDir[4].setSpriteSheet(forma[18]);
    for(i=0;i<5;i++){
        pulandoDir[1].addFrame(sf::IntRect(forma[18].getSize().x/5 * i,forma[18].getSize().y * 0,forma[18].getSize().x /5,forma[18].getSize().y));
        pulandoDir[4].addFrame(sf::IntRect(forma[18].getSize().x/5 * i,forma[18].getSize().y * 0,forma[18].getSize().x /5,forma[18].getSize().y));
    }
    descendoDir[1].setSpriteSheet(forma[18]);
    descendoDir[4].setSpriteSheet(forma[18]);
    for(i=3;i>=0;i--){
        descendoDir[1].addFrame(sf::IntRect(forma[18].getSize().x/5 * i,forma[18].getSize().y * 0,forma[18].getSize().x /5,forma[18].getSize().y));
        descendoDir[4].addFrame(sf::IntRect(forma[18].getSize().x/5 * i,forma[18].getSize().y * 0,forma[18].getSize().x /5,forma[18].getSize().y));
    }
    forma[19].loadFromFile("spriteProtagonista/PulandoEsq0.png");
    pulandoEsq[1].setSpriteSheet(forma[19]);
    pulandoEsq[4].setSpriteSheet(forma[19]);
    for(i=4;i>=0;i--){
        pulandoEsq[1].addFrame(sf::IntRect(forma[19].getSize().x/5 * i,forma[19].getSize().y * 0,forma[19].getSize().x /5,forma[19].getSize().y));
        pulandoEsq[4].addFrame(sf::IntRect(forma[19].getSize().x/5 * i,forma[19].getSize().y * 0,forma[19].getSize().x /5,forma[19].getSize().y));
    }
    descendoEsq[1].setSpriteSheet(forma[19]);
    descendoEsq[4].setSpriteSheet(forma[19]);
    for(i=0;i<5;i++){
        descendoEsq[1].addFrame(sf::IntRect(forma[19].getSize().x/5 * i,forma[19].getSize().y * 0,forma[19].getSize().x /5,forma[19].getSize().y));
        descendoEsq[4].addFrame(sf::IntRect(forma[19].getSize().x/5 * i,forma[19].getSize().y * 0,forma[19].getSize().x /5,forma[19].getSize().y));
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
    levandoDano[1].addFrame(sf::IntRect(forma[27].getSize().x/2 * 1,forma[27].getSize().y * 0,forma[27].getSize().x/2 ,forma[27].getSize().y));
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
//seta o tamanho do heroi
void Player::setTamanho(sf::Vector2f tamanho){
    tron.setScale(tamanho);
}
//seta a posicao do heroi
void Player::setPosicao(sf::Vector2f posicao){
    tron.setPosition(posicao);
}

//da um reset no heroi
void Player::reset(){
    direcao=1;
    vidaQuant =6;
    barraVida.setTexture(vida[5]);
    animatedSprite.setPosition(sf::Vector2f(500,200 - 140));
}
//o heroi ganha vida
bool Player::ganhaVida(){
    bool DeuCerto=false;
    if(vidaQuant < 6){
        DeuCerto=true;
        vidaQuant++;
        barraVida.setTexture(vida[vidaQuant - 1]);
    }
    return DeuCerto;
}
//tira vida do heroi
bool Player::perdeVida(){
    bool DeuCerto=false;
    tempoBatida= batida.getElapsedTime();
    if(vidaQuant > 0){
        if(sf::seconds(0.5) < tempoBatida){
            DeuCerto=true;
            vidaQuant--;
            barraVida.setTexture(vida[vidaQuant - 1]);
            batida.restart();
            animatedSprite.setFrameTime(sf::seconds(0.1));
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
