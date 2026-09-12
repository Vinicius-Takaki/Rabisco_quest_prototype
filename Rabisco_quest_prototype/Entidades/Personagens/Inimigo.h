#pragma once
#include "Personagem.h"
#include "Jogador.h"

namespace Principal {
    class Inimigo : public Personagem
    {
    protected:
        int nivel_maldade;
        Jogador* alvo;
    public:
        Inimigo();
        virtual ~Inimigo();

        void salvarDataBuffer();
        virtual void executar() = 0;
        virtual void danificar(Jogador* p) = 0;
        virtual void salvar() = 0;
        void setAlvo(Jogador* jogador); // define quem perseguir
    };
}