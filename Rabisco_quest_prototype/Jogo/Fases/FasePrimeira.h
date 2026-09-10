#pragma once
#include "Fase.h"
#include "../Entidades/Bloco/Sala.h"
#include "../Entidades/Personagens/Banshee.h"
#include "../Entidades/Personagens/Alma.h"
#include "../Entidades/Obstaculos/Lama.h"
#include "../Listas/ListaEntidade.h"
#include "../Listas/Lista.h"


namespace Principal {
    class FasePrimeira : public Fase {
    private:
        const int maxBanshee;
        const int maxObstaculoLama;
        

    protected:
        // Funções para criar entidades
        void criarBanshees();
        void criarLamas();
        void criarInimigos();
        void criarObstaculo();

    public:
        FasePrimeira();
        ~FasePrimeira();

        void incluirJogadores(Jogador* pJog1, Jogador* pJog2 = NULL); // Inclui 1 ou 2 jogadores na fase. Não deve ser chamada mais de uma vez !!!
        void inicializaFase(); // Chama todas as funções "criar"
        //void limpaFase() // não lembro o que era para ser isso

        // Executa a fase (movimento, colisoes e renderização)
        void executar(sf::RenderWindow* janela);

    };
}