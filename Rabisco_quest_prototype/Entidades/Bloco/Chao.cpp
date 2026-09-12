#include "Chao.h"

// ============================= //
// ===== CLASSE DESCARTADA ===== //
// ============================= //


namespace Principal {
    Chao::Chao(float x, float y, float largura)
    {
        corpo.setSize(sf::Vector2f(largura, 32.f));
        corpo.setPosition(x, y);
        corpo.setFillColor(sf::Color::Blue);
    }

    Chao::~Chao() {}

    void Chao::executar() {}
    void Chao::salvar() {}
    void Chao::obstaculizar(Jogador* p) {}
}
