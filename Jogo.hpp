/*
	JvTron: Trabalho 2
	Departamento de Computação
	UFSCar Universidade Federal de São Carlos
	Disciplina: Estrutura de Dados
	Professor: Roberto Ferrari
	Aluno(a):								RA:
		João Gabriel Melo Barbirato			726546
		Leonardo de Oliveira Peralta		726556
		Gabrieli Santos						726523
    
	Controle de Versão: https://github.com/leonardo1101/JvTron-2.0
*/
#ifndef JOGO_H
#define JOGO_H
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tela.hpp"
#include "player.hpp"
#include "Inimigo.hpp"
#include "AnimatedSprite.hpp"
#include "BarraItens.hpp"
#include "Disco.hpp"
#include "Lista.hpp"
#include "Item.hpp"

class Jogo : public Tela{
private:
    Lista<Item> itens;//Lista com itens
    Lista<Disco> discosHeroi; //Lista de Discos
    Lista<Disco> discosInimigos;
    Lista<Inimigo> inimigos;
    sf::RectangleShape caixaItem[5];//RectangleShape para as caixas da barra de itens
    int idItemCaixa[5];//vetor que contem cada id do item contido na caixa
    
    
    
//     //times para o tempo de ataque e pulo
     sf::Time tempoAtaque;
     sf::Time tempoPulo;

    
    BarraItens sistemaItens;
    
    Player tron;
    Inimigo inimigo;
    
    Item itensPadrao[5];
    
    //Sprites para a barra da vida e dos itens
    sf::Sprite barraVida;
    
    //Variaveis para carregar as texturas
    sf::Texture vida;
    sf::Texture backgroundT;
  	sf::Texture groundT;
    
    sf::Sprite background;//sprite para o background
    sf::Sprite ground;//sprite para o background
    
    
    sf::Clock frameClock, ataqueClock, puloClock;//clocks que são utilizados para monitorar os ataques, pulos e frames

    
        //variaveis para verificar se o heroi está se movendo para utilizar com o pulo
    bool andandoDir;
    bool andandoEsq;

    //variaveis para ver qual estado do pulo está
    bool pulando;
	bool descendo;
   
    //velocidade dos frames para os casos de direita e esquerda
    float speedDir;
    float speedEsq;
    
    
    Animation* currentAnimation;

    //para utilizar nos parametros da lista
    bool deuCerto;
public:
	Jogo(float larg, float alt);
	~Jogo();
	virtual int Executar(sf::RenderWindow & app);
};

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

Jogo::Jogo(float larg, float Alt){
    bool ok;
     sistemaItens.resetBarra();
    //reseta o tron e seta posicao e tamanho
    tron.reset();
    tron.setTamanho(sf::Vector2f(3.0f,3.0f));
    tron.setPosicao(sf::Vector2f(1.0f,540.0f));
    
     sistemaItens.resetBarra();
    
    //faz  load das imagens e seta a escala 
// <<<<<<< HEAD
//     barra.loadFromFile("Itens/barraItens.png");
//     barraItens.setTexture(barra);
//     barraItens.setScale(sf::Vector2f(0.75,0.75));
//     std::cout << "TADAIMA!!!" << std::endl;
//     barraVida.setTexture(tron.getPilha().getTopo());
//     std::cout << "TADAIMAAA!!" << std::endl;
// =======
//     vida.loadFromFile("Itens/6vida.png");
//     barraVida.setTexture(vida);
// >>>>>>> 6fadd775963a69e6655a20f0a11bd8fa1238241c
    barraVida.setScale(sf::Vector2f(0.85,0.85));
    backgroundT.loadFromFile("TilesMap/teste.png");
    background.setTexture(backgroundT);
    groundT.loadFromFile("TilesMap/chao.png");
    ground.setTexture(groundT);
    ground.setScale(sf::Vector2f(1.f,2.5f));
    ground.setPosition(sf::Vector2f(0.f, 768 - 2.5f * 64 ));

    itensPadrao[0].carregarItem("",3.0f);
    itensPadrao[0].setId(0);
    itensPadrao[1].carregarItem("disco",2.9f);
    itensPadrao[1].setId(1);
    itensPadrao[1].setQuantidade(6);
    itensPadrao[2].carregarItem("lanca",3.4f);
    itensPadrao[2].setId(2);
    itensPadrao[2].setQuantidade(6);
    itensPadrao[3].carregarItem("pocao",4.5f);
    itensPadrao[3].setId(3);
    itensPadrao[3].setQuantidade(6);
    
    sistemaItens.inserirItem(itensPadrao[1]);
    sistemaItens.inserirItem(itensPadrao[2]);
    sistemaItens.inserirItem(itensPadrao[3]);
            //variaveis para verificar se o heroi está se movendo para utilizar com o pulo
     andandoDir = false;
     andandoEsq = false;

    //variaveis para ver qual estado do pulo está
    pulando = false;
	descendo = false;
   
    //velocidade dos frames para os casos de direita e esquerda
    speedDir = 200.f;
    speedEsq = 200.f;

    //loop para setar a posicao das caixas da barra

    currentAnimation = &tron.stayAnimation[1];
    inimigos.cria();
    inimigo.setTipo(1);
    inimigo.setPosicao(sf::Vector2f(600.0f,ground.getPosition().y - 69));
    inimigos.insere(inimigo,ok);

};

