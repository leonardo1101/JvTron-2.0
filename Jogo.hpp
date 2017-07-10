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
#include "Som.hpp"
class Jogo : public Tela{
private:
    Som sons;
    sf::Music somFundo;
    sf::Music somHeroi;
    sf::Music somInimigo;
    Lista<Item> itens;//Lista com itens
    Lista<Disco> discosHeroi; //Lista de Discos
    Lista<Disco> discosInimigos; //lista com os discos dos inimigos
    Lista<Item> drops; //lista de itens dos drops dos inimigos
    sf::Text tempoTexto;
    void gerarInimigos(); //funcao que gera os inimigos
     
    sf::Font fonte;

    BarraItens sistemaItens; // barra de itens 
    sf::Sprite hordas[5]; //sprite que mostra as hordas
    sf::Texture hordasTexture[5]; //texture das hordas
    Player tron;    //classe player 
    Inimigo inimigoAux[106]; //vetor de inimigos
    int horda; //int para ver qual a horada
    int quantInimigos; // verifica a quantidade de inimigos
    int quantItena; //int para verificar a quantidade de itens
    Item itensPadrao[6]; // vetor que cseta os itens padroes
    bool setGerarInimigos; // boolean para verificar quando setar os inimigos
    
    sf::View view,view1; //views para movimentação de camera
    
    //Variaveis para carregar as texturas
    sf::Texture vida; 
    sf::Texture backgroundT;
    bool procura; //bool utilizada para procurar o heroi
  	sf::Texture groundT;
    
    sf::Sprite background;//sprite para o background
    sf::Sprite ground;//sprite para o background
    
    Disco discoHeroi[42];
    sf::Clock frameClock;//clocks que são utilizados para monitorar os ataques, pulos e frames
    sf::Clock jogoClock;
    
    sf::Time tempoJogo;//verifica o tempo do jogo
    //para utilizar nos parametros da lista
    int idInimigo;  //int para os ids dos inimigos
    bool deuCerto;
    int minutos,segundos; //int para segundos e minutos do tempo
    bool atualInimigos=false, anima = false;
    float auxTempo;
    int tempo ;
    Item auxItem; //auxiliar para o tempo
    //variavel para utilizada para ter certeza de adicionar apenas um disco quando ataca
    bool adicionarUmDisco=false;
    //Variavel para pegar a quantidade de discos jogados pelo heroi
    int j; // contador j
    int comecoInimigo; //onde começa os inimigos
    bool achou; //se achou o heroi

    //carregamento do disco que pode ser jogado
    Disco disco, discoInimigo;
     
