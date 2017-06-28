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
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tela.hpp"
#include "Item.hpp"
#include "Lista.hpp"
#include "player.hpp"
#include "Inimigo.hpp"
#include "AnimatedSprite.hpp"
#include "Disco.hpp"

class Jogo : public Tela{
private:
    Lista<Item> itens;//Lista com itens
    Lista<Disco> discosHeroi; //Lista de Discos
    Lista<Disco> discosInimigos;
    
    Item itensPadrao[5];//Variaveis do tipo item para pegar ou enviar um item para a lista
    sf::RectangleShape caixaItem[5];//RectangleShape para as caixas da barra de itens
    int idItemCaixa[5];//vetor que contem cada id do item contido na caixa
    sf::RectangleShape * itemSelecionado;
    
    Player tron;
    Inimigo inimigo;
    
    //Sprites para a barra da vida e dos itens
    sf::Sprite barraItens;
    sf::Sprite barraVida;
    
    //Variaveis para carregar as texturas
    sf::Texture vida;
    sf::Texture barra;
    sf::Texture backgroundT;
  	sf::Texture groundT;
    
    sf::Sprite background;//sprite para o background
    sf::Sprite ground;//sprite para o background
    
    
    sf::Clock frameClock, ataqueClock, puloClock;//clocks que são utilizados para monitorar os ataques, pulos e frames

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
<<<<<<< HEAD
    //std::cout << tron.getPilha().getNumeroElementos() << std::endl;
	itemSelecionado = new sf::RectangleShape(sf::Vector2f(52.0f,52.0f));
=======
>>>>>>> 6fadd775963a69e6655a20f0a11bd8fa1238241c
    //reseta o tron e seta posicao e tamanho
    tron.reset();
    tron.setTamanho(sf::Vector2f(3.0f,3.0f));
    tron.setPosicao(sf::Vector2f(1.0f,540.0f));
    
    //faz  load das imagens e seta a escala 
<<<<<<< HEAD
    barra.loadFromFile("Itens/barraItens.png");
    barraItens.setTexture(barra);
    barraItens.setScale(sf::Vector2f(0.75,0.75));
    std::cout << "TADAIMA!!!" << std::endl;
    barraVida.setTexture(tron.getPilha().getTopo());
    std::cout << "TADAIMAAA!!" << std::endl;
=======
    vida.loadFromFile("Itens/6vida.png");
    barraVida.setTexture(vida);
>>>>>>> 6fadd775963a69e6655a20f0a11bd8fa1238241c
    barraVida.setScale(sf::Vector2f(0.85,0.85));
    backgroundT.loadFromFile("TilesMap/teste.png");
    background.setTexture(backgroundT);
    groundT.loadFromFile("TilesMap/chao.png");
    ground.setTexture(groundT);
    ground.setScale(sf::Vector2f(1.f,2.5f));
    ground.setPosition(sf::Vector2f(0.f, 768 - 2.5f * 64 ));

    itensPadrao[0].carregarItem("",3.0f);
    itensPadrao[0].setId(0);
    itensPadrao[1].carregarItem("disco",3.0f);
    itensPadrao[1].setId(1);
    itensPadrao[2].carregarItem("lanca",3.4f);
    itensPadrao[2].setId(2);
    itensPadrao[3].carregarItem("pocao",3.4f);
    itensPadrao[3].setId(3);
    itensPadrao[4].carregarItem("discoLancadoInimigo",3.f);
    itensPadrao[4].setId(4);


    //loop para setar a posicao das caixas da barra



};

Jogo::~Jogo(){
	delete itemSelecionado;
};

