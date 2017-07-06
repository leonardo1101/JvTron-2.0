#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

class Som{
public:
    Som(){};
	void emiteSomDisco(sf::Music &somDisco, bool ok);
	void emiteSomBarra(sf::Music &somBarra, bool ok);
	void emiteSomGolpe(sf::Music &somGolpe, bool ok);
	void emiteSomPulo(sf::Music &somPulo, bool ok);
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
    music.play();
    ok = true;
};
