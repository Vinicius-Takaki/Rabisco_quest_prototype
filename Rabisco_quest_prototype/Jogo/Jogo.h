#pragma once
#include "Entidades/Personagens/Jogador.h"
#include "Fases/FasePrimeira.h"
#include "Ente.h"
#include "Gerenciadores/GerenciadorGrafico.h"
#include "Fases/FaseSegunda.h"


namespace Principal {
    class Jogo {
    private:
        // Dimensões da janela
        const float alturaJanela = 700.f;
        const float larguraJanela = 900.f;
        float larguraFase = 3600.f;

        // Jogadores
        Jogador jogador1;
        Jogador jogador2;
        int faseAtual = 1;
        bool faseInicializada = false;

        GerenciadorGrafico* pGG;

        // Fases
        FasePrimeira fase1;
        FaseSegunda fase2;

        //menu

    public:
        Jogo();
        ~Jogo();

        void executar();
        void atualizarCamera();
    };
}


