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
#include "Renderiza.hpp"
#include "SistemaInimigos.hpp"
class Jogo : public Tela{
private:
    Lista<Item> itens;//Lista com itens
    Lista<Disco> discosHeroi; //Lista de Discos
    Lista<Disco> discosInimigos;
    Lista<Inimigo> inimigos;
    Lista<Item> drops;
    SistemaInimigos sistemaInimigos;
    sf::Text tempoTexto;
    void gerarInimigos();
//     //times para o tempo de ataque e pulo
     sf::Time tempoAtaque;
     sf::Time tempoPulo;
     sf::Font fonte;
     int bloco;

    
    BarraItens sistemaItens;
    
    Player tron;
    Inimigo inimigo;
    Inimigo inimigoAux[86];
    int horda;
    int quantInimigos;
    int quantItena;
    Item itensPadrao[5];
    bool setGerarInimigos;
    
    sf::View view,view1;
    
    //Variaveis para carregar as texturas
    sf::Texture vida;
    sf::Texture backgroundT;
    bool procura;
  	sf::Texture groundT;
    
    sf::Sprite background;//sprite para o background
    sf::Sprite ground;//sprite para o background
    
    
    sf::Clock frameClock;//clocks que são utilizados para monitorar os ataques, pulos e frames
    sf::Clock jogoClock;
    