int Jogo::Executar(sf::RenderWindow & App){
    //variavel para utilizada para ter certeza de adicionar apenas um disco quando ataca
    bool adicionarUmDisco=false;
    //Variavel para pegar a quantidade de discos jogados pelo heroi
    int quantDiscosHeroi=0;
	//variaveis utilizadas para o pulo ser algo crescente/decrescente
    int contPulo = 79;
    int contPulo2 = 0;
    Animation* currentAnimation = &tron.stayAnimation[1];
    //variavel que eh utilizada para quando atacar terminar o ataque
    bool atacando = false;
    inimigo.setTipo(2);
    inimigo.setPosicao(sf::Vector2f(600.0f,ground.getPosition().y - 69));
    AnimatedSprite animatedSprite(sf::seconds(0.7), true, false);
    animatedSprite.setPosition(sf::Vector2f(1.0f,ground.getPosition().y - 140));//coloca o heroi na posicao
    //carregamento do disco que pode ser jogado
    Disco disco, discoInimigo;
     
    //Criação da lista disco
    discosHeroi.cria();
    discosInimigos.cria();
        
    //variaveis para verificar se o heroi está se movendo para utilizar com o pulo
    bool andandoDir = false;
    bool andandoEsq = false;

    //variaveis para ver qual estado do pulo está
    bool pulando = false;
	bool descendo = false;
   
    //velocidade dos frames para os casos de direita e esquerda
    float speedDir = 200.f;
    float speedEsq = 200.f;
    
    //verifica se nenhuma tecla está sendo pressionada
    bool noKeyWasPressed = true;
    //i para loop e nItem para ver o numero do item atual
    int i, nItem=0;

    //times para o tempo de ataque e pulo
    sf::Time tempoAtaque;
    sf::Time tempoPulo;

	//---------------------------  Aqui q vai tudo do jogo. ------------------------------------//
	sf::Event evento; // eventos de jogo
	bool executando = true;
	while (executando){ // loop da tela
        if(!tron.getVidaAtual()) // se nao tem vida, retorne 0
            return 0;
            

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

		// Verificação de eventos
       
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pulando && !descendo){
            
            inimigo.animatedSprite.move(- 1.0f,0.f);
            
            //seta o valor de cada frame
            animatedSprite.setFrameTime(sf::seconds(0.1));
            andandoDir= true;
            andandoEsq=false;
            
            //para o cenário se mover - irá ser mudado para algo mais dinamico
            background.move(- 2.f,0.0f);
            ground.move(- 1.f,0.0f);
            //carrega a animacao do andar para a direita dependendo o id do item
            currentAnimation=&tron.walkingAnimationRight[idItemCaixa[nItem]];
            
            //seta como que vai ser o movimento para o valor de x
            movement.x += speedDir;
            atacando=false;
            noKeyWasPressed = false;
            tron.moverDireita();
        }else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pulando && !descendo){
                inimigo.animatedSprite.move(1.f,0.f);
                animatedSprite.setFrameTime(sf::seconds(0.1));
                background.move(2.f,0.0f);
                ground.move(1.f,0.0f);
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
                                
                                //seta o vetor e o ponto do disco a ser lançado
                                disco.setReset(sf::Vector2f(animatedSprite.getPosition().x + 85, animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),0);
                                adicionarUmDisco=true;
                            }else{
                                animatedSprite.setFrameTime(sf::seconds(0.045));
                            }
                        }else{
                            currentAnimation = &tron.ataqueAnimationEsq[idItemCaixa[nItem]];
                            if(idItemCaixa[nItem] == 1){
                                animatedSprite.setFrameTime(sf::seconds(0.04));
                                
                                //seta o vetor e o ponto do disco a ser lançado
                                disco.setReset(sf::Vector2f(animatedSprite.getPosition().x , animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),0);
                                adicionarUmDisco=true;
            
                            }else{
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
        if(!pulando && !descendo)
             animatedSprite.setPosition(sf::Vector2f(animatedSprite.getPosition().x,ground.getPosition().y - 140));
        
        
        
        if(pulando){
            if(tempoPulo <= sf::seconds(0.5)){
                movement.y -= contPulo * 7.0f;
                
                //se ele estiver andando o valor de x mexe, alem disso temos uma "parede" para que o ususario não possa sair da tela
                if(andandoDir){
                     if(animatedSprite.getPosition().x < 400 ){
                        movement.x += contPulo * 4.0f;
                        background.move(- 2.f,0.0f);
                        ground.move(- 1.f,0.f);
                    }else{
                        background.move(- 4.f,0.0f);
                        ground.move(- 2.f,0.f);
                    }
                }
                if(andandoEsq){
                    if(animatedSprite.getPosition().x > 1 ){
                        movement.x -= contPulo * 4.0f;
                        background.move(2.f,0.0f);
                        ground.move( 1.f,0.f);
                    }else{
                        background.move(- 4.f,0.0f);
                        ground.move(- 2.f,0.f);
                    }
                }
                contPulo--;                
                contPulo2++;
            }else{
                contPulo++;
                pulando = false;
                descendo = true;
            }
        }else{
            if(descendo){
                if(tempoPulo <= sf::seconds(1)){
                    movement.y += contPulo * 7.0f;
                    if(andandoDir){
                        if(animatedSprite.getPosition().x < 400 ){
                            movement.x += contPulo2 * 4.0f;
                            background.move(- 2.f,0.0f);
                            ground.move(- 1.f,0.f);
                        }else{
                            background.move(- 4.f,0.0f);
                            ground.move(- 2.f,0.f);
                        }
                    }
                    if(andandoEsq){
                        if(animatedSprite.getPosition().x > 1 ){
                            movement.x -= contPulo2 * 4.0f;
                            background.move(+ 2.f,0.0f);
                            ground.move( 1.f,0.f);
                        }else{
                            background.move( 4.f,0.0f);
                            ground.move( 2.f,0.f);
                        }
                    }   
                    contPulo++;
                }else{
                    if(descendo == true)
                        andandoDir=false;
                    pulando = false;
                    descendo = false;
                    contPulo = 79;
                    contPulo2=0;
                }
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
        
        //teste para adicionar um disco na lista quando precionado a tecla de ataque
        if(inimigo.getAtacouDisco()){
            if(inimigo.getDirecao() == -1)
                discoInimigo.setReset(sf::Vector2f(inimigo.animatedSprite.getPosition().x , inimigo.animatedSprite.getPosition().y + 30),sf::Vector2f(- 1.0f,0.f),1);
            else
                discoInimigo.setReset(sf::Vector2f(inimigo.animatedSprite.getPosition().x + 85, inimigo.animatedSprite.getPosition().y + 30),sf::Vector2f(1.0f,0.f),1);
            inimigo.setDiscoJogado();
            discosInimigos.insere(discoInimigo,deuCerto);
        }
        if(adicionarUmDisco){
            discosHeroi.insere(disco,deuCerto);
            adicionarUmDisco=false;
        }
        //dependendo do tempo ele irá "sumir" com o disco
        if(tempoAtaque >= sf::seconds(0.25) ){
            atacando=false;
        }
        
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;
        //
        inimigo.animatedSprite.update(frameTime);
        animatedSprite.update(frameTime);
        App.clear();
        itens.remove(item1,deuCerto);
        itens.insere(item1,deuCerto);
        itens.remove(item,deuCerto);
        itens.insere(item,deuCerto);
        App.draw(background);
        App.draw(ground);
        App.draw(barraItens);
        App.draw(*itemSelecionado);
        for(i=0; i<5; i++)
            App.draw(caixaItem[i]);
        App.draw(item.getItem());
        App.draw(item1.getItem());
        App.draw(barraVida);
        
        quantDiscosHeroi = discosHeroi.getQuant();
        //animação do disco indo,  ponto + vetor * escalar
        for(i=0;i<quantDiscosHeroi;i++){
            discosHeroi.remove(disco,deuCerto);
            printf("%d",i);
            if(disco.getPosicao().x <= 1024.0f && disco.getPosicao().x > 0){
                App.draw(disco.getDisco());
                disco.mover();
                discosHeroi.insere(disco,deuCerto);
            }
        }
        quantDiscosHeroi = discosInimigos.getQuant();
        //animação do disco indo,  ponto + vetor * escalar
        for(i=0;i<quantDiscosHeroi;i++){
            discosInimigos.remove(discoInimigo,deuCerto);
            printf("%d",i);
            if(discoInimigo.getPosicao().x <= 1024.0f && discoInimigo.getPosicao().x > 0){
                App.draw(discoInimigo.getDisco());
                discoInimigo.mover();
                discosInimigos.insere(discoInimigo,deuCerto);
            }
        }
        App.draw(inimigo.procurarHeroi(animatedSprite,frameTime));
        App.draw(inimigo.animatedSprite);
        App.draw(animatedSprite);
        
        App.display();
	}
	//Never reaching this point normally, but just in case, exit the application
	return 0;
};
