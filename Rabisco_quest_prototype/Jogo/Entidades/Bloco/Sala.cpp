#include "Sala.h"
#include <algorithm>
using namespace std;

namespace Principal {
    // Construtora com parâmetro
    Sala::Sala(int alturaFornecida, int larguraFornecida)
     : altura(alturaFornecida), largura(larguraFornecida) {
        area.setPosition(sf::Vector2f(0.f, 0.f));
        area.setSize(sf::Vector2f(largura, altura));
        area.setFillColor(sf::Color(100, 100, 100));
    }

    // Construtora sem parâmetro
    Sala::Sala() : altura(100), largura(100) {
        area.setPosition(sf::Vector2f(0.f, 0.f));
        area.setSize(sf::Vector2f(largura, altura));
        area.setFillColor(sf::Color(100, 100, 100));
    }

    Sala::~Sala() {
    }

    // Empurra entidade para dentro da sala
    void Sala::limitar(Entidade* ent) { 
        sf::FloatRect areaEnt = ent->getCorpo().getGlobalBounds();
        sf::FloatRect areaSala = area.getGlobalBounds();

        // Confere a margem de não-colisão e anula negativos
        float erroEsquerda = max(0.f, areaSala.left - areaEnt.left);
        float erroCima = max(0.f, areaSala.top - areaEnt.top);
        float erroDireita = max(0.f,(areaEnt.left + areaEnt.width) - (areaSala.left + areaSala.width));
        float erroBaixo = max(0.f,(areaEnt.top + areaEnt.height) - (areaSala.top + areaSala.height));
        
        // Determina se a entidade está fora da sala
        bool erro = (erroBaixo || erroCima || erroDireita || erroEsquerda);

        // Corrige a posição da entidade e aterrissa ela caso esteja no chao
        if (erro) {
            ent->setPosition(sf::Vector2f(areaEnt.left + (erroEsquerda - erroDireita),
                                          areaEnt.top + (erroCima - erroBaixo)));

            if (erroBaixo)
                ent->pousar();
                
        }
    }

    void Sala::desenhar(sf::RenderWindow& window) {
        window.draw(area);
    }
}