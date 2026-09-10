#include "Entidade.h"

namespace Principal {
    Entidade::Entidade() : x(0.f), y(0.f), noChao(false), velY(0.f), vivo(true) {
        corpo.setPosition(x, y); // posiciona o corpo na origem ao criar
    }

    Entidade::~Entidade() {}

    // Desenha o corpo retangular na janela
    void Entidade::desenhar(sf::RenderWindow& window) {
        window.draw(corpo);
    }

    void Entidade::salvarDataBuffer() {}

    sf::RectangleShape& Entidade::getCorpo() { // Retorna o corpo para quem precisar acessar
        return corpo;
    }
    void Entidade::aplicarGravidade() {
        if (!noChao) {
            if (velY < 10.f) // VELOCIDADE TERMINAL, TALVEZ REMOVA !!!
                velY += 0.5f; // acelera para baixo enquanto estiver fora do chão
        }
        corpo.move(0.f, velY); // aplica a velocidade vertical no corpo
        noChao = false; // reseta noChao
    }

    sf::Vector2f Entidade::getPosicao() const {
        return corpo.getPosition(); // Retorna a posição atual do corpo na tela
    }
    void Entidade::setPosition(sf::Vector2f pos) {
        corpo.setPosition(pos);
        x = pos.x;
        y = pos.y;
    }

    void Entidade::pousar() {
        velY = 0.f;
        noChao = true;
    }
	void Entidade::setVivo(bool v) {
		vivo = v;
	}
	bool Entidade::getVivo() const {
		return vivo;
	}
    sf::Vector2f Entidade::getTam() const 
    { return corpo.getSize(); }
}