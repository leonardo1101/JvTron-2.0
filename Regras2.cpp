/*
	JvTron: Trabalho 1
	Departamento de Computação
	UFSCar Universidade Federal de São Carlos
	Disciplina: Estrutura de Dados
	Professor: Roberto Ferrari
	Aluno(a):								RA:
		João Gabriel Melo Barbirato			726546
		Leonardo de Oliveira Peralta		726556
		Gabrieli Santos						726523

	Controle de Versão: https://github.com/leonardo1101/JvTron
*/

#include <iostream>
#include "Tela.hpp"
#include <string.h>

#include <SFML/Graphics.hpp>

class Regras2 : public Tela{
private: 
	// atributos privados
	const int maxNumeroTeclas; // numero de teclas
	const int maxNumeroBotoes;
	float largura, altura, centrox, centroy; // variáveis pra guardar medidas da tela utilizada
	int numeroItem;
	sf::Text titulo;
	sf::Font fonte;
	sf::Text *botao;
	sf::Text *infos; // vetor de textoBotao para teclas
	sf::Text *descricaoTeclas; // descricao das teclas
	sf::RectangleShape *tecla, *quadradoPraItens; // vetor de teclas
	sf::Image *imagens;
	sf::Texture *texturas;
	sf::Sprite * spriteImagens;

	// métodos privados
	void desenha(sf::RenderWindow &) const;
public: // métodos públicos
	Regras2(float larg, float alt);
	~Regras2();
	void MovaParaEsquerda();
	void MovaParaDireita();
	int ItemApertado();
	virtual int Executar(sf::RenderWindow &App);
};

// Implementação dos métodos

// Construtor
// Inicializa e configura os atributos
Regras2::Regras2(float larg, float alt):  maxNumeroTeclas(4), maxNumeroBotoes(2){
	std::string textoBotao[maxNumeroBotoes] = { "Anterior", "Menu"}; // textoBotao do botão
	std::string instrucoes[maxNumeroTeclas] = { // informacoes sobre as teclas
		"1", "2", "3", "4"
	};
	std::string descricao[maxNumeroTeclas-1] = { "6 pontos de vida", "5 minutos", "drop de itens" };
	numeroItem = 0;
	std::string caminhoImagem[maxNumeroTeclas+1] = { "Itens/disco.png", "Itens/lanca.png", "Itens/pocao.png", "Itens/disco.png", "Itens/6vida.png" };

	// alocação de posições
	descricaoTeclas = new sf::Text[maxNumeroTeclas-1]; // vetor de descriões das teclas
	tecla = new sf::RectangleShape[maxNumeroTeclas]; // vetor de teclas
	infos = new sf::Text[maxNumeroTeclas]; // vetor de informações
	botao = new sf::Text[maxNumeroBotoes]; // vetor de botoes

	spriteImagens = new sf::Sprite[maxNumeroTeclas+1]; // vetor para as spriteImagens
	quadradoPraItens = new sf::RectangleShape[maxNumeroTeclas];
	imagens = new sf::Image[maxNumeroTeclas+1];
	texturas = new sf::Texture[maxNumeroTeclas+1];

	// variaveis das medidas
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;

	if (!fonte.loadFromFile("Tr2n.ttf")){} // fonte das letras

	// inicializando titulo
	titulo.setCharacterSize(70);
	titulo.setString("PARA TODOS OS LADOS");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*6.34, centroy-altura*1/3 + titulo.getCharacterSize() - 150));
	titulo.setColor(sf::Color(0,255,255));

	// inicializando imagens
	for(int i=0; i < maxNumeroTeclas + 1; i++){
		imagens[i].loadFromFile(caminhoImagem[i]);
		texturas[i].loadFromImage(imagens[i]);
		spriteImagens[i].setTexture(texturas[i]);
		if(i < maxNumeroTeclas){
			spriteImagens[i].setScale(sf::Vector2f(.15f,.15f));
			spriteImagens[i].setPosition(sf::Vector2f(100 + i*largura/(maxNumeroTeclas), (titulo.getCharacterSize()+60) + altura/(maxNumeroTeclas+1)));
			quadradoPraItens[i].setSize(sf::Vector2f(50,50));
			quadradoPraItens[i].setFillColor(sf::Color(32,32,32));
			quadradoPraItens[i].setOutlineThickness(1);
			quadradoPraItens[i].setOutlineColor(sf::Color(255,60,0));
			quadradoPraItens[i].setPosition(sf::Vector2f(90 + i*largura/(maxNumeroTeclas), (titulo.getCharacterSize()+50) + altura/(maxNumeroTeclas+1)));
		}else{
			spriteImagens[i].setScale(sf::Vector2f(.35f,.35f));
			spriteImagens[i].setPosition(sf::Vector2f(-180 + largura/(maxNumeroTeclas), (titulo.getCharacterSize()+150) + altura/(maxNumeroTeclas+1)));
		}
	}

	// inicializando botoes
	for(int i=0; i < maxNumeroBotoes; i++){
		botao[i].setFont(fonte);
		botao[i].setCharacterSize(40);
		if(i == 0)
			botao[i].setColor(sf::Color(0,255,255));
		else
			botao[i].setColor(sf::Color::White);
		botao[i].setString(textoBotao[i]);
		botao[i].setPosition(sf::Vector2f(centrox + ((i-1)*largura/(maxNumeroBotoes+1) + botao[i].getCharacterSize()*1.95), altura-100));
	}

	// inicializando descricoes dos botoes
	for(int i=0; i < maxNumeroTeclas - 1; i++){
		descricaoTeclas[i].setString(descricao[i]);
		descricaoTeclas[i].setFont(fonte);
		descricaoTeclas[i].setCharacterSize(40);
		descricaoTeclas[i].setColor(sf::Color::White);
		descricaoTeclas[i].setPosition(sf::Vector2f(50+largura/(maxNumeroTeclas), (titulo.getCharacterSize() + 290) + i*altura/(maxNumeroTeclas+8)));
	}

	// inicializando as infos
	for(int i=0; i < maxNumeroTeclas; i++){
		infos[i].setString(instrucoes[i]);
		infos[i].setFont(fonte);
		infos[i].setCharacterSize(35);
		infos[i].setColor(sf::Color(0,255,255));

		tecla[i].setSize(sf::Vector2f(50,50));
		tecla[i].setFillColor(sf::Color(32,32,32));
		tecla[i].setOutlineThickness(1);
		tecla[i].setOutlineColor(sf::Color(0,255,255));

		infos[i].setPosition(sf::Vector2f(100 + i*largura/(maxNumeroTeclas), (titulo.getCharacterSize() - 20) + altura/(maxNumeroTeclas+1)));
		tecla[i].setPosition(sf::Vector2f(90 + i*largura/(maxNumeroTeclas), (titulo.getCharacterSize() - 20) + altura/(maxNumeroTeclas+1)));
	}
}
// fim construtor

