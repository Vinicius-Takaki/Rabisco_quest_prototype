#include "Rato.h"
#include <cmath>

namespace Principal {

    Rato::Rato(float x, float y, float altura, float largura) : raio(200.0f), velAtual(0.f)
    {
        corpo.setSize(sf::Vector2f(altura, largura));
        corpo.setFillColor(sf::Color::Red);
        corpo.setPosition(sf::Vector2f(x, y));
        vel = sf::Vector2f(2.0f * nivel_maldade, 0.0f);
        carregarTextura("Sprites/Rato.png");
    }

    Rato::~Rato() {}

    void Rato::executar() { mover(); aplicarGravidade(); }

    void Rato::mover()
    {
        if (alvo != nullptr)
        {
            sf::Vector2f pos_alvo = alvo->getCorpo().getPosition();
            sf::Vector2f pos_inimigo = corpo.getPosition();

            // só persegue se o jogador estiver dentro do raio de detecção
            if (fabs(pos_alvo.x - pos_inimigo.x) <= raio &&
                fabs(pos_alvo.y - pos_inimigo.y) <= raio) //Referencia: https://www.youtube.com/watch?v=HXFTzs7jzJ8&list=PLR17O9xbTbIBBoL3lli44N8LdZVvg-_uZ&index=3
                perseguir(pos_alvo, pos_inimigo);
            else
                velAtual *= 0.85f; // fora do raio: desacelera gradualmente (inércia)
        }
        else
            velAtual *= 0.85f;

        corpo.move(velAtual, 0);
    }

    // Move horizontalmente na direção do jogador //Referencia: https://www.youtube.com/watch?v=HXFTzs7jzJ8&list=PLR17O9xbTbIBBoL3lli44N8LdZVvg-_uZ&index=3
    void Rato::perseguir(sf::Vector2f pos_alvo, sf::Vector2f pos_inimigo)
    {
        // velocidade alvo: positiva se jogador à direita, negativa se à esquerda
        float velAlvo = (pos_alvo.x - pos_inimigo.x > 0) ? vel.x : -vel.x;

        // inércia: velocidade atual se aproxima gradualmente da velocidade alvo
        // quanto menor a aceleracao (0.0 a 1.0), mais lenta a resposta
        float aceleracao = 0.15f;
        velAtual += (velAlvo - velAtual) * aceleracao;
    }

    void Rato::danificar(Jogador* p) { p->colidir(this); }
    void Rato::salvar() {}
}
