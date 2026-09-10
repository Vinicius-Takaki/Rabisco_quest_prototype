#include "Banshee.h"
#include <cmath>

namespace Principal {

	Banshee::Banshee(float x, float y, float largura, float altura) : raio(300.0f), temp_pulo(3 - nivel_maldade)
    {
        corpo.setSize(sf::Vector2f(largura, altura));
        corpo.setFillColor(sf::Color::Yellow);
        corpo.setPosition(sf::Vector2f(x, y));
        vel = sf::Vector2f(2.0f * nivel_maldade, 0.f);
        tamanho = nivel_maldade;
    }

    Banshee::~Banshee() {}

    void Banshee::executar()
    {
        mover();
        aplicarGravidade(); // cai como os outros personagens
    }

    void Banshee::mover()
    {
        if (alvo == nullptr) return;

        sf::Vector2f pos_alvo = alvo->getCorpo().getPosition();
        sf::Vector2f pos_inimigo = corpo.getPosition();

        if (fabs(pos_alvo.x - pos_inimigo.x) <= raio)
        {
            perseguir(pos_alvo, pos_inimigo);
        }
    }

    void Banshee::perseguir(sf::Vector2f pos_alvo, sf::Vector2f pos_inimigo)
    {
        // move horizontalmente em direcao ao jogador
        if (pos_alvo.x - pos_inimigo.x > 0)
            corpo.move(vel.x, 0);
        else
            corpo.move(-vel.x, 0);

        // pula periodicamente quando esta no chao
        if (noChao && clockPulo.getElapsedTime().asSeconds() > temp_pulo) {
            velY = -10.f; // impulso de pulo
            noChao = false;
            clockPulo.restart();
        }
    }

    void Banshee::danificar(Jogador* p)
    {
        p->colidir(this);
    }

    void Banshee::salvar() {}
}