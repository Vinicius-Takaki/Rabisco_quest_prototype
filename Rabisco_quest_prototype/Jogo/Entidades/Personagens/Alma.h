#pragma once
#include "Inimigo.h"

namespace Principal {
    class Alma : public Inimigo
    {
    private:
        float raio;  // distância máxima para detectar e perseguir o jogador
        

    public:
        Alma(float x, float y, float largura, float altura);// construtor para criar inimigo em posição específica
        ~Alma();

        void executar();
        void danificar(Jogador* p);
        void salvar();
        void mover();

        void perseguir(sf::Vector2f pos_alvo, sf::Vector2f pos_inimigo); // move em direção ao jogador
    };
}