    sf::Time tempoJogo;
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
void Jogo::gerarInimigos(){
    int i, tipo=0;
    float local=0;
    int escada=0;
    int posicaoEscada[7]={800,3320,8320,12180,14900,17900,19920};
    bool ok;
    switch(horda){
        case 0:
            for(i=0;i<14;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                
                printf("\nx = %f",local);
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=14;
            break;
        case 1:
            
            for(i=0;i<28;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                
                printf("\nx = %f",local);
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=28 ;
            break;
        case 2:

            for(i=0;i<42;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                
                printf("\nx = %f",local);
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=42;
            break;
        case 3:

            for(i=0;i<66;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                
                printf("\nx = %f",local);
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=66;
            break;
        case 4:
            for(i=0;i<80;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                printf("\nx = %f",local);
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=80 ;
            break;
    }
    
    
};
Jogo::Jogo(float larg, float Alt){
    bool ok;
    int i;
    bloco=0;
    //reseta o tron e seta posicao e tamanho
    tron.reset();
    tron.setTamanho(sf::Vector2f(3.0f,3.0f));
    tron.setPosicao(sf::Vector2f(1.0f,540.0f));
    setGerarInimigos=false;
    
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
    backgroundT.loadFromFile("TilesMap/teste.png");
    
    background.setTexture(backgroundT);
    background.setScale(sf::Vector2f(3.3f,3.3f));
    background.setPosition(sf::Vector2f(- 768.f, - 2.5f * 64 * 3.5 + 20));
    groundT.loadFromFile("TilesMap/chao.png");
    ground.setTexture(groundT);
    ground.setScale(sf::Vector2f(4.258f,2.5f));
    ground.setPosition(sf::Vector2f(- 189.f, 768 - 2.5f * 64 ));

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
    
    view.setSize(1024, 768);
    view.setCenter(1024/2, 768/2);
    view1.setSize(1024, 768);
    view1.setCenter(1024/2, 768/2);
    sistemaItens.resetBarra();
    sistemaItens.inserirItem(itensPadrao[1]);
    sistemaItens.inserirItem(itensPadrao[2]);
    sistemaItens.inserirItem(itensPadrao[3]);
    

    
    inimigos.cria();
    drops.cria();
        //animação do disco indo,  ponto + vetor * escalar
    fonte.loadFromFile("Tr2n.ttf");
    tempoTexto.setCharacterSize(40);
	tempoTexto.setFont(fonte);
	tempoTexto.setPosition(sf::Vector2f(626 - tempoTexto.getCharacterSize()*3.5, 10.f));
	tempoTexto.setColor(sf::Color::Cyan);
    horda =-1;
    procura=false;
};

Jogo::~Jogo(){
	printf("");
};

int Jogo::Executar(sf::RenderWindow & App){
    int minutos,segundos;
    sf::Vector2f moveInimigo;
    
    Item auxItem;
    //variavel para utilizada para ter certeza de adicionar apenas um disco quando ataca
    bool adicionarUmDisco=false;
    //Variavel para pegar a quantidade de discos jogados pelo heroi
    int quantDiscosHeroi=0;


    //carregamento do disco que pode ser jogado
    Disco disco, discoInimigo;
     
    //Criação da lista disco
    discosHeroi.cria();
    discosInimigos.cria();
    bool setChao = false;

    //verifica se nenhuma tecla está sendo pressionada
    bool noKeyWasPressed = true;
    //i para loop e nItem para ver o numero do item atual
    int i, nItem=0;
    std::map<std::string,MyKeys> Keys;
    MyKeys key;

	//---------------------------  Aqui q vai tudo do jogo. ------------------------------------//
	sf::Event evento; // eventos de jogo
	bool executando = true;
    jogoClock.restart();
    sf::Time aux=jogoClock.getElapsedTime();
	while (executando){
        tempoJogo=jogoClock.getElapsedTime();
        if(segundos == 3){
            if(!setGerarInimigos){
                horda++;
                gerarInimigos();
                setGerarInimigos=true;
                procura=false;
            }
        }else{
            setGerarInimigos=false;
            if(segundos == 20){
                procura=true;
            }
        }
        
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
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !tron.getPulando() && !tron.getAtacando()){

            tron.moverDireita();
            //seta o valor de cada frame

            noKeyWasPressed = false;
            
        }else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !tron.getPulando() && !tron.getAtacando()){

                tron.moverEsquerda();
            }else{
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || tron.getAtacando()) && !tron.getPulando() && !tron.getAndando()){
                    noKeyWasPressed = false;
                    if(!tron.getAtacando()){
                        sistemaItens.usarItem(nItem);
                        tron.atacar();
                        if(tron.adicionarDisco()){
                            if(tron.getDirecao() == 1){
                                disco.setReset(sf::Vector2f(tron.animatedSprite.getPosition().x + 85, tron.animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),0);
                                
                            }else{
                                disco.setReset(sf::Vector2f(tron.animatedSprite.getPosition().x , tron.animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),0);
                            }                              
                        }     
                    }
                }else{
	                if(!tron.getAtacando() && !tron.getPulando() ){
	                     tron.parado();
                         moveInimigo=sf::Vector2f(0.f,0.f);
	                }
                }
                
            }
        }
       
        //para o pulo animacoes de descendo e pulando são diferentes, mas são usadas
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::X) || tron.getPulando()) && !tron.getAtacando()){
            tron.pular();
            noKeyWasPressed = false;
        }
        
            //time para o tempo de pulo
                tron.setTimePulo();
                if(!tron.getPulando()){
                    tron.fakeGravidade(sf::Vector2f(0.f, 768 - 2.5f * 64 ));
                }
                tron.setTimeAtaque();
                
                //teste para adicionar um disco na lista quando precionado a tecla de ataque
                
                if(tron.adicionarDisco()){
                    tron.idDisco++;
                    disco.id = tron.idDisco;
                    discosHeroi.insere(disco,deuCerto);
                    tron.resetDisco();
                }
                bloco++;
            
            
            
    //         if (noKeyWasPressed)
    //         {
    //             
    //         }
                
            view.setCenter(view.getCenter() + tron.getCameraGround());
            noKeyWasPressed = true;
            //
            tron.animatedSprite.update(frameTime);
            App.clear();
            App.setView(view);
            App.draw(background);
            App.draw(ground);
            App.setView(view1);
            App.draw(sistemaItens.barraItens);
            App.draw(sistemaItens.itemSelecionado);
            for(i=0;i<4;i++){
                App.draw(sistemaItens.caixaItem[i]);
            }
            quantItena = sistemaItens.quantItens();
            for(i=0;i<quantItena;i++){
                if(i == 0){
                    sistemaItens.itens.PegaOPrimeiro(auxItem,deuCerto);
                } else
                    sistemaItens.itens.PegaOProximo(auxItem,deuCerto);
                if(!deuCerto)
                    break;
                App.draw(auxItem.getItem());
            }
            
            App.draw(tron.barraVida);
            bloco++;
            
            float auxTempo = tempoJogo.asSeconds();
            int tempo  = static_cast<int>(auxTempo);
            segundos = tempo % 60;
            minutos = (tempo - segundos)/60;
            segundos = segundos % 1;
            segundos = tempo % 60 - segundos;
            std::string auxSegundos = std::to_string(segundos);
            std::string auxMinutos= std::to_string(minutos);
            tempoTexto.setString(auxMinutos + " : " + auxSegundos );
            App.draw(tempoTexto);
        
            
        App.setView(view);
        bool atualInimigos=false, anima = false;
            for(i=0;i<quantInimigos;i++){
                quantDiscosHeroi = discosHeroi.getQuant();
                int j;
                //animação do disco indo,  ponto + vetor * escalar
                for(j=0;j<quantDiscosHeroi;j++){
                    if(i == 0){
                        discosHeroi.PegaOPrimeiro(disco,deuCerto);
                    } else
                        discosHeroi.PegaOProximo(disco,deuCerto);
                    App.draw(disco.getDisco());
                    if(disco.getPosicao().x <= 5000.0f && disco.getPosicao().x > 0){
                        if(disco.Bateu(inimigoAux[i].animatedSprite)  && inimigoAux[i].getVida() > 0 ){
                            inimigoAux[i].tirarVida();
                            anima=true;
                            discosHeroi.removeP(disco,deuCerto);
                            quantDiscosHeroi--;
                        }else{
                            if(i == 0){
                                
                                discosHeroi.removeP(disco,deuCerto);
                                disco.mover();
                                discosHeroi.insere(disco,deuCerto);
                            }
                        }   
                    }else{                       
                        
                        discosHeroi.removeP(disco,deuCerto);
                    }
                }
                if(tron.animatedSprite.getGlobalBounds().intersects(inimigoAux[i].animatedSprite.getGlobalBounds()) && tron.getAtacando() ){
                    
                            inimigoAux[i].tirarVida();
                            anima=true;
                        }
                if(inimigoAux[i].getVida() > 0){ 
                    inimigoAux[i].fakeGravidade(sf::Vector2f(inimigoAux[i].animatedSprite.getPosition().x,ground.getPosition().y));
                    inimigoAux[i].animatedSprite.update(frameTime);
                    bool achou = inimigoAux[i].procurarHeroi(tron.animatedSprite,frameTime);
                    if(procura && !achou)
                        inimigoAux[i].procura(tron.animatedSprite,frameTime);
                    if(!inimigoAux[i].getAtacouDisco() && inimigoAux[i].getAtacando()){
                        if(inimigoAux[i].Bateu(tron.animatedSprite)){
                            tron.perdeVida();
                        }
                    }
                    if(inimigoAux[i].getAtacouDisco()){
                        if(inimigoAux[i].getDirecao() == -1)
                            discoInimigo.setReset(sf::Vector2f(inimigoAux[i].animatedSprite.getPosition().x , inimigoAux[i].animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),1);
                        else
                            discoInimigo.setReset(sf::Vector2f(inimigoAux[i].animatedSprite.getPosition().x + 85, inimigoAux[i].animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),1);
                        inimigoAux[i].setDiscoJogado();
                        
                        discoInimigo.mover(tron.getAndando(),tron.getDirecao(),tron.getPulando());
                        discosInimigos.insere(discoInimigo,deuCerto);
                    }
                    if(!anima)
                     App.draw(inimigoAux[i].animatedSprite);
                  
                }else{
                    if(!inimigoAux[i].statusDrop && drops.getQuant() < 4){
                        inimigoAux[i].statusDrop=true;
                        inimigoAux[i].drop.setPosicao(sf::Vector2f(inimigoAux[i].animatedSprite.getPosition().x ,inimigoAux[i].animatedSprite.getPosition().y                         ));
                        drops.insere(inimigoAux[i].drop,deuCerto);
                    }
                }
                anima=false;
            }
            bloco++;
    
       

        quantDiscosHeroi = discosInimigos.getQuant();
        for(i=0;i<quantDiscosHeroi;i++){
            Disco discoAux;
            discosInimigos.remove(discoAux,deuCerto);
            if(discoAux.getPosicao().x <= 1024.0f && discoAux.getPosicao().x > 0){
                 if(discoAux.Bateu(tron.animatedSprite) ){
                     tron.perdeVida();
                     
                 }else{
                    discoAux.mover(tron.getAndando(),tron.getDirecao(),tron.getPulando());
                    App.draw(discoAux.getDisco());
                    discosInimigos.insere(discoAux,deuCerto);
                }
            }
        }
        int dropItens = drops.getQuant();
        Item drop;
        for(i=0;i<dropItens;i++){
            if(i == 0){
                drops.PegaOPrimeiro(drop,deuCerto);
            }else{
                drops.PegaOProximo(drop,deuCerto);
            }
                if(tron.animatedSprite.getGlobalBounds().intersects(drop.item.getGlobalBounds()) ){
                    drops.removeP(drop,deuCerto);
                    sistemaItens.inserirItem(drop);
                }
                App.draw(drop.item);
                printf("Quantidade de itens: %d\n",dropItens);
            }
            
            
        App.draw(tron.animatedSprite);

        App.draw(inimigo.animatedSprite);
        bloco=0;
        
        App.display();
	}
	//Never reaching this point normally, but just in case, exit the application
	return 0;
};
#endif