    //Criação da lista disco
   
public:
	Jogo(float larg, float alt);
    void reset(float larg, float alt);
	~Jogo();
    void AcoesInimigo(sf::Time,sf::RenderWindow & App);
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
//opção para jogar novamente
 void Jogo::reset(float larg, float alt){
     bool ok;
    int i;
    
    //reseta o tron e seta posicao e tamanho
    tron.reset();
    tron.setTamanho(sf::Vector2f(3.0f,3.0f));
    tron.setPosicao(sf::Vector2f(1.0f,540.0f));
    setGerarInimigos=false;
    //seta a posicao das sprites da horda
    hordasTexture[0].loadFromFile("Arts/1horda.png");
    hordasTexture[1].loadFromFile("Arts/2horda.png");
    hordasTexture[2].loadFromFile("Arts/3horda.png");
    hordasTexture[3].loadFromFile("Arts/4horda.png");
    hordasTexture[4].loadFromFile("Arts/5horda.png");
    
    for(i=0;i<5;i++){
        hordas[i].setTexture(hordasTexture[i]);
        hordas[i].setScale(sf::Vector2f(3.f,3.f));
        hordas[i].setPosition(sf::Vector2f(512 - (hordasTexture[i].getSize().x/2)*3 , 768/2 - (hordasTexture[i].getSize().y/2)*3  ));
    }
    //seta o background e o ground
    backgroundT.loadFromFile("TilesMap/teste.png");
    
    background.setTexture(backgroundT);
    background.setScale(sf::Vector2f(3.3f,3.3f));
    background.setPosition(sf::Vector2f(- 768.f, - 2.5f * 64 * 3.5 + 20));
    groundT.loadFromFile("TilesMap/chao.png");
    ground.setTexture(groundT);
    ground.setScale(sf::Vector2f(4.258f,2.5f));
    ground.setPosition(sf::Vector2f(- 189.f, 768 - 2.5f * 64 ));
    //seta os valores das cameras
    view.setSize(1024, 768);
    view.setCenter(1024/2, 768/2);
    view1.setSize(1024, 768);
    view1.setCenter(1024/2, 768/2);
    //seta os valores da barra e insere os itens iniciais
    sistemaItens.resetBarra();
    sistemaItens.inserirItem(itensPadrao[1]);
    sistemaItens.inserirItem(itensPadrao[2]);
    sistemaItens.inserirItem(itensPadrao[3]);
    sistemaItens.inserirItem(itensPadrao[4]);

    fonte.loadFromFile("Tr2n.ttf");
    tempoTexto.setCharacterSize(40);
	tempoTexto.setFont(fonte);
	tempoTexto.setPosition(sf::Vector2f(626 - tempoTexto.getCharacterSize()*3.5, 10.f));
	tempoTexto.setColor(sf::Color::Cyan);
    //inicia contadores de horda,id,quant,procura
    horda =0;
    idInimigo=0;
    quantInimigos=0;
    comecoInimigo=0;
    procura=false;
}
//funcao que gera os inimigos e a posicao inicial deles
void Jogo::gerarInimigos(){
    int i, tipo=0;
    float local=0;
    int escada=0;
    int posicaoEscada[7]={800,3320,8320,12180,14900,17900,19920};
    bool ok;
    switch(horda){
        case 0:
            for(i=0;i<7;i++){
                comecoInimigo=0;
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=7;
            break;
        case 1:
             comecoInimigo=quantInimigos+comecoInimigo;
            for(i=comecoInimigo;i<comecoInimigo+7;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=7 ;
            break;
        case 2:
            comecoInimigo=quantInimigos+comecoInimigo;
            for(i=comecoInimigo;i<7+comecoInimigo;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=7;
            break;
        case 3:
            comecoInimigo=quantInimigos+comecoInimigo;
            for(i=comecoInimigo;i<7+comecoInimigo;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=7;
            break;
        case 4:
            comecoInimigo=quantInimigos+comecoInimigo;
            for(i=comecoInimigo;i<7+comecoInimigo;i++){
                tipo=rand() % 2 + 1;
                inimigoAux[i].setTipo(tipo);
                local = rand() %  400 + posicaoEscada[escada];
                inimigoAux[i].setPosicao(sf::Vector2f(local,ground.getPosition().y - 69));
                if(escada == 6)
                    escada=0;
                else
                    escada++;
            }
            quantInimigos=7 ;
            break;
    }
    
    
    
};
Jogo::Jogo(float larg, float Alt){
    bool ok;
    int i;
    //reseta o tron e seta posicao e tamanho
    tron.reset();
    tron.setTamanho(sf::Vector2f(3.0f,3.0f));
    tron.setPosicao(sf::Vector2f(1.0f,540.0f));
    setGerarInimigos=false;
    //seta a posicao das sprites da horda
    hordasTexture[0].loadFromFile("Arts/1horda.png");
    hordasTexture[1].loadFromFile("Arts/2horda.png");
    hordasTexture[2].loadFromFile("Arts/3horda.png");
    hordasTexture[3].loadFromFile("Arts/4horda.png");
    hordasTexture[4].loadFromFile("Arts/5horda.png");
    for(i=0;i<5;i++){
        hordas[i].setTexture(hordasTexture[i]);
        hordas[i].setScale(sf::Vector2f(3.f,3.f));
        hordas[i].setPosition(sf::Vector2f(512 - (hordasTexture[i].getSize().x/2)*3 , 768/2 - (hordasTexture[i].getSize().y/2)*3  ));
    }
     //seta o background e o ground
    backgroundT.loadFromFile("TilesMap/teste.png");
    
    background.setTexture(backgroundT);
    background.setScale(sf::Vector2f(3.3f,3.3f));
    background.setPosition(sf::Vector2f(- 768.f, - 2.5f * 64 * 3.5 + 20));
    groundT.loadFromFile("TilesMap/chao.png");
    ground.setTexture(groundT);
    ground.setScale(sf::Vector2f(4.258f,2.5f));
    ground.setPosition(sf::Vector2f(- 189.f, 768 - 2.5f * 64 ));
    //cria os itens padrões
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
    itensPadrao[4].carregarItem("discoDois",4.5f);
    itensPadrao[4].setId(4);
    itensPadrao[4].setQuantidade(6);
     //seta os valores das cameras
    view.setSize(1024, 768);
    view.setCenter(1024/2, 768/2);
    view1.setSize(1024, 768);
    view1.setCenter(1024/2, 768/2);
    //seta os valores da barra e insere os itens iniciais
    sistemaItens.resetBarra();
    sistemaItens.inserirItem(itensPadrao[1]);
    sistemaItens.inserirItem(itensPadrao[2]);
    sistemaItens.inserirItem(itensPadrao[3]);
    sistemaItens.inserirItem(itensPadrao[4]);
    //cria o sistema de drops
    drops.cria();
        //animação do disco indo,  ponto + vetor * escalar
    fonte.loadFromFile("Tr2n.ttf");
    tempoTexto.setCharacterSize(40);
	tempoTexto.setFont(fonte);
	tempoTexto.setPosition(sf::Vector2f(626 - tempoTexto.getCharacterSize()*3.5, 10.f));
	tempoTexto.setColor(sf::Color::Cyan);
    horda =0;
    idInimigo=0;
    procura=false;
};

Jogo::~Jogo(){
	printf("");
};

int Jogo::Executar(sf::RenderWindow & App){
    sons.musica(somFundo,deuCerto); //som da musica de fundo
     discosHeroi.cria(); //cria a lista de disco do heroi
    discosInimigos.cria();//cria a lista de disco do inimigo
    Disco dUm,dDois; //discos auxiliares
    int drawHorda =0; // verifica qual horda mostrar
    tron.idDisco=0; //set o id dos discos
    bool pulou=false;
    //verifica se nenhuma tecla está sendo pressionada
    bool noKeyWasPressed = true;
    //i para loop e nItem para ver o numero do item atual
    int i, nItem=0;
    std::map<std::string,MyKeys> Keys;
    MyKeys key;
	sf::Event evento; // eventos de jogo
	bool executando = true;
    jogoClock.restart(); //seta o clock do jogo
    sf::Time aux=jogoClock.getElapsedTime();
	while (executando){
        tempoJogo=jogoClock.getElapsedTime();
        if(segundos == 3 ){ // se for 3 segundos ele ira mostrar qual eh a horda e gerar inimigos
            if(!setGerarInimigos){
                gerarInimigos();
                horda++; 
                drawHorda++;
                setGerarInimigos=true;
                procura=false;
            }
        }else{
            setGerarInimigos=false;
            if(segundos == 10){ //comeca a procurar o heroi
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
        //seta qual item o heroi esta usando no momento
        tron.setIdItem(sistemaItens.selecionarItem(nItem));
        
        //movimentos do heroi
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !tron.getPulando() && !tron.getAtacando()){
            
            if(!(tron.animatedSprite.getPosition().x > 21040.0f && tron.animatedSprite.getPosition().x <  21080.0f)){
                tron.moverDireita();
                view.setCenter(view.getCenter() + tron.getCameraGround());
                
            }
            
        }else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !tron.getPulando() && !tron.getAtacando()){
                if(!(tron.animatedSprite.getPosition().x > - 280.0f && tron.animatedSprite.getPosition().x < - 200.0f)){
                    tron.moverEsquerda();
                    view.setCenter(view.getCenter() + tron.getCameraGround());
                }
            }else{
                //ataque no heroi
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || tron.getAtacando()) && !tron.getPulando() && !tron.getAndando()){
                    if(!tron.getAtacando()){
                        //o heroi esta usando um item
                        sistemaItens.usarItem(nItem);
                        tron.atacar();
                        //caso o heroi esteja com o disco e ele atacar será adicionado um disco da lista de discos do heroi
                        if(tron.adicionarDisco()){
                            if(tron.getDirecao() == 1){
                                disco.setReset(sf::Vector2f(tron.animatedSprite.getPosition().x + 85, tron.animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),0);
                                
                            }else{
                                disco.setReset(sf::Vector2f(tron.animatedSprite.getPosition().x , tron.animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),0);
                            }                              
                        } 
                        if(tron.getAdicionarDoisDiscos()){
                            dUm.setReset(sf::Vector2f(tron.animatedSprite.getPosition().x , tron.animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),0);
                            dDois.setReset(sf::Vector2f(tron.animatedSprite.getPosition().x + 85, tron.animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),0);
                        }
                        if(tron.getAtacando() && tron.getIdItem() == 2){
                            
                            sons.emiteSomBarra(somHeroi,deuCerto);
                        }
                        
                    }
                }else{
	                if(!tron.getAtacando() && !tron.getPulando() ){
	                     tron.parado();
                         view.setCenter(view.getCenter() + tron.getCameraGround());
	                }
                }
                
            }
        }
        
        //para o pulo animacoes de descendo e pulando são diferentes, mas são usadas
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::X) || tron.getPulando()) && !tron.getAtacando()){
             if(!(tron.animatedSprite.getPosition().x > 21040.0f && tron.animatedSprite.getPosition().x <  21080.0f) &&
                !(tron.animatedSprite.getPosition().x > - 280.0f && tron.animatedSprite.getPosition().x < - 200.0f)){
                    tron.pular();
                    if(!pulou){
                        sons.emiteSomPulo(somHeroi,deuCerto);
                        pulou=true;
                    }
                    view.setCenter(view.getCenter() + tron.getCameraGround());
             }
        }else{
            pulou=false;
        }
        
