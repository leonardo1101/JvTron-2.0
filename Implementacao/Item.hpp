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
#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "AnimatedSprite.hpp"

#define maxItens 5

class Item{
    public:
        void setLocationItem(sf::Vector2f); // seta a posicao do item
        void carregarItem(std::string,float); // carrega o item
        bool Bateu(AnimatedSprite &heroi); //verifica se batei
        void setId(int); //seta o id do item
        int getId(); //pega o id do item
        int idCaixa; // id da caixa que o item está
        int getQuantidade(); // pega a quantidade de itens
        void setQuantidade(int); // seta a  quantidade de itens
        void diminuirQuantidade(); // diminui a quantidade de iten
        void aumentarQuantidade(); // aumenta a quantidade de itens
        void mover(sf::Vector2f);   // faz o item mudar de posicao
        void setPosicao(sf::Vector2f); // seta a posicao do item 
        sf::Vector2u getTamanho(); // pega o tamanha do item
        void fakeGravidade(sf::Vector2f gravidade); // gravidade sobre o item
        sf::Sprite getItem(); // pega o item
        sf::Sprite itemDrop; // item do drop
       sf::Sprite item; // item
    private:
       sf::Texture textura;
       sf::Texture texturaDrop;
       int quantidade;
       int id;
};
void Item::fakeGravidade(sf::Vector2f gravidade){
        item.setPosition(sf::Vector2f(item.getPosition().x,gravidade.y + 100));//coloca o heroi na posicao
};

void Item::mover(sf::Vector2f m){
    item.move(m);
};
int Item::getQuantidade(){
    return quantidade;
};
void Item::diminuirQuantidade(){
    if(quantidade - 1 >= 0)
        quantidade--;
};
void Item::aumentarQuantidade(){
    if(quantidade + 1 < 7)
        quantidade++;
};
void Item::setQuantidade(int quant){
    if(quant < 7 && quant>=0)
        quantidade=quant;
};

void Item::setPosicao(sf::Vector2f posicao){
    itemDrop.setPosition(posicao);
    item.setPosition(posicao);
};
sf::Vector2u Item::getTamanho(){
    
    return textura.getSize();
}
int Item::getId(){
    return id;
}
void Item::setId(int i){
    id=i;    
}
//pega a imagem do item
void Item::carregarItem(std::string nome, float escala){
    if(nome != ""){
        textura.loadFromFile("Itens/"+nome+".png");
        item.setTexture(textura);
        item.setScale(sf::Vector2f(item.getScale().x/escala,item.getScale().y/escala));
        texturaDrop.loadFromFile("Itens/"+nome+"Drop.png");
        itemDrop.setTexture(texturaDrop);
        itemDrop.setScale(sf::Vector2f(itemDrop.getScale().x/5,itemDrop.getScale().y/5));
    }
};

void Item::setLocationItem(sf::Vector2f posicao){
    item.setPosition(posicao);    
    itemDrop.setPosition(posicao);   
};
//pega a sprite do item
sf::Sprite Item::getItem(){
    return item;  
};
bool operator==(Item& lhs, Item& rhs){

    if(lhs.getId() == rhs.getId())
        return true;
    return false;
};
bool Item::Bateu(AnimatedSprite &heroi){
    sf::RectangleShape range(sf::Vector2f(item.getPosition().x, item.getPosition().y ));
    range.setPosition(sf::Vector2f(item.getPosition().x, item.getPosition().y ));
    range.setFillColor(sf::Color(32, 210, 212));
    range.setSize(sf::Vector2f(50.f, 50.f));
    

        if(300 + heroi.getPosition().x >= range.getPosition().x  && heroi.getPosition().x < range.getPosition().x + 50
    )
            return true;
 
    
    return false;
}
#endif
