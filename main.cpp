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
    sf::Texture disco;
    sf::Sprite background;
    sf::RectangleShape caixaItem[5];
    int idItemCaixa[5];
    int contPulo=0;
    sf::RectangleShape itemSelecionado(sf::Vector2f(52.0f,52.0f));
    Animation* currentAnimation = &tron.stayAnimation[1];
    bool atacando=false;
    AnimatedSprite animatedSprite(sf::seconds(0.7), true, false);
    sf::Sprite ataqueDisco;
    disco.loadFromFile("Itens/discoLancado.png");
    ataqueDisco.setTexture(disco);
    animatedSprite.setPosition(sf::Vector2f(1.0f,540.0f));
    int contDisco =10000;
    sf::Clock frameClock,ataqueClock,puloClock;
    sf::Vector2f vetor;
    bool pulando = false;
    bool descendo = false;
    bool andandoDir = false;
    float speedDir = 200.f;
    float speedEsq = 200.f;
    bool noKeyWasPressed = true;
    
    int i, nItem=0;
    
    tron.reset();
    tron.setTamanho(sf::Vector2f(3.0f,3.0f));
    tron.setPosicao(sf::Vector2f(1.0f,540.0f));
    
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
    item.carregarItem("disco",3.0f);
    sf::Vector2f pDisco;
    item.setId(1);
    item1.setLocationItem(sf::Vector2f(930.0f,10.0f));
    item1.carregarItem("lanca",3.5f);
    item.setId(2);
    itens.cria();
    sf::Time tempoAtaque;
    sf::Time tempoPulo;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!", sf::Style::Fullscreen);
    barraItens.setPosition(sf::Vector2f(window.getSize().x - barra.getSize().x * 0.75,0.0f));
    
    for(i=0; i<5; i++){
        caixaItem[i].setSize(sf::Vector2f(50.0f,50.0f));
        caixaItem[i].setFillColor(sf::Color(35, 77, 77));
        caixaItem[i].setPosition(sf::Vector2f(window.getSize().x - barra.getSize().x * 0.75 + 80  + 80.0f * i,17.0f));
        idItemCaixa[i]=0;
    }
    idItemCaixa[0]=1;
    idItemCaixa[1]=2;
    item.setLocationItem(sf::Vector2f(caixaItem[0].getPosition().x - 8 ,caixaItem[0].getPosition().y - 8 ));
    item1.setLocationItem(sf::Vector2f(caixaItem[1].getPosition().x - 3 ,caixaItem[1].getPosition().y - 5 ));
    itens.insere(item,deuCerto);
    itens.insere(item1,deuCerto);
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pulando){
            animatedSprite.setFrameTime(sf::seconds(0.1));
            andandoDir= true;
            background.move(- 1.f,0.0f);
            currentAnimation=&tron.walkingAnimationRight[idItemCaixa[nItem]];
            movement.x += speedDir;
            atacando=false;
            noKeyWasPressed = false;
            tron.moverDireita();
        }else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pulando){
                animatedSprite.setFrameTime(sf::seconds(0.1));
                background.move(1.f,0.0f);
                andandoDir= false;
                currentAnimation = &tron.walkingAnimationLeft[idItemCaixa[nItem]];
                movement.x -= speedEsq;
                atacando=false;
                noKeyWasPressed = false;
                tron.moverEsquerda();
            }else{
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || atacando){
                    noKeyWasPressed = false;
                    if(atacando == false){
                        atacando = true;
                        ataqueClock.restart();
                        if(tron.getDirecao() == 1){
                            currentAnimation = &tron.ataqueAnimation[idItemCaixa[nItem]];
                            if(idItemCaixa[nItem] == 1){
                                animatedSprite.setFrameTime(sf::seconds(0.04));
                                pDisco = sf::Vector2f(animatedSprite.getPosition().x + 85, animatedSprite.getPosition().y + 30);
                                vetor.x=1.0;
                                vetor.y=0;
                            }else{
                                vetor.x=1025;
                                animatedSprite.setFrameTime(sf::seconds(0.045));
                            }
                        }else{
                            currentAnimation = &tron.ataqueAnimationEsq[idItemCaixa[nItem]];
                            if(idItemCaixa[nItem] == 1){
                                animatedSprite.setFrameTime(sf::seconds(0.04));
                                pDisco = sf::Vector2f(animatedSprite.getPosition().x, animatedSprite.getPosition().y + 30);
                                vetor.x=-1.0;
                                vetor.y=0;
                            }else{
                                vetor.x=1025;
                                animatedSprite.setFrameTime(sf::seconds(0.045));
                            }
                            
                        }
                        
                    }
                    
                }else{
                         if(!atacando && !pulando){
                             andandoDir= false;
                            if(tron.getDirecao() == 1){
                                animatedSprite.setFrameTime(sf::seconds(0.7));
                                currentAnimation = &tron.stayAnimation[idItemCaixa[nItem]];
                                noKeyWasPressed = false;
                            }else{
                                animatedSprite.setFrameTime(sf::seconds(0.7));
                                currentAnimation = &tron.stayAnimationEsq[idItemCaixa[nItem]];
                                noKeyWasPressed = false;
                            }
                        
                        }
                    
                }
                
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X) || pulando || descendo){
                        if(pulando == false && descendo == false){
                            puloClock.restart();
                            pulando = true;
                        }
                        if(!descendo){
                            animatedSprite.setFrameTime(sf::seconds(0.08));
                            currentAnimation = &tron.pulandoDir[idItemCaixa[nItem]];
                        }else{
                            animatedSprite.setFrameTime(sf::seconds(0.08));
                            currentAnimation = &tron.descendoDir[idItemCaixa[nItem]];
                        }
                        noKeyWasPressed = false;
        }
        tempoPulo = puloClock.getElapsedTime();
        
        if(pulando){
            if(tempoPulo <= sf::seconds(0.4)){
                movement.y -= contPulo * 7.0f;
                if(andandoDir)
                     movement.x += contPulo * 7.0f;
                contPulo++;
            }else{
                contPulo--;
                pulando = false;
                descendo = true;
                
            }
        }
        if(descendo){
            if(tempoPulo <= sf::seconds(0.8)){
                movement.y += contPulo * 7.0f;
                if(andandoDir)
                    movement.x += contPulo * 7.0f;
                contPulo--;
            }else{
                andandoDir=false;
                pulando = false;
                descendo = false;
                contPulo = 0;
                
            }
        }
        if(animatedSprite.getPosition().x >= 400 ){
            speedDir=0.f;
        }else{
            speedDir=200.f;
        }
        if(animatedSprite.getPosition().x <= 1 ){
            speedEsq=0.f;
        }else{
            speedEsq=200.f;
        }
        animatedSprite.play(*currentAnimation );
        animatedSprite.move(movement * frameTime.asSeconds());
        tempoAtaque = ataqueClock.getElapsedTime();
        
        if(atacando == true && tempoAtaque >= sf::seconds(0.15) && tempoAtaque < sf::seconds(0.20)){
                
            contDisco = 0;
            ataqueDisco.setPosition(pDisco);
        }
        if(tempoAtaque >= sf::seconds(0.25) ){
            ataqueDisco.setPosition(sf::Vector2f(-0.1f,-0.1f));
            atacando=false;
        }
        
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        animatedSprite.update(frameTime);
        window.clear();
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
        if((pDisco.x + vetor.x * contDisco) <= 1024.0f && (pDisco.x + vetor.x * contDisco) > 0){
            contDisco++;
            ataqueDisco.setPosition(sf::Vector2f(pDisco.x + vetor.x * contDisco, pDisco.y ));
            window.draw(ataqueDisco);
        }
        window.draw(animatedSprite);
        
        window.display();
       
    
    //Never reaching this point normally, but just in case, exit the application
    }
    return 0;
}
