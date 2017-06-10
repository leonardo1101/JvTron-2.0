#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Item.hpp"
#include "Lista.hpp"
#include <string>


int main (){
    Lista<Item> itens;
    Item item,item1;
    sf::Sprite barraItens;
    sf::Texture barra;
    barra.loadFromFile("Itens/barraItens.png");
    barraItens.setTexture(barra);
    sf::RectangleShape teste(sf::Vector2f(100.0f,100.0f));
    teste.setFillColor(sf::Color(100, 250, 50));
    bool deuCerto;
    
    item.setLocationItem(sf::Vector2f(2.0f,2.0f));
    item.carregarItem("lanca");
    itens.cria();
    itens.insere(item,deuCerto);
    sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!", sf::Style::Fullscreen);
    barraItens.setPosition(sf::Vector2f(1366.0f - barra.getSize().x,0.0f));
    while (window.isOpen())
    {
    sf::Event Event;

//     std::map<std::string,MyKeys> Keys;
//     MyKeys key;
// 
//     key.myInputType = KeyboardInput;
//     key.myEventType = sf::Event::KeyPressed;
//     key.myKeyCode = sf::Keyboard::D;
//     Keys["tron-Direita"] = key;
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
//             // teclas tron
//             if (TestEvent(Keys["tron-Direita"], Event)){
//                 iT = 50;
// //                 aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
//                 aux = tron.getForma().getPosition() + tron.getFimCauda();
//                 tron.mudarDireita();
//                  virou=true; 
//             }
//             if (TestEvent(Keys["tron-Esquerda"], Event)){
//                 iT = 50;
// //                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
//                 aux = tron.getForma().getPosition() + tron.getFimCauda();
//                 tron.mudarEsquerda(); 
//                  virou=true; 
//             }
//             if (TestEvent(Keys["tron-Cima"], Event)){
//                 iT = 50;
// //                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
//                 aux = tron.getForma().getPosition() + tron.getFimCauda();
//                 tron.mudarCima();
//                  virou=true; 
//             }
//             if (TestEvent(Keys["tron-Baixo"], Event)){
//                 iT = 50;
// //                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
//                 aux = tron.getForma().getPosition() + tron.getFimCauda();
//                 tron.mudarBaixo();
//                  virou=true; 
//             }
// 
//             // teclas rinzzler
//             if (TestEvent(Keys["rinz-Direita"], Event)){
//                 iR = 50;
//                 virou=true; 
// //                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
//                 aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
//                 rinz.mudarDireita();
//             }
//             if (TestEvent(Keys["rinz-Esquerda"], Event)){
//                 iR = 50;
//                 virou=true;
// //                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
//                 aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
//                 rinz.mudarEsquerda(); 
//             }
//             if (TestEvent(Keys["rinz-Cima"], Event)){
//                 iR = 50;
//                 virou=true;
// //                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
//                 aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
//                 rinz.mudarCima();
//             }
//             if (TestEvent(Keys["rinz-Baixo"], Event)){
//                 iR = 50;    
//                 virou=true;
// //                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
//                 aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
//                 rinz.mudarBaixo();
//             }
        }
        
        itens.remove(item1,deuCerto);
        itens.insere(item,deuCerto);
//         window.draw(teste);
        window.draw(barraItens);
//         window.draw(item1.getItem());
        window.display();
       
    
    //Never reaching this point normally, but just in case, exit the application
    }
    return 0;
}
