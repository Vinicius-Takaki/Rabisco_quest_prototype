#pragma once
#include "Obstaculo.h"

namespace Principal {
    class Diamante : public Obstaculo {
    public:
        Diamante(float x, float y, float largura, float altura);
        ~Diamante();

        void executar() override;
        void salvar() override;
        void obstacularizar(Jogador* p);
    };
}