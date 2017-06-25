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

#ifndef TELA_H
#define TELA_H

#include <SFML/Graphics.hpp>

class Tela{
public:
	virtual int Executar(sf::RenderWindow & app) = 0;
};

#endif