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
        sf::Vector2u getTamanho();
        sf::Sprite getItem();
    private:
       sf::Sprite item;
       sf::Texture textura;
       int quantidade;
       int id;
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

void Item::carregarItem(std::string nome, float escala){
    textura.loadFromFile("Itens/"+nome+".png");
    item.setTexture(textura);
    item.setScale(sf::Vector2f(item.getScale().x/escala,item.getScale().y/escala));
};

void Item::setLocationItem(sf::Vector2f posicao){
    item.setPosition(posicao);    
};
sf::Sprite Item::getItem(){
    return item;  
};
