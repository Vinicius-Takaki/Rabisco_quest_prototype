#pragma once
#include "Fase.h"
#include "../Entidades/Bloco/Sala.h"
#include "../Entidades/Personagens/Slime.h"
#include "../Entidades/Personagens/Rato.h"
#include "../Entidades/Obstaculos/Armadilha.h"
#include "../Listas/ListaEntidade.h"
#include "../Listas/Lista.h"

namespace Principal {
    class FaseSegunda : public Fase {
    private:
        const int maxSlime;
        const int maxArmadilha;

    protected:
        // Funcoes para criar entidades
        void criarSlimes();
        void criarArmadilhas(); // cria armadilhas
        void criarInimigos();
        void criarObstaculo();
		void criarDiamante(); // cria diamante no final da fase
        std::string getTexturaChao() const override { return "Sprites/Chao2.png"; }
    public:
        FaseSegunda();
        ~FaseSegunda();

        void incluirJogadores(Jogador* pJog1); // Inclui 1 ou 2 jogadores na fase. Nao deve ser chamada mais de uma vez !!!
        void inicializaFase(); // Chama todas as funcoes "criar"
        void executar(sf::RenderWindow* janela); // Executa a fase (movimento, colisoes e renderizacao)
        
    };

}