            //time para o tempo de pulo
                tron.setTimePulo();
                if(!tron.getPulando()){
                    //gravidade para o heroi
                    tron.fakeGravidade(sf::Vector2f(0.f, 768 - 2.5f * 64 ));
                }
                tron.setTimeAtaque();
                
                //teste para adicionar um disco na lista quando precionado a tecla de ataque
                if(tron.adicionarDisco()){
                    tron.idDisco++;
                    disco.id = tron.idDisco;
                    discosHeroi.insere(disco,deuCerto);
                    sons.emiteSomDisco(somHeroi,deuCerto);
                    tron.resetDisco();
                }
                //verifica se ele esta usando o item de lancar dois discos
                if(tron.getAdicionarDoisDiscos()){
                    
                    sons.emiteSomDisco(somHeroi,deuCerto);
                    tron.idDisco++;
                    dUm.id = tron.idDisco;
                    discosHeroi.insere(dUm,deuCerto);
                    tron.idDisco++;
                    dDois.id = tron.idDisco;
                    discosHeroi.insere(dDois,deuCerto);
                    tron.resetDisco();
                    
                    sons.emiteSomDisco(somHeroi,deuCerto);
                }
            
            
                
            tron.animatedSprite.update(frameTime);
            App.clear();
            //seta a camera e desenha os compnente corretamente na tela
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
            auxTempo = tempoJogo.asSeconds();
            tempo  = static_cast<int>(auxTempo);
            segundos = tempo % 60;
            minutos = (tempo - segundos)/60;
            segundos = segundos % 1;
            segundos = tempo % 60 - segundos;
            std::string auxSegundos = std::to_string(segundos);
            std::string auxMinutos= std::to_string(minutos);
            tempoTexto.setString(auxMinutos + " : " + auxSegundos );
            App.draw(tempoTexto);
            