Jogo::~Jogo(){
	printf("");
};

int Jogo::Executar(sf::RenderWindow & App){

//     sistemaItens.inserirItem(itensPadrao[1]);
//     sistemaItens.inserirItem(itensPadrao[2]);

    Item auxItem;
    //variavel para utilizada para ter certeza de adicionar apenas um disco quando ataca
    bool adicionarUmDisco=false;
    //Variavel para pegar a quantidade de discos jogados pelo heroi
    int quantDiscosHeroi=0;
	//variaveis utilizadas para o pulo ser algo crescente/decrescente
    int contPulo = 79;
    int contPulo2 = 0;
    //variavel que eh utilizada para quando atacar terminar o ataque
    bool atacando = false;
    
    //carregamento do disco que pode ser jogado
    Disco disco, discoInimigo;
     
    //Criação da lista disco
    discosHeroi.cria();
    discosInimigos.cria();
    

    AnimatedSprite animatedSprite(sf::seconds(0.7), true, false);
    animatedSprite.setPosition(sf::Vector2f(1.0f,ground.getPosition().y - 140));//coloca o heroi na posicao
    
    //verifica se nenhuma tecla está sendo pressionada
    bool noKeyWasPressed = true;
    //i para loop e nItem para ver o numero do item atual
    int i, nItem=0;
    std::map<std::string,MyKeys> Keys;
    MyKeys key;

	//---------------------------  Aqui q vai tudo do jogo. ------------------------------------//
	sf::Event evento; // eventos de jogo
	bool executando = true;
	while (executando){ // loop da tela
//         if(!tron.getVidaAtual()) // se nao tem vida, retorne 0
//             return 0;
            

//         switch(tron.getVidaAtual()){
//             case 6:
//                 vida.loadFromFile("Itens/6vida.png");
//                 break;
//             case 5:
//                 vida.loadFromFile("Itens/5vida.png");
//                 break;
//             case 4:
//                 vida.loadFromFile("Itens/4vida.png");
//                 break;
//             case 3:
//                 vida.loadFromFile("Itens/3vida.png");
//                 break;
//             case 2:
//                 vida.loadFromFile("Itens/2vida.png");
//                 break;
//             case 1:
//                 vida.loadFromFile("Itens/1vida.png");
//                 break;
//             case 0:
//                 return 0; // vai virar tela de perdeu
//                 break;
//         }

        
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


		while (App.pollEvent(evento)){ // loop de eventos
			if (evento.type == sf::Event::Closed){
				return (-1);
			}
			 // Mudanca de Itens
            if (TestEvent(Keys["item1"], evento)){
                nItem=0;
            }
            if (TestEvent(Keys["item2"], evento)){
                nItem=1;
            }
            if (TestEvent(Keys["item3"], evento)){
                nItem=2;
            }
            if (TestEvent(Keys["item4"], evento)){
                nItem=3;
            }
            if (TestEvent(Keys["item5"], evento)){
                nItem=4;
                
            }
		}
		//da um restart no time do frame
        sf::Time frameTime = frameClock.restart();
        sf::Vector2f movement(0.f, 0.f);
        tron.setTimeFrame(frameClock.restart());
        tron.estadoPulo();
        tron.setIdItem(sistemaItens.selecionarItem(nItem));
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !tron.getPulando()){
            
             inimigo.animatedSprite.move(- 2.f,0.f);
            
            tron.moverDireita();
            //seta o valor de cada frame

            
            //para o cenário se mover - irá ser mudado para algo mais dinamico

            atacando=false;
            noKeyWasPressed = false;
            
        }else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !tron.getPulando() && !descendo){
                inimigo.animatedSprite.move(2.f,0.f);
                atacando=false;
                noKeyWasPressed = false;
                tron.moverEsquerda();
            }else{
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || tron.getAtacando() && !tron.getPulando()){
                    noKeyWasPressed = false;
                    if(!tron.getAtacando()){
                        tron.atacar();
                        sistemaItens.usarItem(nItem);
                        if(tron.adicionarDisco()){
                            if(tron.getDirecao() == 1){
                                disco.setReset(sf::Vector2f(tron.animatedSprite.getPosition().x + 85, tron.animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),0);
                                
                            }else{
                                disco.setReset(sf::Vector2f(tron.animatedSprite.getPosition().x , tron.animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),0);
                            }                              
                        }     
                    }
                }else{
	                if(!atacando && !tron.getPulando()){
	                     tron.parado();
	                }
                }
                
            }
        }
        if(tron.getAtacando() && !tron.adicionarDisco()){
            
            if(tron.animatedSprite.getGlobalBounds().intersects(inimigo.animatedSprite.getGlobalBounds()) )
                printf("mataaaaaaaaaaaaaaaaaaa");
        }
        //para o pulo animacoes de descendo e pulando são diferentes, mas são usadas
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X) || tron.getPulando()){
            tron.pular();
            noKeyWasPressed = false;
        }
        //time para o tempo de pulo
        tron.setTimePulo();
        if(!tron.getPulando()){
             tron.fakeGravidade(ground.getPosition());
        }else{
            if(tron.getDirecao() == 1)
                inimigo.animatedSprite.move(- 2.f,0.f);
            else
                inimigo.animatedSprite.move( 2.f,0.f);
        }
        inimigo.fakeGravidade(sf::Vector2f(inimigo.animatedSprite.getPosition().x,ground.getPosition().y));
        background.move(tron.getCameraBackground());
        ground.move(tron.getCameraGround());
        tron.setTimeAtaque();
        
        //teste para adicionar um disco na lista quando precionado a tecla de ataque
        if(inimigo.getAtacouDisco()){
            if(inimigo.getDirecao() == -1)
                discoInimigo.setReset(sf::Vector2f(inimigo.animatedSprite.getPosition().x , inimigo.animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),1);
            else
                discoInimigo.setReset(sf::Vector2f(inimigo.animatedSprite.getPosition().x + 85, inimigo.animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),1);
            inimigo.setDiscoJogado();
            discosInimigos.insere(discoInimigo,deuCerto);
        }
        if(tron.adicionarDisco()){
            discosHeroi.insere(disco,deuCerto);
            tron.resetDisco();
        }
        
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;
        //
        inimigo.animatedSprite.update(frameTime);
        tron.animatedSprite.update(frameTime);
        App.clear();
        App.draw(ground);
        App.draw(sistemaItens.barraItens);
        App.draw(sistemaItens.itemSelecionado);
         for(i=0;i<4;i++){
             App.draw(sistemaItens.caixaItem[i]);
         }
         int quantItena = sistemaItens.quantItens();
        for(i=0;i<quantItena;i++){
             sistemaItens.itens.remove(auxItem,deuCerto);
             App.draw(auxItem.getItem());
             sistemaItens.itens.insere(auxItem,deuCerto);
         }
         
       
        App.draw(barraVida);
        
        quantDiscosHeroi = discosHeroi.getQuant();
        //animação do disco indo,  ponto + vetor * escalar
        for(i=0;i<quantDiscosHeroi;i++){
            discosHeroi.remove(disco,deuCerto);
            if(disco.getPosicao().x <= 1024.0f && disco.getPosicao().x > 0){
                App.draw(disco.getDisco());
                if(disco.getDisco().getGlobalBounds().intersects(inimigo.animatedSprite.getGlobalBounds()) )
                    printf("mataaaaaaaaaaaaaaaaaaa");
                disco.mover();
                discosHeroi.insere(disco,deuCerto);
            }
        }
        
//         int quantInimigos = inimigos.getQuant();
//         //animação do disco indo,  ponto + vetor * escalar
//         for(i=0;i<quantInimigos;i++){
//             inimigos.remove(inimigo,deuCerto);
//             if(inimigo.getPosicao().x <= 1024.0f && inimigo.getPosicao().x > 0){
//                 App.draw(inimigo.animatedSprite);
//             }
//             inimigos.insere(inimigo,deuCerto);
//         }
        quantDiscosHeroi = discosInimigos.getQuant();
        //animação do disco indo,  ponto + vetor * escalar
        for(i=0;i<quantDiscosHeroi;i++){
            discosInimigos.remove(discoInimigo,deuCerto);
            if(discoInimigo.getPosicao().x <= 1024.0f && discoInimigo.getPosicao().x > 0){
                App.draw(discoInimigo.getDisco());
                discoInimigo.mover();
                discosInimigos.insere(discoInimigo,deuCerto);
            }
        }
        inimigo.procurarHeroi(tron.animatedSprite,frameTime);
        App.draw(inimigo.animatedSprite);
        App.draw(tron.animatedSprite);
        App.display();
	}
	//Never reaching this point normally, but just in case, exit the application
	return 0;
};
#endif
