/*
    JvAdventure: Trabalho 2
    Departamento de Computação
    UFSCar Universidade Federal de São Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        João Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523

    Controle de Versão: https://github.com/leonardo1101/JvTron
*/
#include <iostream>
#include "Tela.hpp"
#include <string.h>

#include <SFML/Graphics.hpp>

class Regras1 : public Tela{
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
	sf::RectangleShape *tecla; // vetor de teclas

	// métodos privados
	void desenha(sf::RenderWindow &) const;
public: // métodos públicos
	Regras1(float larg, float alt);
	~Regras1();
	void MovaParaEsquerda();
	void MovaParaDireita();
	int ItemApertado();
	virtual int Executar(sf::RenderWindow &App);
};

// Implementação dos métodos

// Construtor
// Inicializa e configura os atributos
Regras1::Regras1(float larg, float alt):  maxNumeroTeclas(4), maxNumeroBotoes(2){
	std::string textoBotao[maxNumeroBotoes] = { "Menu", "Seguinte"}; // textoBotao do botão
	std::string instrucoes[maxNumeroTeclas] = { // informacoes sobre as teclas
		"<", ">", "z", "x"
	};
	std::string descricao[maxNumeroTeclas-1] = { "Mover o personagem", "Utilizar item selecionado", "Pular" };
	numeroItem = 0;

	// alocação de posições
	descricaoTeclas = new sf::Text[maxNumeroTeclas-1]; // veteor para descricao das teclas
	tecla = new sf::RectangleShape[maxNumeroTeclas]; // vetor de teclas
	infos = new sf::Text[maxNumeroTeclas]; // vetor de informações
	botao = new sf::Text[maxNumeroBotoes]; // vetor de botoes

	// variaveis das medidas
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;

	if (!fonte.loadFromFile("Tr2n.ttf")){} // fonte das letras

	// inicializando titulo
	titulo.setCharacterSize(70);
	titulo.setString("REGRAS");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*2, centroy-altura*1/3 + titulo.getCharacterSize() - 150));
	titulo.setColor(sf::Color(0,255,255));

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
		descricaoTeclas[i].setPosition(sf::Vector2f(largura/(maxNumeroTeclas), (titulo.getCharacterSize() + 132.5) + i*altura/(maxNumeroTeclas+1)));
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

		switch(i){
			case 0:// <
			case 1:// >
				infos[i].setPosition(sf::Vector2f(100 + i*largura/(maxNumeroTeclas+10), (titulo.getCharacterSize() - 20) + altura/(maxNumeroTeclas+1)));
				tecla[i].setPosition(sf::Vector2f(90 + i*largura/(maxNumeroTeclas+10), (titulo.getCharacterSize() - 20) + altura/(maxNumeroTeclas+1)));
				break;
			case 2: // z
			case 3: // x
				infos[i].setPosition(sf::Vector2f(100 + largura/(maxNumeroTeclas+10), (titulo.getCharacterSize() - 20) + i*altura/(maxNumeroTeclas+1)));
				tecla[i].setPosition(sf::Vector2f(90 + largura/(maxNumeroTeclas+10), (titulo.getCharacterSize() - 20) + i*altura/(maxNumeroTeclas+1)));
				break;
		}
	}
}
// fim construtor

// Destrutor
// Deleta o vetor de teclas
Regras1::~Regras1(){ 
	delete infos;
	delete botao;
	delete tecla;
	delete descricaoTeclas;
};

// Executar
// Recebe por referência a janela da biblioteca gráfica
int Regras1::Executar(sf::RenderWindow &App){
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
								return 0;
								break;
							case 1: // proxima pagina
								return 3;
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
void Regras1::desenha(sf::RenderWindow & App) const{
	sf::RectangleShape linhas; // retângulo para linhas
	// configuração do retangulo
    linhas.setPosition(sf::Vector2f(50, 50));
    linhas.setFillColor(sf::Color(32,32,32));
    linhas.setOutlineThickness(1);
    linhas.setOutlineColor(sf::Color(0,255,255));
    linhas.setSize(sf::Vector2f(largura-100, altura -100));

    // desenha na janela
    App.clear(sf::Color(32,32,32));
	App.draw(linhas);
	App.draw(titulo);
	for(int i=0; i < maxNumeroBotoes; i++){
		App.draw(botao[i]);
	}
	for(int i = 0; i < maxNumeroTeclas; i++){
		App.draw(tecla[i]);
		App.draw(infos[i]);
	}
	for(int i=0; i < maxNumeroTeclas-1; i++){
		App.draw(descricaoTeclas[i]);
	}
};
// fim desenha

// MovaParaCima
// Move a seleção de botão para cima
void Regras1::MovaParaEsquerda(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setColor(sf::Color(255,255,255));
		numeroItem--;
		botao[numeroItem].setColor(sf::Color(0,255,255));
	}
};
// fim MovaParaCima

// MovaParaBaixo
// Move a seleção de botão para baixo
void Regras1::MovaParaDireita(){
	if(numeroItem + 1 < maxNumeroBotoes){
		botao[numeroItem].setColor(sf::Color(255,255,255));
		numeroItem++;
		botao[numeroItem].setColor(sf::Color(0,255,255));
	}
};
// fim MovaParaBaixo
int Regras1::ItemApertado(){ return numeroItem; };
