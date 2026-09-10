#pragma once
#include "../Listas/ListaEntidade.h"
#include "../Entidades/Personagens/Jogador.h"
#include "../Gerenciadores/GerenciadorColisao.h"

namespace Principal {
    class Fase {
    private:
        const int maxAlmas;
        const int maxPlataformas;


    protected:
        ListaEntidades listaE;
        GerenciadorColisao GC;
        Jogador* pJ1;
        Jogador* pJ2;
        // Dimensões da fase
        const int alturaFase = 700;
        const int larguraFase = 3600;
        Sala minhaSala;

        void criarAlmasPenadas(); // Cria almas aleatoriamente
        void criarPlataformas(); // Cria plataformas aleatoriamente
        void criarCenario(); // vide Fase.cpp

        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;

        void sementear(); // Aleatoriza a semente de rng

    public:
        Fase();
        virtual ~Fase();

        virtual void inicializaFase() = 0;
        void limpaFase(); // Limpa lista e desaloca entidades
        // salvaFase() carregaFase()

        virtual void incluirJogadores(Jogador* pJog1, Jogador* pJog2 = NULL); // Inclui jogadores na lista. Nao deve ser chamado mais do que uma vez!!!

        virtual void executar(sf::RenderWindow* janela) = 0;
    };
}