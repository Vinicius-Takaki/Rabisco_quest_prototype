#pragma once
#include "../Listas/ListaEntidade.h"
#include "../Entidades/Personagens/Jogador.h"
#include "../Gerenciadores/GerenciadorColisao.h"
#include <string>

namespace Principal {
    class Fase {
    private:
        const int maxRatos;
        const int maxPlataformas;


    protected:
        ListaEntidades listaE;
        GerenciadorColisao GC;
        Jogador* pJ1;
        // Dimensões da fase
        const int alturaFase = 700;
        const int larguraFase = 3600;
        Sala minhaSala;
        const float zonaSegura = 700.f; // NOVO: distância inicial livre de inimigos/obstáculos perigosos

        void criarRatosPenados(); // Cria ratos aleatoriamente
        void criarPlataformas(); // Cria plataformas aleatoriamente
        void criarCenario(); // vide Fase.cpp

        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;
        virtual std::string getTexturaChao() const { return "Sprites/Chao1.png"; }

        void sementear(); // Aleatoriza a semente de rng
        void criarChao();

    public:
        Fase();
        virtual ~Fase();

        virtual void inicializaFase() = 0;
        void limpaFase(); // Limpa lista e desaloca entidades
        // salvaFase() carregaFase()

        virtual void incluirJogadores(Jogador* pJog1); // Inclui jogadores na lista. Nao deve ser chamado mais do que uma vez!!!

        virtual void executar(sf::RenderWindow* janela) = 0;
        // Desenha elementos da interface (vida, pontuação, etc.)
        void desenharVida(sf::RenderWindow* janela);
        void inicializarChao();

    };
}