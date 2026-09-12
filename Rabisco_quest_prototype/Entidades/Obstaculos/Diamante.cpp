#include "Diamante.h"

namespace Principal {
    Diamante::Diamante(float x, float y, float largura, float altura) {
        corpo.setSize(sf::Vector2f(largura, altura));
        corpo.setPosition(x, y);
        carregarTextura("Sprites/Diamante.png");
    }

    Diamante::~Diamante() {}

    void Diamante::executar() {}

    void Diamante::salvar() {}

    void Diamante::obstacularizar(Jogador* p) {
        p->setVenceu(true);
    }
}