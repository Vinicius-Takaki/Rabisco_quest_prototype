#include "FasePrimeira.h"
#include "../Entidades/Personagens/Sapo.h"
#include "../Entidades/Personagens/Rato.h"
//#include "../Entidades/" // LAMA

namespace Principal {
    FasePrimeira::FasePrimeira() : maxSapo(5), maxObstaculoLama(5) {
        GC.setSala(&minhaSala);

        minhaSala.setTexturaFundo("Sprites/Cenario1.png");

    }

    FasePrimeira::~FasePrimeira() {
        
    }

    // Cria inimigos médios
    // VIDE criarAlmas() DA CLASSE FASE PARA PEGAR INSPIRAÇÕES !!!
    void FasePrimeira::criarSapos() {
        int qtd = rand() % (maxSapo + 1 - 3) + 3;
        float altura = 40.f;
        float largura = 40.f;

        for (int i = 0; i < qtd; i++) {
            float randX = zonaSegura + (rand() % (int)(larguraFase - zonaSegura - 200.f)); // MODIFICADO
            float randY = alturaFase / 2.f;

            float enemyX = 50.f + randX;

            Sapo* inimigo = new Sapo(enemyX, randY, largura, altura);
            inimigo->setAlvo(pJ1);
            listaE.incluir(static_cast<Entidade*>(inimigo), true);
            GC.incluirInimigo(inimigo);
        }
    }

    void FasePrimeira::criarLamas() {
        int qtd = rand() % (maxObstaculoLama + 1 - 3) + 3;
        float altura = 6.f;
        float largura = 80.f;

        for (int i = 0; i < qtd; i++) {
            float randX = zonaSegura + (float)(rand() % (int)(larguraFase - zonaSegura - 150.f)); // MODIFICADO
            float randY =90.f;

            Lama* lama = new Lama(randX, randY, largura, altura);
            listaE.incluir(static_cast<Entidade*>(lama), true);
            GC.incluirObstcaulo(lama);
        }
    }

    void FasePrimeira::criarInimigos() {
        criarRatosPenados();
        criarSapos();
    }

    void FasePrimeira::criarObstaculo() {
        criarPlataformas();
        criarLamas();
    }


    void FasePrimeira::incluirJogadores(Jogador* pJog1) {
        Fase::incluirJogadores(pJog1);
        pJog1->setPosition(sf::Vector2f(50.f, alturaFase - 80.f));
    }

    void FasePrimeira::inicializaFase() {
        criarObstaculo();
        criarInimigos();
        inicializarChao();
    }

    void FasePrimeira::executar(sf::RenderWindow* janela) {
        minhaSala.desenhar(*janela);
        listaE.percorrer();

        listaE.limparMortos(&GC);  

        GC.executar();

        listaE.desenhaTodos(*janela);
        desenharVida(janela);
    }

}