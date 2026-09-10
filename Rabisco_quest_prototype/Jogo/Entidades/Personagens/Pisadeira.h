#pragma once
#include "Inimigo.h"
#include "../Projetil.h"
#include <cmath>

namespace Principal {
    class GerenciadorColisao;

    class Pisadeira : public Inimigo {
    private:
        float raio;       
        float raioTiro;    
        float tamanho;
        short int forca;
        sf::Clock clock_Tiro;
        float temp_Tiro;
        Projetil* tiro;
        GerenciadorColisao* pGC;

    public:
        Pisadeira(float x, float y, float largura, float altura);
        ~Pisadeira();
        void executar();
        void mover();
        void perseguir(sf::Vector2f pos_alvo);
        void fazerProjetil();
        void atualizarProjetil();
        void danificar(Jogador* p);
        void salvar();
        void setGC(GerenciadorColisao* pG) { pGC = pG; }
    };
}