#pragma once
#include "../Entidade.h"
#include "../Personagens/Jogador.h"

namespace Principal {
    class Obstaculo : public Entidade {
    protected:
        bool danoso;

    public:
        Obstaculo();
        virtual ~Obstaculo();
        void salvarDataBuffer();
        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void obstacularizar(Jogador* p) = 0;

    };
}