            if(segundos == 3   ){
                App.draw(hordas[minutos]);
            }
            if(minutos == 5   ){
                return 4;
            }else{
                if(tron.getVida() == 0   ){
                    return 5;
                }
            }
            
        App.setView(view);
        
       atualInimigos=false;
       anima = false;
        
       AcoesInimigo(frameTime,App);
       //percorre a lista de discos do heroi
           Disco discoAux;
         discosHeroi.PegaOPrimeiro(discoAux,deuCerto);
         int j=0;
         while(deuCerto){
            App.draw(discoAux.getDisco());
            discoAux.mover();
            discosHeroi.atualizaP(discoAux,deuCerto);
            discoHeroi[j]=discoAux;
            Disco discoInserir = discoAux;
            j++;
            discosHeroi.PegaOProximo(discoAux,deuCerto);
         }
       
        //percorre os discos do heroi
         int quantDiscosInimigo = discosInimigos.getQuant();
        for(i=0;i<quantDiscosInimigo;i++){
             Disco discoAuxInimigo;
            if(i == 0){
                discosInimigos.PegaOPrimeiro(discoAuxInimigo,deuCerto);
            }else{
                discosInimigos.PegaOProximo(discoAuxInimigo,deuCerto);
            }
            discosInimigos.removeP(discoAuxInimigo,deuCerto);
            if(discoAuxInimigo.getPosicao().x <= view.getCenter().x + 600 && discoAuxInimigo.getPosicao().x >view.getCenter().x - 600 ){
                 if(discoAuxInimigo.Bateu(tron.animatedSprite) ){
                     tron.perdeVida();
                 }else{
                    App.draw(discoAuxInimigo.desenho);
                    discoAuxInimigo.mover(tron.getAndando(),tron.getDirecao(),tron.getPulando());
                    discosInimigos.insere(discoAuxInimigo,deuCerto);
                }
            }
        }
        //percorre a lista de drops
        int dropItens = drops.getQuant();
        Item drop;
        drops.PegaOPrimeiro(drop,deuCerto);
        while(deuCerto){
            if(drop.Bateu(tron.animatedSprite) ){
                drops.removeP(drop,deuCerto);
                sistemaItens.inserirItem(drop);
            }else{
                App.draw(drop.itemDrop);
            }
            drops.PegaOProximo(drop,deuCerto);
        }
  
            
            
