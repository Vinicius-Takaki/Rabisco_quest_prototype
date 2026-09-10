#pragma once
#include "Fase.h"
#include "../Entidades/Bloco/Sala.h"
#include "../Entidades/Personagens/Pisadeira.h"
#include "../Entidades/Personagens/Alma.h"
#include "../Entidades/Obstaculos/Armadilha.h"
#include "../Listas/ListaEntidade.h"
#include "../Listas/Lista.h"

namespace Principal {
    class FaseSegunda : public Fase {
    private:
        const int maxPisadeira;
        const int maxArmadilha;

    protected:
        // Funcoes para criar entidades
        void criarPisadeiras();
        void criarArmadilhas(); // cria armadilhas
        void criarInimigos();
        void criarObstaculo();
        void criarProjeteis(); // adiciona na lista os projeteis disparados pelas pisadeiras

    public:
        FaseSegunda();
        ~FaseSegunda();

        void incluirJogadores(Jogador* pJog1, Jogador* pJog2 = NULL); // Inclui 1 ou 2 jogadores na fase. Nao deve ser chamada mais de uma vez !!!
        void inicializaFase(); // Chama todas as funcoes "criar"

        // Executa a fase (movimento, colisoes e renderizacao)
        void executar(sf::RenderWindow* janela);
    };

}


