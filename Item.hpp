#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define maxItens 5

class Item{
    public:
        void setLocationItem(sf::Vector2f);
        void carregarItem(std::string);
        sf::RectangleShape getItem();
    private:
       sf::RectangleShape item;
};

void Item::carregarItem(std::string nome){
    sf::Texture textura;
    textura.loadFromFile("Itens/"+nome+".png");
    
};

void Item::setLocationItem(sf::Vector2f posicao){
    item.setPosition(posicao);    
};
sf::RectangleShape Item::getItem(){
    return item;  
};