        App.draw(tron.animatedSprite);

        
        App.display();
	}
	//Never reaching this point normally, but just in case, exit the application
	return 0;
};
//percorre o vetor dos inimigos verificando se fora lancado o disco ou se o disco do heroi bateu em alguem
void Jogo::AcoesInimigo(sf::Time frameTime,sf::RenderWindow & App){
    int i;
            for(i=comecoInimigo;i<quantInimigos+comecoInimigo;i++){
              int  quantDiscos = discosHeroi.getQuant();
                 int j=0;
                //animação do disco indo,  ponto + vetor * escalar
                for(j=0;j<quantDiscos;j++){
                    if(discoHeroi[j].getPosicao().x <= view.getCenter().x + 600 && discoHeroi[j].getPosicao().x > view.getCenter().x - 600){
                        if(discoHeroi[j].Bateu(inimigoAux[i].animatedSprite)  && inimigoAux[i].getVida() > 0 ){
                            inimigoAux[i].tirarVida();
                            anima=true;
                            discosHeroi.removeP(discoHeroi[j],deuCerto);
                            quantDiscos--;
                        }  
                    }else{                       
                        
                        discosHeroi.removeP(discoHeroi[j],deuCerto);
                    }
                }
                if(tron.Bateu(inimigoAux[i].animatedSprite) && tron.getAtacando() && !tron.pocaoUsando ){
                    
                            inimigoAux[i].tirarVida();
                            anima=true;
                        }
                if(inimigoAux[i].getVida() > 0){ 
                    inimigoAux[i].fakeGravidade(sf::Vector2f(inimigoAux[i].animatedSprite.getPosition().x,ground.getPosition().y));
                    inimigoAux[i].animatedSprite.update(frameTime);
                    achou = inimigoAux[i].procurarHeroi(tron.animatedSprite,frameTime);
                    if(procura && !achou)
                        inimigoAux[i].procura(tron.animatedSprite,frameTime);
                    if(!inimigoAux[i].getAtacouDisco() && inimigoAux[i].getAtacando()){
                        if(inimigoAux[i].Bateu(tron.animatedSprite) && inimigoAux[i].getAtacando() && !inimigoAux[i].andando ){
                            sons.emiteSomBarra(somInimigo,deuCerto);
                            tron.perdeVida();
                        }
                    }
                    if(inimigoAux[i].getAtacouDisco()){
                        if(inimigoAux[i].getDirecao() == -1)
                            discoInimigo.setReset(sf::Vector2f(inimigoAux[i].animatedSprite.getPosition().x , inimigoAux[i].animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),1);
                        else
                            discoInimigo.setReset(sf::Vector2f(inimigoAux[i].animatedSprite.getPosition().x + 85, inimigoAux[i].animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),1);
                        inimigoAux[i].setDiscoJogado();
                        discoInimigo.id=idInimigo;
                        idInimigo++;
                        discoInimigo.mover(tron.getAndando(),tron.getDirecao(),tron.getPulando());
                        discosInimigos.insere(discoInimigo,deuCerto);
                        sons.emiteSomDisco(somInimigo,deuCerto);
                    }
                    if(!anima)
                     App.draw(inimigoAux[i].animatedSprite);
                  
                }else{
                    if(!inimigoAux[i].statusDrop && drops.getQuant() < 4){
                        inimigoAux[i].statusDrop=true;
                        inimigoAux[i].drop.setPosicao(sf::Vector2f(inimigoAux[i].animatedSprite.getPosition().x + 80 ,inimigoAux[i].animatedSprite.getPosition().y + 75 ));
                        drops.insere(inimigoAux[i].drop,deuCerto);
                    }
                }
                anima=false;
            }
}
#endif
