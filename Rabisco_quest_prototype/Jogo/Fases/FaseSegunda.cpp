#include "FaseSegunda.h"
#include "../Entidades/Personagens/Pisadeira.h"
#include "../Entidades/Obstaculos/Armadilha.h"

namespace Principal {
    FaseSegunda::FaseSegunda() : maxPisadeira(3), maxArmadilha(5) {
        GC.setSala(&minhaSala);
    }

    FaseSegunda::~FaseSegunda() {}

    void FaseSegunda::criarPisadeiras() {
        int qtd = rand() % maxPisadeira + 1;
        float largura = 50.f;
        float altura = 50.f;
        for (int i = 0; i < qtd; i++) {
            float randX = (larguraFase / 2) + (rand() % (int)(larguraFase / 2 - 200)) + 100.f;
            float randY = alturaFase - 60.f;
            Pisadeira* chefao = new Pisadeira(randX, randY, largura, altura);
            chefao->setAlvo(pJ1);
            chefao->setGC(&GC);
            listaE.incluir(static_cast<Entidade*>(chefao), true);
            GC.incluirInimigo(chefao);
        }
    }

    void FaseSegunda::criarArmadilhas() {
        int qtd = rand() % (maxArmadilha + 1 - 3) + 3;
        float largura = 20.f;
        float altura = 20.f;

        for (int i = 0; i < qtd; i++) {
            float randX = (int)(rand() % (larguraFase - 150)) + 50.f;
            float randY = alturaFase - 60.f;

            Armadilha* arm = new Armadilha(randX, randY, largura, altura);
            listaE.incluir(static_cast<Entidade*>(arm), true);
            GC.incluirObstcaulo(arm);
        }
    }

    void FaseSegunda::criarInimigos() {
        criarAlmasPenadas(); // compartilhada — vem de Fase
        criarPisadeiras();   // exclusiva fase 2
    }

    void FaseSegunda::criarObstaculo() {
        criarPlataformas();  // compartilhada — vem de Fase
        criarArmadilhas();   // exclusiva fase 2
    }

    void FaseSegunda::incluirJogadores(Jogador* pJog1, Jogador* pJog2) {
        Fase::incluirJogadores(pJog1, pJog2);
        pJog1->setPosition(sf::Vector2f(50.f, alturaFase - 80.f));
        if (pJog2)
            pJog2->setPosition(sf::Vector2f(800.f, alturaFase - 80.f));
    }

    void FaseSegunda::inicializaFase() {
        criarObstaculo();
        criarInimigos();
    }

    void FaseSegunda::executar(sf::RenderWindow* janela) {
        minhaSala.desenhar(*janela);
        listaE.percorrer();

        // Remover entidades mortas notificando o Gerenciador de Colisao
        // antes de executar o próprio Gerenciador para evitar uso de
        // ponteiros já liberados (use-after-free).
        listaE.limparMortos(&GC);

        GC.executar();

        listaE.desenhaTodos(*janela);
        // chamada de limparMortos removida daqui para evitar dupla remoção
    }
}