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
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

class Som{
public:
    Som(){};
    //mite o som do disco sendo jogado
	void emiteSomDisco(sf::Music &somDisco, bool ok);
    //emite o som da barra
	void emiteSomBarra(sf::Music &somBarra, bool ok);
	void emiteSomGolpe(sf::Music &somGolpe, bool ok);
    //emite o som do pulo
	void emiteSomPulo(sf::Music &somPulo, bool ok);
    //emite o som da musica
	void musica(sf::Music &music, bool ok); //musica de fundo
};

void Som::emiteSomDisco(sf::Music &somDisco, bool ok){
    if(!somDisco.openFromFile("sons/som-disco.ogg")){
        std::cout << "ERROR 1" << std::endl;
        ok = false;
    }
    somDisco.play();
    ok = true;
};

void Som::emiteSomBarra(sf::Music &somBarra, bool ok){
    if(!somBarra.openFromFile("sons/lanca.ogg")){
        std::cout << "ERROR 1" << std::endl;
        ok = false;
    }
    
    somBarra.setVolume(40);
    somBarra.play();
    ok = true;
};

void Som::emiteSomGolpe(sf::Music &somGolpe, bool ok){
    if(!somGolpe.openFromFile("2.ogg")){
        std::cout << "ERROR 1" << std::endl;
        ok = false;
    }
    somGolpe.play();
    ok = true;
};

void Som::emiteSomPulo(sf::Music &somPulo, bool ok){
    if(!somPulo.openFromFile("sons/jump.ogg")){
        std::cout << "ERROR 1" << std::endl;
        ok = false;
    }
    somPulo.play();
    ok = true;
};

void Som::musica(sf::Music &music, bool ok){
    if(!music.openFromFile("sons/Derezzed.ogg")){
        std::cout << "ERROR 1" << std::endl;
        ok = false;
    }
    music.setVolume(75);
    music.setLoop(true);
    music.play();
    ok = true;
};
