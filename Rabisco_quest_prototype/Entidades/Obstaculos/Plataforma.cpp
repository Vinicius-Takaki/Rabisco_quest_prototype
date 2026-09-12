#include "Plataforma.h"
#include <algorithm>
#include "Obstaculo.h"

namespace Principal {
    Plataforma::Plataforma(float x, float y, float largura, float altura, sf::Color cor) {
        corpo.setSize(sf::Vector2f(largura, altura));
        corpo.setPosition(x, y);
        corpo.setFillColor(cor);
    }
    Plataforma::~Plataforma() {}

    void Plataforma::executar() {
        // plataformas são estáticas — não sofrem gravidade
    }

    void Plataforma::resolverColisao(Entidade* ent) {
        sf::FloatRect rEnt = ent->getCorpo().getGlobalBounds();
        sf::FloatRect rObs = corpo.getGlobalBounds();

        float overlapCima = (rEnt.top + rEnt.height) - rObs.top;
        float overlapBaixo = (rObs.top + rObs.height) - rEnt.top;
        float overlapEsquerda = (rEnt.left + rEnt.width) - rObs.left;
        float overlapDireita = (rObs.left + rObs.width) - rEnt.left;

        float minOverlap = std::min({ overlapCima, overlapBaixo, overlapEsquerda, overlapDireita });

        if (minOverlap == overlapCima) {
            ent->setPosition(sf::Vector2f(rEnt.left, rObs.top - rEnt.height));
            ent->pousar();
        }
        else if (minOverlap == overlapBaixo) {
            ent->setPosition(sf::Vector2f(rEnt.left, rObs.top + rObs.height));
        }
        else if (minOverlap == overlapEsquerda) {
            ent->setPosition(sf::Vector2f(rObs.left - rEnt.width, rEnt.top));
        }
        else {
            ent->setPosition(sf::Vector2f(rObs.left + rObs.width, rEnt.top));
        }
    }

    void Plataforma::obstacularizar(Jogador* p) {
        resolverColisao(p);
    }

    void Plataforma::obstacularizar(Entidade* p) {
        resolverColisao(p);
    }

    void Plataforma::salvar() {}
}