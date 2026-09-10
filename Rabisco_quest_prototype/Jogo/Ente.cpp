#include "Ente.h"
#include "Gerenciadores/GerenciadorGrafico.h"

namespace Principal {
	// Inicializa os ponteiros estáticos como nulos
	int Ente::contador_id = 0;

	GerenciadorGrafico* Ente::pGG = nullptr;
	sf::RenderWindow* Ente::pJanela = nullptr;

	Ente::Ente() : id(0) {}
	Ente::~Ente() {}

	// Guarda o ponteiro do gerenciador gráfico 
	void Ente::setGG(GerenciadorGrafico* pG) {
		pGG = pG;
	}

	// Guarda o ponteiro da janela 
	void Ente::setJanela(sf::RenderWindow* j) {
		pJanela = j;
	}

	// Retorna gerenciador (talvez seja bom deixar const essas e mais outras funções get)
	GerenciadorGrafico* Ente::getGG() {
		return pGG;
	}
}