#pragma once
#include "Fase.h"
#include "../Entidades/Bloco/Sala.h"
#include "../Entidades/Personagens/Sapo.h"
#include "../Entidades/Personagens/Rato.h"
#include "../Entidades/Obstaculos/Lama.h"
#include "../Entidades/Obstaculos/Diamante.h"
#include "../Listas/ListaEntidade.h"
#include "../Listas/Lista.h"


namespace Principal {
    class FasePrimeira : public Fase {
    private:
        const int maxSapo;
        const int maxObstaculoLama;
        

    protected:
        // Funções para criar entidades
        void criarSapos();
        void criarLamas();
        void criarInimigos();
        void criarObstaculo();

    public:
        FasePrimeira();
        ~FasePrimeira();

        void incluirJogadores(Jogador* pJog1); // Inclui 1 ou 2 jogadores na fase. Não deve ser chamada mais de uma vez !!!
        void inicializaFase(); // Chama todas as funções "criar"
        //void limpaFase() // não lembro o que era para ser isso

        // Executa a fase (movimento, colisoes e renderização)
        void executar(sf::RenderWindow* janela);

    };
}