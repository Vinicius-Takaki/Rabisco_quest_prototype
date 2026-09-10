// Projetil.h
#pragma once
#include "Entidade.h"

namespace Principal {
    class Jogador; // CORRIGIDO: forward declaration

    class Projetil : public Entidade {
    private:
        sf::Vector2f vel;
        bool ativo;

    public:
        Projetil(float x, float y, sf::Vector2f vel);
        ~Projetil();
        void executar();
        void salvar();
        void colidir(Entidade* alvo);
        bool getAtivo() const;
        void setAtivo(bool a) { ativo = a; }
    };
}