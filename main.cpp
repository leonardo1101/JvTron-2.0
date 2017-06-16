#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include "Item.hpp"
#include "Lista.hpp"
#include "player.hpp"
#include "AnimatedSprite.hpp"
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
    Player tron;
    sf::Sprite barraItens;
    sf::Sprite barraVida;
    sf::Texture vida;
    sf::Texture barra;
    sf::Texture mapa;
    sf::Sprite background;
    sf::RectangleShape caixaItem[5];
    sf::RectangleShape itemSelecionado(sf::Vector2f(52.0f,52.0f));
    Animation* currentAnimation = &tron.stayAnimation;
    
    AnimatedSprite animatedSprite(sf::seconds(0.7), true, false);
    
    animatedSprite.setPosition(sf::Vector2f(1.0f,558.0f));
    
    sf::Clock frameClock;

    float speed = 200.f;
    bool noKeyWasPressed = true;
    
    int i, nItem=0;
    
    tron.reset();
    tron.setTamanho(sf::Vector2f(3.0f,3.0f));
    tron.setPosicao(sf::Vector2f(1.0f,558.0f));
    
    itemSelecionado.setFillColor(sf::Color(32, 210, 212));
    itemSelecionado.setPosition(sf::Vector2f(819.0f,16.0f));
    barra.loadFromFile("Itens/barraItens.png");
    barraItens.setTexture(barra);
    barraItens.setScale(sf::Vector2f(0.75,0.75));
    vida.loadFromFile("Itens/6vida.png");
    barraVida.setTexture(vida);
    barraVida.setScale(sf::Vector2f(0.85,0.85));
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
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!", sf::Style::Fullscreen);
    barraItens.setPosition(sf::Vector2f(window.getSize().x - barra.getSize().x * 0.75,0.0f));
    
     for(i=0; i<5; i++){
        caixaItem[i].setSize(sf::Vector2f(50.0f,50.0f));
        caixaItem[i].setFillColor(sf::Color(35, 77, 77));
        caixaItem[i].setPosition(sf::Vector2f(window.getSize().x - barra.getSize().x * 0.75 + 80  + 80.0f * i,17.0f));
        
    }
    
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
        sf::Time frameTime = frameClock.restart();
        sf::Vector2f movement(0.f, 0.f);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            animatedSprite.setFrameTime(sf::seconds(0.1));
            currentAnimation = &tron.walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                animatedSprite.setFrameTime(sf::seconds(0.1));
                currentAnimation = &tron.walkingAnimationLeft;
                movement.x -= speed;
                noKeyWasPressed = false;
            }else{
                animatedSprite.setFrameTime(sf::seconds(0.7));
                currentAnimation = &tron.stayAnimation;
                noKeyWasPressed = false;
            }
        }
        
        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        animatedSprite.update(frameTime);

        itemSelecionado.setPosition(sf::Vector2f(window.getSize().x - barra.getSize().x * 0.75 + 79 + 80.0f * nItem ,16.0f));
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
        window.draw(animatedSprite);
        window.display();
       
    
    //Never reaching this point normally, but just in case, exit the application
    }
    return 0;
}
