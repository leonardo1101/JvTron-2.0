#ifndef Renderiza_H
#define Renderiza_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Renderiza{
    public:
        void reset();
        void desenha(sf::Sprite& ,sf::Sprite &,sf::RenderWindow & App );
        
    private:
        int cont;
};
void Renderiza::reset(){
    cont=0;
}
void Renderiza::desenha(sf::Sprite & um , sf::Sprite & dois, sf::RenderWindow & App){
    if(cont == 0)
        App.draw(um);
    else
        App.draw(dois);
    
    if(cont >= 1)
        cont=0;
    else
        cont++;
};
#endif
