/*
    JvTron: Trabalho 2
    Departamento de Computação
    UFSCar Universidade Federal de São Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        João Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523

    Controle de Versão: https://github.com/leonardo1101/JvTron-2.0
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "TodasTelas.hpp"

/* isso é o comando no terminal linux pra compilar o programa
    g++ -c main.cpp && g++ main.o TodasTelas.hpp Item.hpp Lista.hpp player.hpp AnimatedSprite.hpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app
*/

// main()
// Função principal e gerenciadora de telas.
int main (){
    std::vector<Tela*> telas; // vetor que conterá as telas
    int numeroTela = 0; // tela de inicio da aplicacao (0) é o menu

    // Janela do aplicativo creation
    sf::RenderWindow App(sf::VideoMode(1024, 768), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    App.setFramerateLimit(150);
    // Esconder seta do mouse
    //App.setMouseCursorVisible(false);

    // Preparacao das tela
    Menu * s0 = new Menu(App.getSize().x, App.getSize().y); // TELA 0: menu do jogo
    telas.push_back(s0);
    Jogo * s1 = new Jogo(App.getSize().x, App.getSize().y);
    telas.push_back(s1);
    Regras1 * s2 = new Regras1(App.getSize().x, App.getSize().y);
    telas.push_back(s2);

    // loop principal
    while (numeroTela >= 0){
        if( (numeroTela = telas[numeroTela]->Executar(App)) == 1 );// chamada do metodo que faz funcionar a tela atual
            telas[1] = new Jogo(App.getSize().x, App.getSize().y);
    } // fim loop principal

    return EXIT_SUCCESS; // fim do programa
}
// fim main