// Destrutor
// Deleta o vetor de teclas
Regras2::~Regras2(){ 
	delete infos;
	delete botao;
	delete tecla;
	delete descricaoTeclas;
};

// Executar
// Recebe por referência a janela da biblioteca gráfica
int Regras2::Executar(sf::RenderWindow &App){
	// declaracao de variaveis
	sf::Event Event; // eventos de jogo
	bool executando = true;
	while (executando){ // loop da tela
		// Verificação de eventos
		while (App.pollEvent(Event)){ // loop de eventos
			if (Event.type == sf::Event::Closed){ // se fechar a tela
				return (-1); // fim jogo
			}
			// ao pressionar botões
			if (Event.type == sf::Event::KeyPressed){
				switch (Event.key.code){
					case sf::Keyboard::Right:
						MovaParaDireita();
						break;
					case sf::Keyboard::Left:
						MovaParaEsquerda();
						break;
					case sf::Keyboard::Return:
						switch(ItemApertado()){
							case 0: // menu
								return 2;
								break;
							case 1: // proxima pagina
								return 0;
								break;
						}
					default:
						break;
				}
			}
		}// fim loop de eventos

		// desenhar coisas na tela
		App.clear();
		desenha(App); // chamada de método desenha
        App.display();
	} // fim loop da tela

	// não há como chegar até aqui mas, se acontecer, termine o programa.
	return (-1);
}
// fim Executar

// Desenha
// Método que desenha na tela alguns atributos
void Regras2::desenha(sf::RenderWindow & App) const{
	sf::RectangleShape linhas; // retângulo para linhas
    sf::Text horas;
    sf::Sprite itensGeneralizados(spriteImagens[2]);
	// configuração do retangulo
    linhas.setPosition(sf::Vector2f(50, 50));
    linhas.setFillColor(sf::Color(32,32,32));
    linhas.setOutlineThickness(1);
    linhas.setOutlineColor(sf::Color(0,255,255));
    linhas.setSize(sf::Vector2f(largura-100, altura -100));

    horas.setString("5:00");
	horas.setFont(fonte);
	horas.setCharacterSize(40);
	horas.setColor(sf::Color::Cyan);
	horas.setPosition(sf::Vector2f(-150 + largura/(maxNumeroTeclas), (titulo.getCharacterSize()+50) + 2*altura/(maxNumeroTeclas+1)));

	itensGeneralizados.setScale(.25f,.25f);
	itensGeneralizados.setPosition(sf::Vector2f(-100 + largura/(maxNumeroTeclas), (titulo.getCharacterSize()+120) + 2*altura/(maxNumeroTeclas+1)));
    // desenha na janela
    App.clear(sf::Color(32,32,32));
	App.draw(linhas);
    App.draw(horas);
    App.draw(itensGeneralizados);
	App.draw(titulo);
	for(int i=0; i < maxNumeroBotoes; i++){
		App.draw(botao[i]);
	}
	for(int i = 0; i < maxNumeroTeclas; i++){
		App.draw(quadradoPraItens[i]);
		App.draw(tecla[i]);
		App.draw(infos[i]);
	}
	for(int i=0; i < maxNumeroTeclas+1; i++){
		App.draw(spriteImagens[i]);
	}
	for(int i=0; i < maxNumeroTeclas-1; i++){
		App.draw(descricaoTeclas[i]);
	}
};
// fim desenha

// MovaParaCima
// Move a seleção de botão para cima
void Regras2::MovaParaEsquerda(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setColor(sf::Color(255,255,255));
		numeroItem--;
		botao[numeroItem].setColor(sf::Color(0,255,255));
	}
};
// fim MovaParaCima

// MovaParaBaixo
// Move a seleção de botão para baixo
void Regras2::MovaParaDireita(){
	if(numeroItem + 1 < maxNumeroBotoes){
		botao[numeroItem].setColor(sf::Color(255,255,255));
		numeroItem++;
		botao[numeroItem].setColor(sf::Color(0,255,255));
	}
};
// fim MovaParaBaixo
int Regras2::ItemApertado(){ return numeroItem; };