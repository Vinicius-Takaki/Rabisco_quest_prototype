#pragma once
#include "Entidades/Personagens/Jogador.h"
#include "Fases/FasePrimeira.h"
#include "Ente.h"
#include "Gerenciadores/GerenciadorGrafico.h"
#include "Fases/FaseSegunda.h"
#include <SFML/Graphics.hpp>

namespace Principal {
    class Jogo {
    private:
        const float alturaJanela = 700.f;
        const float larguraJanela = 900.f;
        float larguraFase = 3600.f;

        Jogador jogador1;
        int faseAtual = 1;
        bool faseInicializada = false;
        bool jogoPerdido = false;
        bool jogoGanho = false;

        sf::Texture texturaDerrota;
        sf::Texture texturaVitoria;
        sf::Sprite spriteDerrota;
        sf::Sprite spriteVitoria;
        sf::Clock clockReiniciar;

        GerenciadorGrafico* pGG;

        FasePrimeira fase1;
        FaseSegunda fase2;

    public:
        Jogo();
        ~Jogo();

        void executar();
        void atualizarCamera();
    };
}