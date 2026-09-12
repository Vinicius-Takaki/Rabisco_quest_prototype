#include "Lama.h"

namespace Principal {
	Lama::Lama(float x, float y, float largura, float altura) : largura(largura) { // CORRIGIDO: inicializa o atributo largura
		//id = Principal::ID_LAMA;
		corpo.setSize(sf::Vector2f(largura, altura));
		corpo.setPosition(x, y);
		corpo.setFillColor(sf::Color::Magenta);
		carregarTextura("Sprites/Lama.png");
	}
	Lama::~Lama() {}
	void Lama::executar()
	{
		aplicarGravidade();
	}
	void Lama::obstacularizar(Jogador* p)
	{
		p->diminuirVelocidade();
	}
	void Lama::salvar() {
		// Implementação do método salvar
	}
}