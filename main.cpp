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


// struct, enum e TestEvent para pegar a tecla e deixar ela "pressionada"
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
    //Lista com itens
    Lista<Item> itens;
    //Variaveis do tipo item para pegar ou enviar um item para a lista
    Item item,item1;
    
    Player tron;
    
    //Sprites para a barra da vida e dos itens
    sf::Sprite barraItens;
    sf::Sprite barraVida;
    
    //Variaveis para carregar as texturas
    sf::Texture vida;
    sf::Texture barra;
    sf::Texture mapa;
    sf::Texture disco;
    //sprite para o background
    sf::Sprite background;
    
    //RectangleShape para as caixas da barra de itens
    sf::RectangleShape caixaItem[5];
    
    //vetor que contem cada id do item contido na caixa
    int idItemCaixa[5];
    
    //variaveis utilizadas para o pulo ser algo crescente/decrescente
    int contPulo=0;
    int contPulo2=0; 
    
    //Caixa que representa qual item está itemSelecionado
    sf::RectangleShape itemSelecionado(sf::Vector2f(52.0f,52.0f));
    
    
    Animation* currentAnimation = &tron.stayAnimation[1];
    
    //variavel que eh utilizada para quando atacar terminar o ataque
    bool atacando=false;
    AnimatedSprite animatedSprite(sf::seconds(0.7), true, false);
    
    //carregamento do disco que pode ser jogado
    sf::Sprite ataqueDisco;
    disco.loadFromFile("Itens/discoLancado.png");
    ataqueDisco.setTexture(disco);
    
    //coloca o heroi na posicao
    animatedSprite.setPosition(sf::Vector2f(1.0f,540.0f));
    
    //escalar da reta que o disco irá passar
    int contDisco =10000;
    
    //clocks que são utilizados para monitorar os ataques, pulos e frames
    sf::Clock frameClock,ataqueClock,puloClock;
    
    //vetor da reta do disco
    sf::Vector2f vetor;
    
    //variaveis para ver qual estado do pulo está
    bool pulando = false;
    bool descendo = false;
    
    //variaveis para verificar se o heroi está se movendo para utilizar com o pulo
    bool andandoDir = false;
    bool andandoEsq = false;
   
    //velocidade dos frames para os casos de direita e esquerda
    float speedDir = 200.f;
    float speedEsq = 200.f;
    
    //verifica se nenhuma tecla está sendo pressionada
    bool noKeyWasPressed = true;
    //i para loop e nItem para ver o numero do item atual
    int i, nItem=0;
    
    //reseta o tron e seta posicao e tamanho
    tron.reset();
    tron.setTamanho(sf::Vector2f(3.0f,3.0f));
    tron.setPosicao(sf::Vector2f(1.0f,540.0f));
    
    //seta cor e posicao para o item selecionado
    itemSelecionado.setFillColor(sf::Color(32, 210, 212));
    itemSelecionado.setPosition(sf::Vector2f(819.0f,16.0f));
    
    //faz  load das imagens e seta a escala 
    barra.loadFromFile("Itens/barraItens.png");
    barraItens.setTexture(barra);
    barraItens.setScale(sf::Vector2f(0.75,0.75));
    vida.loadFromFile("Itens/6vida.png");
    barraVida.setTexture(vida);
    barraVida.setScale(sf::Vector2f(0.85,0.85));
    mapa.loadFromFile("TilesMap/teste.png");
    background.setTexture(mapa);
    background.setScale(sf::Vector2f(4.4f,2.5f));
    
    //para utilizar nos parametros da lista
    bool deuCerto;
    
    //faz load dos itens
    item.carregarItem("disco",3.0f);
    sf::Vector2f pDisco;
    item.setId(1);
    item1.setLocationItem(sf::Vector2f(930.0f,10.0f));
    item1.carregarItem("lanca",3.5f);
    item.setId(2);
    itens.cria();
    
    //times para o tempo de ataque e pulo
    sf::Time tempoAtaque;
    sf::Time tempoPulo;
    
    //seta valores da tela
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!", sf::Style::Fullscreen);
    //seta posicao das barras
    barraItens.setPosition(sf::Vector2f(window.getSize().x - barra.getSize().x * 0.75,0.0f));
    
    //loop para setar a posicao das caixas da barra
    for(i=0; i<5; i++){
        caixaItem[i].setSize(sf::Vector2f(50.0f,50.0f));
        caixaItem[i].setFillColor(sf::Color(35, 77, 77));
        caixaItem[i].setPosition(sf::Vector2f(window.getSize().x - barra.getSize().x * 0.75 + 80  + 80.0f * i,17.0f));
        idItemCaixa[i]=0;
    }
    //seta valores dos id das caixas para realizar teste - nao mexa
    idItemCaixa[0]=1;
    idItemCaixa[1]=2;
    item.setLocationItem(sf::Vector2f(caixaItem[0].getPosition().x - 8 ,caixaItem[0].getPosition().y - 8 ));
    item1.setLocationItem(sf::Vector2f(caixaItem[1].getPosition().x - 3 ,caixaItem[1].getPosition().y - 5 ));
    //adiciona itens na lista
    itens.insere(item,deuCerto);
    itens.insere(item1,deuCerto);
    while (window.isOpen())
    {
        sf::Event Event;

        std::map<std::string,MyKeys> Keys;
        MyKeys key;
        
        //parte para verificar em qual item ficará selecionado
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
        //da um restart no time do frame
        sf::Time frameTime = frameClock.restart();
        sf::Vector2f movement(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pulando && !descendo){
            
            //seta o valor de cada frame
            animatedSprite.setFrameTime(sf::seconds(0.1));
            andandoDir= true;
            andandoEsq=false;
            
            //para o cenário se mover - irá ser mudado para algo mais dinamico
            background.move(- 1.f,0.0f);
            //carrega a animacao do andar para a direita dependendo o id do item
            currentAnimation=&tron.walkingAnimationRight[idItemCaixa[nItem]];
            
            //seta como que vai ser o movimento para o valor de x
            movement.x += speedDir;
            atacando=false;
            noKeyWasPressed = false;
            tron.moverDireita();
        }else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pulando && !descendo){
                animatedSprite.setFrameTime(sf::seconds(0.1));
                background.move(1.f,0.0f);
                andandoDir= false;
                andandoEsq=true;
                currentAnimation = &tron.walkingAnimationLeft[idItemCaixa[nItem]];
                movement.x -= speedEsq;
                atacando=false;
                noKeyWasPressed = false;
                tron.moverEsquerda();
            }else{
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || atacando && !descendo){
                    noKeyWasPressed = false;
                    if(atacando == false){
                        atacando = true;
                        ataqueClock.restart();
                        if(tron.getDirecao() == 1){
                            currentAnimation = &tron.ataqueAnimation[idItemCaixa[nItem]];
                            
                            //dependendo de qual ataque iremos ter uma velocidade e outros fatores diferentes como vetor e pontos
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
                         if(!atacando && !pulando && !descendo){
                             andandoDir= false;
                             andandoEsq=false;
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
        //para o pulo animacoes de descendo e pulando são diferentes, mas são usadas
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X) || pulando || descendo){
                        if(pulando == false && descendo == false){
                            puloClock.restart();
                            pulando = true;
                        }
                        if(!descendo){
                            if(tron.getDirecao() == 1){
                                animatedSprite.setFrameTime(sf::seconds(0.1));
                                currentAnimation = &tron.pulandoDir[idItemCaixa[nItem]];
                            }else{
                                animatedSprite.setFrameTime(sf::seconds(0.1));
                                currentAnimation = &tron.pulandoEsq[idItemCaixa[nItem]];
                            }
                        }else{
                            if(tron.getDirecao() == 1){
                                animatedSprite.setFrameTime(sf::seconds(0.1));
                                currentAnimation = &tron.descendoDir[idItemCaixa[nItem]];
                            }else{
                                animatedSprite.setFrameTime(sf::seconds(0.1));
                                currentAnimation = &tron.descendoEsq[idItemCaixa[nItem]];
                            }
                        }
                        noKeyWasPressed = false;
        }
        //time para o tempo de pulo
        tempoPulo = puloClock.getElapsedTime();
        
        if(pulando){
            if(tempoPulo <= sf::seconds(0.5)){
                movement.y -= contPulo * 7.0f;
                
                //se ele estiver andando o valor de x mexe, alem disso temos uma "parede" para que o ususario não possa sair da tela
                if(andandoDir){
                     if(animatedSprite.getPosition().x < 400 ){
                        movement.x += contPulo * 4.0f;
                        background.move(- 1.f,0.0f);
                    }else{
                        background.move(- 2.f,0.0f);
                    }
                    
                }
                if(andandoEsq){
                    if(animatedSprite.getPosition().x > 1 ){
                        movement.x -= contPulo * 4.0f;
                        background.move( 1.f,0.0f);
                    }else{
                        background.move( 2.f,0.0f);
                    }
                }
                contPulo++;                
                contPulo2++;
               
            }else{
                
                contPulo--;
                pulando = false;
                descendo = true;
            }
        }
        
        if(descendo){
            if(tempoPulo <= sf::seconds(1)){
                movement.y += contPulo * 7.0f;
                if(andandoDir){
                    if(animatedSprite.getPosition().x < 400 ){
                        movement.x += contPulo2 * 4.0f;
                        background.move(- 1.f,0.0f);
                    }else{
                        background.move(- 2.f,0.0f);
                    }
                    
                }
                if(andandoEsq){
                    if(animatedSprite.getPosition().x > 1 ){
                        movement.x -= contPulo2 * 4.0f;
                        background.move(+ 1.f,0.0f);
                    }else{
                        background.move( 2.f,0.0f);
                    }
                    
                }   
                contPulo--;
            }else{
                if(descendo == true)
                    andandoDir=false;
                pulando = false;
                descendo = false;
                contPulo = 0;
                contPulo2=0;
                
            }
        }
        //testes para o heroi não sair da tela
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
        //da um play na animação e move ela
        animatedSprite.play(*currentAnimation );
        animatedSprite.move(movement * frameTime.asSeconds());
        tempoAtaque = ataqueClock.getElapsedTime();
        //teste para setar o ataque do disco
        if(atacando == true && tempoAtaque >= sf::seconds(0.15) && tempoAtaque < sf::seconds(0.20)){
                
            contDisco = 0;
            ataqueDisco.setPosition(pDisco);
        }
        //dependendo do tempo ele irá "sumir" com o disco
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
        //animação do disco indo,  ponto + vetor * escalar
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
