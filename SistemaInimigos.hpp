#ifndef SISTEMAINIMIGOS_H
#define SISTEMAINIMIGOS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Lista.hpp"
#include "Inimigo.hpp"

class SistemaInimigos{
    public:
        Lista<Inimigo> inimigos;
        void gerarQuanInimigos(int);
        
    private:
        void adicionarInimigo();
        
};
void SistemaInimigos::gerarQuanInimigos(int quant){
    int i;
    inimigos.cria();
    for(i=0;i<quant;i++){
        adicionarInimigo();
    }
};
void SistemaInimigos::adicionarInimigo(){
    bool ok;
    Inimigo inimigo;
    inimigo.setTipo( 1);
    inimigos.insere(inimigo,ok);
};
#endif
