#include <SFML/Graphics.hpp>
#include <iostream>

class Disco{
    public:
        
        //move o disco de acordo com o vetor;
        void mover();
        
        //pega a sprite do disco
        sf::Sprite getDisco();
        
        //faz um reset no disco colocando primeiro o ponto e depois o vetor
        void setReset(sf::Vector2f,sf::Vector2f);
        
        //posicao do disco
        sf::Vector2f getPosicao();
        
    private:
        sf::Vector2f ponto;
        sf::Vector2f vetor;
        float escalar;
        sf::Sprite desenho;
        sf::Texture img;
};
sf::Vector2f Disco::getPosicao(){
    return desenho.getPosition();
};
void Disco::mover(){
    desenho.setPosition(sf::Vector2f(ponto.x + vetor.x * escalar,ponto.y + vetor.y * escalar));
    escalar+=5.0f;
};
sf::Sprite Disco::getDisco(){
    return desenho;
};
void Disco::setReset(sf::Vector2f p,sf::Vector2f v){
    img.loadFromFile("Itens/discoLancado.png");
    desenho.setTexture(img);
    ponto=p;
    vetor=v;
    escalar=0;
    desenho.setPosition(sf::Vector2f(ponto.x + vetor.x * escalar,ponto.y + vetor.y * escalar));
};
