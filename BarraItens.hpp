#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.hpp"

class BarraItens{
    public:
        void resetBarra();
        void selecionarItem(int);
        void inserirItem();
        
    private:
        sf::Texture barra;
        Lista<Item> itens;
        sf::Sprite barraItens;
        sf::RectangleShape caixaItem[4];
        sf::RectangleShape itemSelecionado;
        
        int getIdItem(int);
};
void BarraItens::resetBarra(){
    int i;
    Item itemVazio;
    bool deuCerto;
    
    barra.loadFromFile("Itens/barraItens.png");
    barraItens.setTexture(barra);
    barraItens.setScale(sf::Vector2f(0.75,0.75));

    itens.cria();
    
    for(int i=0; i<4; i++){
        caixaItem[i].setSize(sf::Vector2f(50.0f,50.0f));
        caixaItem[i].setFillColor(sf::Color(35, 77, 77));
        caixaItem[i].setPosition(sf::Vector2f(1024 - barra.getSize().x * 0.75 + 80  + 80.0f * i,17.0f));
        itemVazio.carregarItem("",3.0f);
        itemVazio.setId(0);
        itemVazio.setPosicao(sf::Vector2f(caixaItem[i].getPosition().x + 25.f - 200/3, caixaItem[i].getPosition().x + 25.f - 200/3));
        itens.insere(itemVazio,deuCerto);
    }
    //seta posicao das barras
    barraItens.setPosition(sf::Vector2f(1024 - barra.getSize().x * 0.75,0.0f));
};

int BarraItens::selecionarItem(int numCaixa){
    itemSelecionado = new sf::RectangleShape(sf::Vector2f(52.0f,52.0f));
    itemSelecionado.setFillColor(sf::Color(32, 210, 212));
    itemSelecionado.setPosition(sf::Vector2f(1024.f - barra.getSize().x * 0.75 + 79 + 80.0f * nItem ,16.0f));
    return getIdItem(numCaixa);
};

int BarraItens::getIdItem(int numCaixa){
    bool deuCerto;
    Item auxItem;
    int aux,i,quant;
    quant = itens.getQuant();
    for(i=0;i<quant;i++){
        itens.remove(auxItem,deuCerto);
        if(i == numCaixa)
            aux = itens.getId();
        itens.insere(auxItem,deuCerto);
    }
    return aux;
};
