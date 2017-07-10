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
#include <SFML/Graphics.hpp>

// Estrutura da tela Perdeu
class Perdeu : public Tela{
private:
	// atributos privados
	const int maxNumeroItens; // número máximo de botões
	int numeroItem; // número do item pressionado
	float largura, altura, centrox, centroy; // medidas da tela
	sf::Font fonte;
	sf::Text titulo;
	sf::Color cor;
	sf::Text *botao; // vetor de botões

	void MovaParaCima();
	void MovaParaBaixo();
	void desenha(sf::RenderWindow &) const;
	int ItemApertado();
public:
	// métodos privados
	Perdeu(float larg, float alt);
	~Perdeu();
	virtual int Executar(sf::RenderWindow &App);
};

// Construtor
// Recebe como parâmetros as dimensões da janela e a cor do ganhador
// Inicializa e configura os atributos
Perdeu::Perdeu(float larg, float alt): maxNumeroItens(2){
	std::string texto[maxNumeroItens] = {"Jogar novamente", "Sair"}; // texto dos botões
	numeroItem = 0; // seleciona o primeiro item

	// configuração das medidas
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;
	cor = sf::Color(sf::Color(255,60,0));

	botao = new sf::Text[maxNumeroItens]; // alocação de botões

	if (!fonte.loadFromFile("Tr2n.ttf")){} // carregar fonte selecionada
	// inicializando titulo
	titulo.setCharacterSize(100);
	titulo.setString("Perdeu");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*1.95, centroy-altura*1/2 + titulo.getCharacterSize() - 10));
	titulo.setColor(cor);

	//inicializando botoes
	for(int i = 0; i < maxNumeroItens; i++){
		botao[i].setFont(fonte);
		botao[i].setCharacterSize(40);

		if(i == 0)
			botao[i].setColor(cor);
		else
			botao[i].setColor(sf::Color::White);

		botao[i].setString(texto[i]);
		botao[i].setPosition(sf::Vector2f(centrox - botao[i].getCharacterSize()*5, (altura-100)*5/6 + altura/(maxNumeroItens+1)/4*i-20));
	}
}
// fim Construtor

// Destrutor
// Deleta vetor de botões
Perdeu::~Perdeu(){ delete botao; }; // fim Destrutor

// Executar
// Recebe por referência a janela da biblioteca gráfica
int Perdeu::Executar(sf::RenderWindow &App){
	// declaracao de variaveis
	sf::Event Event; // eventos do jogo
	bool Executando = true;
	while (Executando){ // loop da tela
		// Verificação de eventos
		while (App.pollEvent(Event)){ // loop de eventos
			if (Event.type == sf::Event::Closed){ // se fechar a tela
				return (-1); // fim jogo
			}
			// ao pressionar botões
			if (Event.type == sf::Event::KeyPressed){
				switch (Event.key.code){
					// navegar pelas opções
					case sf::Keyboard::Up:
                        MovaParaCima();
                        break;
                    case sf::Keyboard::Down:
                        MovaParaBaixo();
                        break;
                    // pressionar opção
					case sf::Keyboard::Return:
						switch(ItemApertado()){
                            case 0:
                            	return (0); // jogar novamente
                                break;
                            case 1:
                            	App.close();
                                return (-1); // sair
                                break;
                        }
                        break;
				}
			}
		}// fim loop de eventos

		// desenhar coisas na tela
		App.clear();
		desenha(App);
        App.display();
	} // fim loop da tela

	// não há como chegar até aqui mas, se acontecer, termine o programa.
	return (-1);
}
// fim Executar

// Desenha
// Método que desenha na tela alguns atributos
void Perdeu::desenha(sf::RenderWindow & App) const{
	sf::RectangleShape linhas; // retângulo para linhas
	// configuração do retangulo
    linhas.setPosition(sf::Vector2f(50, 50));
    linhas.setFillColor(sf::Color(32,32,32));
    linhas.setOutlineThickness(1);
    linhas.setOutlineColor(cor);
    linhas.setSize(sf::Vector2f(largura-100, altura -100));

    sf::Image imagem;
    sf::Texture textura;
    sf::Sprite sprite;
    imagem.loadFromFile("perdeu.png");
    textura.loadFromImage(imagem);
    sprite.setTexture(textura);
    sprite.setScale(sf::Vector2f(5.0f,5.0f));
    sprite.setOrigin(imagem.getSize().x/2, imagem.getSize().y/2);
    sprite.setPosition(sf::Vector2f(centrox, centroy));

    // desenha na janela
    App.clear(sf::Color(32,32,32));
    App.draw(linhas);
	App.draw(titulo);
	App.draw(sprite);
	for(int i = 0; i < maxNumeroItens; i++){
		App.draw(botao[i]);
	}
};
// fim Desenha

// MovaParaCima
// Move a seleção de botão para cima
void Perdeu::MovaParaCima(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setColor(sf::Color::White);
		numeroItem--;
		botao[numeroItem].setColor(cor);
	}
};
// fim MovaParaCima

// MovaParaBaixo
// Move a seleção de botão para baixo
void Perdeu::MovaParaBaixo(){
	if(numeroItem + 1 < maxNumeroItens){
		botao[numeroItem].setColor(sf::Color::White);
		numeroItem++;
		botao[numeroItem].setColor(cor);
	}
};
// fim MovaParaBaixo

// ItemApertado
// Retorna o número do botão selecionado
int Perdeu::ItemApertado(){ return numeroItem; };
// fim ItemApertado
