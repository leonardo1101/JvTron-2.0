#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Item.hpp"
#include "Lista.hpp"
#include <string>

enum InputType{
    KeyboardInput
};
 
struct MyKeys{
    InputType myInputType;
    sf::Event::EventType myEventType;
    sf::Keyboard::Key myKeyCode;
};

bool TestEvent(MyKeys k, sf::Event e){
    // Keyboard event
    if (k.myInputType == KeyboardInput &&
        k.myEventType == e.type &&
        k.myKeyCode == e.key.code)
    {
        return (true);
    }
    return (false);
};

int main (){
    Lista<Item> itens;
    Item item,item1;
    sf::Sprite barraItens;
    sf::Sprite barraVida;
    sf::Texture vida;
    sf::Texture barra;
    sf::Texture mapa;
    sf::Sprite background;
    sf::RectangleShape caixaItem[5];
    sf::RectangleShape itemSelecionado(sf::Vector2f(87.0f,87.0f));
    int i, nItem=0;
    
    for(i=0; i<5; i++){
        caixaItem[i].setSize(sf::Vector2f(85.0f,85.0f));
        caixaItem[i].setFillColor(sf::Color(35, 77, 77));
        caixaItem[i].setPosition(sf::Vector2f(820.0f + 110.0f * i,17.0f));
        
    }
    
    itemSelecionado.setFillColor(sf::Color(32, 210, 212));
    itemSelecionado.setPosition(sf::Vector2f(819.0f,16.0f));
    barra.loadFromFile("Itens/barraItens.png");
    barraItens.setTexture(barra);
    vida.loadFromFile("Itens/6vida.png");
    barraVida.setTexture(vida);
    mapa.loadFromFile("TilesMap/teste.png");
    background.setTexture(mapa);
    background.setScale(sf::Vector2f(4.4f,2.5f));
    bool deuCerto;
    
    item.setLocationItem(sf::Vector2f(825.0f,20.0f));
    item.carregarItem("disco",2.5f);
    item1.setLocationItem(sf::Vector2f(930.0f,10.0f));
    item1.carregarItem("lanca",2.2f);
    itens.cria();
    itens.insere(item,deuCerto);
    itens.insere(item1,deuCerto);
    sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!", sf::Style::Fullscreen);
    barraItens.setPosition(sf::Vector2f(1366.0f - barra.getSize().x,0.0f));
    while (window.isOpen())
    {
    sf::Event Event;

    std::map<std::string,MyKeys> Keys;
    MyKeys key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::Num1;
    Keys["item1"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::Num2;
    Keys["item2"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::Num3;
    Keys["item3"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::Num4;
    Keys["item4"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::Num5;
    Keys["item5"] = key;
// 
//     key.myInputType = KeyboardInput;
//     key.myEventType = sf::Event::KeyPressed;
//     key.myKeyCode = sf::Keyboard::A;
//     Keys["tron-Esquerda"] = key;
// 
//     key.myInputType = KeyboardInput;
//     key.myEventType = sf::Event::KeyPressed;
//     key.myKeyCode = sf::Keyboard::S;
//     Keys["tron-Baixo"] = key;
//     
//     key.myInputType = KeyboardInput;
//     key.myEventType = sf::Event::KeyPressed;
//     key.myKeyCode = sf::Keyboard::W;
//     Keys["tron-Cima"] = key;
//     
//     key.myInputType = KeyboardInput;
//     key.myEventType = sf::Event::KeyPressed;
//     key.myKeyCode = sf::Keyboard::K;
//     Keys["rinz-Baixo"] = key;
// 
//     key.myInputType = KeyboardInput;
//     key.myEventType = sf::Event::KeyPressed;
//     key.myKeyCode = sf::Keyboard::L;
//     Keys["rinz-Direita"] = key;
// 
//     key.myInputType = KeyboardInput;
//     key.myEventType = sf::Event::KeyPressed;
//     key.myKeyCode = sf::Keyboard::J;
//     Keys["rinz-Esquerda"] = key;
//     
//     key.myInputType = KeyboardInput;
//     key.myEventType = sf::Event::KeyPressed;
//     key.myKeyCode = sf::Keyboard::I;
//     Keys["rinz-Cima"] = key;  
    

    // gameloop
        while(window.pollEvent(Event)){ // eventloop
            // pensar em eventos pra Ganhou e Perdeu
            switch(Event.type){
                //evento para fechar
                case sf::Event::Closed:
                    window.close();
                    return (-1);
                    break;
                //evento quando aumentar/diminuir, necessario ?    
                case sf::Event::Resized:
                    printf("Nova janela com width: %i e com height: %i \n",Event.size.width,Event.size.height);
                    break;
                //"aparece" o q a pessoa escreve
                case sf::Event::TextEntered:
                    if(Event.text.unicode < 128)
                        printf("%c",Event.text.unicode);         
                    break;
               
            }
            // Mudanca de Itens
            if (TestEvent(Keys["item1"], Event)){
                nItem=0;
            }
            if (TestEvent(Keys["item2"], Event)){
                nItem=1;
            }
            if (TestEvent(Keys["item3"], Event)){
                nItem=2;
            }
            if (TestEvent(Keys["item4"], Event)){
                nItem=3;
            }
            if (TestEvent(Keys["item5"], Event)){
                nItem=4;
            }

        }
        itemSelecionado.setPosition(sf::Vector2f(819.0f + 110.0f * nItem ,16.0f));
        itens.remove(item1,deuCerto);
        itens.remove(item,deuCerto);
        itens.insere(item,deuCerto);
        itens.insere(item1,deuCerto);
        window.draw(background);
        window.draw(barraItens);
        window.draw(itemSelecionado);
        for(i=0; i<5; i++)
            window.draw(caixaItem[i]);
        window.draw(item.getItem());
        window.draw(item1.getItem());
        window.draw(barraVida);
        window.display();
       
    
    //Never reaching this point normally, but just in case, exit the application
    }
    return 0;
}
