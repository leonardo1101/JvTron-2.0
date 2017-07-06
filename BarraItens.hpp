#ifndef BARRAITENS_H
#define BARRAITENS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Lista.hpp"
#include "Item.hpp"

class BarraItens{
    public:
        void resetBarra();
        int selecionarItem(int);
        void inserirItem(Item );
        Lista<Item> itens;
        sf::Sprite barraItens;
        sf::RectangleShape caixaItem[4];
        sf::RectangleShape itemSelecionado;
        void usarItem(int numCaixa);
        int quantItens();
           int getDois();
    private:
        int dois;
         sf::Texture barra;
         int idItemCaixa[4];
        int quantidadeItens;
        int getIdItem(int);
        void setPosicaoItens(int);
        void setCorCaixar(int);
        sf::Vector2f centralizar(sf::Vector2f,sf::Vector2u, int id);
      

};
sf::Vector2f BarraItens::centralizar(sf::Vector2f posicao,sf::Vector2u tamanho,int id){
    sf::Vector2f central;
    switch(id){
            case 4:
                central.x = posicao.x + 37.f - (tamanho.x/2.9)/2;
                central.y = posicao.y + 38.f - (tamanho.y/2.9)/2;
                break;
        
            case 3:
                central.x = posicao.x + 25.f - (tamanho.x/4.5)/2;
                central.y = posicao.y + 25.f - (tamanho.y/4.5)/2;
                break;
            case 2:
                central.x = posicao.x + 26.f - (tamanho.x/3.4)/2;
                central.y = posicao.y + 25.f - (tamanho.y/3.4)/2;
                break;
            case 1:
                central.x = posicao.x + 25.f - (tamanho.x/2.9)/2;
                central.y = posicao.y + 25.f - (tamanho.y/2.9)/2;
                break;

    }
    return central;
};

int BarraItens::quantItens(){
    return quantidadeItens;
}

void BarraItens::resetBarra(){ 
    int i; 
    bool deuCerto; 
    quantidadeItens=0;
    barra.loadFromFile("Itens/barraItens.png"); 
    barraItens.setTexture(barra); 
    barraItens.setScale(sf::Vector2f(0.75,0.75)); 
 
    itens.cria(); 
     
    for(int i=0; i<4; i++){ 
        caixaItem[i].setSize(sf::Vector2f(50.0f,50.0f)); 
        caixaItem[i].setFillColor(sf::Color(35, 77, 77)); 
        caixaItem[i].setPosition(sf::Vector2f(1024 - barra.getSize().x * 0.75 + 80  + 80.0f * i,17.0f)); 
        idItemCaixa[i]=0;

    } 
    //seta posicao das barras 
    barraItens.setPosition(sf::Vector2f(1024 - barra.getSize().x * 0.75,0.0f)); 
}; 
 
int BarraItens::selecionarItem(int numCaixa){ 
    itemSelecionado.setSize(sf::Vector2f(52.0f,52.0f)); 
    itemSelecionado.setFillColor(sf::Color(32, 210, 212)); 
    itemSelecionado.setPosition(sf::Vector2f(1024.f - barra.getSize().x * 0.75 + 79 + 80.0f * numCaixa ,16.0f)); 
    return idItemCaixa[numCaixa] ; 
}; 
 
int BarraItens::getIdItem(int numCaixa){ 

    return idItemCaixa[numCaixa]; 
}; 
void BarraItens::setPosicaoItens(int a){ 
    bool deuCerto; 
    Item auxItem; 
    int i=0; 
    for(i=0;i<4;i++){ 
        idItemCaixa[i]=0;
    }  
    i=0;
    itens.PegaOPrimeiro(auxItem,deuCerto);
    while(deuCerto){
        idItemCaixa[i]=auxItem.getId();
        auxItem.idCaixa=i;
        auxItem.setPosicao(centralizar(caixaItem[i].getPosition(),auxItem.getTamanho(),auxItem.getId())); 
        itens.atualizaP(auxItem,deuCerto); 
        i++;
        itens.PegaOProximo(auxItem,deuCerto);
    }
    
}; 
void BarraItens::setCorCaixar(int quant ){ 
    bool deuCerto; 
    int aux =0,i,quantItem;  
    for(i=0;i<4;i++){ 
        Item auxItem; 
        if(i<quant){
            if(i == 0){
                itens.PegaOPrimeiro(auxItem,deuCerto);
            } else
                itens.PegaOProximo(auxItem,deuCerto);
            if(!deuCerto)
                break;
            quantItem=auxItem.getQuantidade();
            caixaItem[i].setFillColor(sf::Color(95 - 10 * quantItem, 40 + 5 * quantItem , 40 + 5 * quantItem)); 
        }else{
            quantItem=6;
            caixaItem[i].setFillColor(sf::Color(95 - 10 * quantItem, 40 + 5 * quantItem , 40 + 5 * quantItem)); 
        }
    }  
}; 
void BarraItens::inserirItem(Item item){
    bool deuCerto;
    int i=0,quant; 
    if(itens.estaNaLista(item)){
        Item auxItem;
        itens.PegaOPrimeiro(auxItem,deuCerto);
        while(deuCerto){
            if(item.getId() == auxItem.getId() ){
                auxItem.aumentarQuantidade();  
            }
            caixaItem[auxItem.idCaixa].setFillColor(sf::Color(95 - 10 * auxItem.getQuantidade(), 40 + 5 * auxItem.getQuantidade() , 40 + 5 * auxItem.getQuantidade())); 
            itens.atualizaP(auxItem,deuCerto); 
            i++;
            itens.PegaOProximo(auxItem,deuCerto);
        }
    }else{
            printf("Fora dos itens");
            item.setQuantidade(6);
            item.idCaixa = quantidadeItens;
            idItemCaixa[quantidadeItens]=item.getId();
            item.setPosicao(centralizar(caixaItem[quantidadeItens].getPosition(),item.getTamanho(),item.getId())); 
            itens.insere(item,deuCerto);
            quantidadeItens++;
    }
    
};
void BarraItens::usarItem(int numCaixa){
    bool deuCerto;
    Item auxItem;
    bool excluiu=false;
    int aux =0,i,quant,quantItem=1; 
    quant = itens.getQuant(); 
        auxItem.idCaixa=numCaixa;
        if(itens.estaNaListaCaixa(auxItem)){
            itens.removePCaixa(auxItem,deuCerto);
            quantItem=auxItem.getQuantidade();
            caixaItem[numCaixa].setFillColor(sf::Color(95 - 10 * quantItem, 40 + 5 * quantItem , 40 + 5 * quantItem)); 
            auxItem.diminuirQuantidade(); 
            if(auxItem.getQuantidade() > 1 )
                itens.insere(auxItem,deuCerto);
            else{
                excluiu=true;
                quantidadeItens--;
                idItemCaixa[numCaixa]=0;
            }
    }
    if(excluiu){
        quant--;
        setCorCaixar(quant);
        setPosicaoItens(quant);
    }
};


#endif
