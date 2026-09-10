#include "Projetil.h"
#include "../Entidades/Personagens/Jogador.h" 

namespace Principal {

    Projetil::Projetil(float x, float y, sf::Vector2f v)
        : vel(v), ativo(true)
    {
        corpo.setSize(sf::Vector2f(10.f, 10.f));
        corpo.setFillColor(sf::Color::Yellow);
        corpo.setPosition(x, y);
    }

    Projetil::~Projetil() {}

    void Projetil::executar() {
        if (!ativo) return;
        corpo.move(vel.x, vel.y);

        sf::Vector2f pos = corpo.getPosition();
        if (pos.x < -20.f || pos.x > 3600 + 20.f || pos.y < -20.f || pos.y > 700 + 20.f) 
            ativo = false;
        aplicarGravidade();
    }

    void Projetil::salvar() {}

    void Projetil::colidir(Entidade* p) {
        if (!ativo) return;

        Jogador* jogador = dynamic_cast<Jogador*>(p);
        if (jogador && jogador->getVivo())
            jogador->colidir(nullptr); 

        ativo = false;
    }

    bool Projetil::getAtivo() const { return ativo; }
}
