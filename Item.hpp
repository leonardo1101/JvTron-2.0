#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define maxItens 5

class Item{
    public:
        void setLocationItem(sf::Vector2f);
        void carregarItem(std::string);
        sf::Sprite getItem();
    private:
       sf::Sprite item;
       sf::Texture textura;
};

void Item::carregarItem(std::string nome){
    textura.loadFromFile("Itens/"+nome+".png");
    item.setTexture(textura);
    item.setScale(sf::Vector2f(item.getScale().x/5.0f,item.getScale().y/5.0f));
};

void Item::setLocationItem(sf::Vector2f posicao){
    item.setPosition(posicao);    
};
sf::Sprite Item::getItem(){
    return item;  
};
