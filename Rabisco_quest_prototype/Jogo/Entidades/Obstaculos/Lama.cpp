#include "Lama.h"

namespace Principal {
	Lama::Lama(float x, float y, float largura, float altura) {
		//id = Principal::ID_LAMA;
		corpo.setSize(sf::Vector2f(largura, altura));
		corpo.setPosition(x, y);
		corpo.setFillColor(sf::Color::Magenta);
	}
	Lama::~Lama() {}
	//diminuir a velocidade do jogador 
	void Lama::executar()
	{
		aplicarGravidade();
	}
	//deve ser implementado no gerenciador de colisões uma forma de detectar a colisão do jogador com a lama para que ocorra o efeito
	void Lama::obstacularizar(Jogador* p)
	{
		p->diminuirVelocidade();
	}
	void Lama::salvar() {
		// Implementação do método salvar
	}
}