#include "FaseSegunda.h"
#include "../Entidades/Personagens/Slime.h"
#include "../Entidades/Obstaculos/Armadilha.h"
#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Entidades/Obstaculos/Diamante.h"
#include <algorithm>

namespace Principal {
    FaseSegunda::FaseSegunda() : maxSlime(3), maxArmadilha(5) {
        GC.setSala(&minhaSala);
        minhaSala.setTexturaFundo("Sprites/Cenario2.png");

    }

    FaseSegunda::~FaseSegunda() {}

    void FaseSegunda::criarSlimes() {
        int qtd = rand() % maxSlime + 1;
        float largura = 50.f;
        float altura = 50.f;
        for (int i = 0; i < qtd; i++) {
            float randX = (larguraFase / 2) + (rand() % (int)(larguraFase / 2 - 200)) + 100.f;
            float randY = alturaFase / 2.f;

            Slime* chefao = new Slime(randX, randY, largura, altura);
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
            float randX = zonaSegura + (int)(rand() % (int)(larguraFase - zonaSegura - 150.f)); // MODIFICADO
            float randY = alturaFase / 2.f;

            Armadilha* arm = new Armadilha(randX, randY, largura, altura);
            listaE.incluir(static_cast<Entidade*>(arm), true);
            GC.incluirObstcaulo(arm);
        }
    }
    void FaseSegunda::criarDiamante() {
        float x = larguraFase - 100.f;
        float y = alturaFase - 110.f;
        Diamante* dia = new Diamante(x, y, 40.f, 40.f);
        listaE.incluir(static_cast<Entidade*>(dia), true);
        GC.incluirObstcaulo(dia);
    }

    void FaseSegunda::criarInimigos() {
        // Cria inimigos compartilhados e exclusivos da fase
        criarRatosPenados(); // vinda de Fase (Rato)
        criarSlimes();       // exclusiva fase 2 (Slime)
    }

    void FaseSegunda::criarObstaculo() {
        // Criar o diamante primeiro para que as plataformas evitem sua área
        criarDiamante();
        criarPlataformas();  // compartilhada - vem de Fase
        criarArmadilhas();   // exclusiva fase 2
    }

    void FaseSegunda::incluirJogadores(Jogador* pJog1) {
        Fase::incluirJogadores(pJog1);
        pJog1->setPosition(sf::Vector2f(50.f, alturaFase - 100.f));
    }

    void FaseSegunda::inicializaFase() {
        criarObstaculo();
        criarInimigos();
        inicializarChao();
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
        // desenhar HUD (vida dos jogadores)
        desenharVida(janela);
        // chamada de limparMortos removida daqui para evitar dupla remoção
    }
}