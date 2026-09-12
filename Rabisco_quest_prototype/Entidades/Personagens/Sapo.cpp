#include "Sapo.h"
#include <cmath>

namespace Principal {

    Sapo::Sapo(float x, float y, float largura, float altura)
        : raio(300.0f), temp_pulo(4 - nivel_maldade), velAtual(0.f)
    {
        corpo.setSize(sf::Vector2f(largura, altura));
        corpo.setFillColor(sf::Color::Yellow);
        corpo.setPosition(sf::Vector2f(x, y));
        vel = sf::Vector2f(2.0f * nivel_maldade, 0.f);
        tamanho = nivel_maldade;
        carregarTextura("Sprites/Sapo.png");
    }

    Sapo::~Sapo() {}

    void Sapo::executar()
    {
        mover();
        aplicarGravidade(); // cai como os outros personagens
    }

    void Sapo::mover()
    {
        if (alvo == nullptr) {
            velAtual *= 0.85f; // sem alvo: desacelera até parar
            corpo.move(velAtual, 0);
            return;
        }

        sf::Vector2f pos_alvo = alvo->getCorpo().getPosition();
        sf::Vector2f pos_inimigo = corpo.getPosition();

        if (fabs(pos_alvo.x - pos_inimigo.x) <= raio)
            perseguir(pos_alvo, pos_inimigo);
        else
            velAtual *= 0.85f; // fora do raio: desacelera gradualmente (inércia)

        corpo.move(velAtual, 0);
    }

    void Sapo::perseguir(sf::Vector2f pos_alvo, sf::Vector2f pos_inimigo)
    {
        // velocidade alvo: positiva se jogador à direita, negativa se à esquerda
        float velAlvo = (pos_alvo.x - pos_inimigo.x > 0) ? vel.x : -vel.x;

        // inércia: acelera gradualmente em direção à velocidade alvo
        // quanto menor a aceleracao (0.0 a 1.0), mais lenta a resposta
        float aceleracao = 0.12f;
        velAtual += (velAlvo - velAtual) * aceleracao;

        // pula periodicamente quando está no chão
        if (noChao && clockPulo.getElapsedTime().asSeconds() > temp_pulo) {
            velY = -10.f; // impulso de pulo
            noChao = false;
            clockPulo.restart();
        }
    }

    void Sapo::danificar(Jogador* p) { p->colidir(this); }
    void Sapo::salvar() {}
}
