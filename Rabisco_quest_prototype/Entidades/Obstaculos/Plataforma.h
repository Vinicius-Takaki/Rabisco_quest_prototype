#pragma once
#include "Obstaculo.h"

namespace Principal {
    class Plataforma : public Obstaculo {
    private:
        void resolverColisao(Entidade* ent); // resolve colisão pelo lado de menor sobreposição

    public:
        Plataforma(float x, float y, float largura, float altura, sf::Color cor = sf::Color::Cyan);
        ~Plataforma();

        void executar();
        void obstacularizar(Jogador* p);
        void obstacularizar(Entidade* p);
        void salvar();
    };
}