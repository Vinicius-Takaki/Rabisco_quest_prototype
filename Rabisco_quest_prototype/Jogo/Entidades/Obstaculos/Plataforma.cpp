#include "Plataforma.h"

namespace Principal {
    Plataforma::Plataforma(float x, float y, float largura, float altura) {
        // construtor para criar plataforma em posição específica, com largura e altura definidas (altura valor a definir)
        //id = Principal::ID_ARMADILHA;
        corpo.setSize(sf::Vector2f(largura, altura));
        corpo.setPosition(x, y);
        corpo.setFillColor(sf::Color::Cyan);
    }
    Plataforma::~Plataforma() {}

    void Plataforma::executar() { aplicarGravidade(); }
    
    void Plataforma::obstacularizar(Jogador* p)
    {
        sf::FloatRect rJog = p->getCorpo().getGlobalBounds();
        sf::FloatRect rObs = corpo.getGlobalBounds();
        float penetracao = (rJog.top + rJog.height) - rObs.top;
        p->setPosition(sf::Vector2f(rJog.left, rJog.top - penetracao));
        p->pousar();
    }

    void Plataforma::obstacularizar(Entidade* p) {
        sf::FloatRect rEnt = p->getCorpo().getGlobalBounds();
        sf::FloatRect rObs = corpo.getGlobalBounds();
        float penetracao = (rEnt.top + rEnt.height) - rObs.top;
        p->setPosition(sf::Vector2f(rEnt.left, rEnt.top - penetracao));
        p->pousar();
    }


    void Plataforma::salvar() {}
}
