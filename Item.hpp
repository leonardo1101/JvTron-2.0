#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define maxItens 5

class Item{
    public:
        void setLocationItem(sf::Vector2f);
        void carregarItem(std::string,float);
        void setId(int);
        int getId();
        int getQuantidade();
        void setQuantidade(int);
        void diminuirQuantidade();
        void aumentarQuantidade();
        void mover(sf::Vector2f);
        void setPosicao(sf::Vector2f);
        sf::Vector2u getTamanho();
        void fakeGravidade(sf::Vector2f gravidade);
        sf::Sprite getItem();
        
       sf::Sprite item;
    private:
       sf::Texture textura;
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
    }
};

void Item::setLocationItem(sf::Vector2f posicao){
    item.setPosition(posicao);    
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
#endif
