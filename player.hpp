#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include "Pilha.hpp"

class Player{
    public:
        Player(int=10); // inicialmente tem 10 vidas
        void moverDireita();
        void moverEsquerda();
        int getDirecao();
        void Parado();
        void reset();
        void setTamanho(sf::Vector2f);
        void setPosicao(sf::Vector2f);
        void setIdItem(int);
        sf::Sprite getTron();
        
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
        void perdeVida();
        void ganhaVida();
        int getVidaAtual() const;
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
};
void Player::setIdItem(int id){
    idItem = id;   
    
};
void Player::moverDireita(){
    direcao=1;
};
void Player::moverEsquerda(){
    direcao=2;
};
int Player::getDirecao(){
    
   return direcao; 
}
Player::Player(int v): nVidas(v){
    int i;
    bool DeuCerto;
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
    for(int i = 0; i < nVidas; i++)
        if(vida.Vazia())
            vida.Empilha(1, DeuCerto);
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

void Player::ganhaVida(){
    bool DeuCerto;
    vida.Empilha(1, DeuCerto);
}

void Player::perdeVida(){
    int x;
    bool DeuCerto;
    if(!vida.Vazia())
        vida.Desempilha(x, DeuCerto);
};

int Player::getVidaAtual() const{
    return vida.getNumeroElementos();
};