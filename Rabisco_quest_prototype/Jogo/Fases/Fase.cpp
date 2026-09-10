#include "Fase.h"
#include "../Entidades/Personagens/Alma.h"
#include "../Entidades/Entidade.h"
#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Ente.h"
#include "../Gerenciadores/GerenciadorGrafico.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
namespace Principal {
    Fase::Fase()
    : maxAlmas(5), maxPlataformas(5), minhaSala(alturaFase, larguraFase),
        pJ1(nullptr), pJ2(nullptr) {
        sementear(); // Irei colocar o sementear no construtor porque ao colocar nas outras funções de criação simplemente não geravam mais de uma entidade

    }

    Fase::~Fase() {
        // ...
    }
    // Esvazia a lista e desaloca entidades
    void Fase::limpaFase() {
        listaE.limpar();
        GC.limpar();
    }

    // Cria inimigos fáceis
    void Fase::criarAlmasPenadas() {
        //sementear(); 
        int qtd = rand() % (maxAlmas + 1 - 3) + 5;
        float largura = 40.f;
        float altura = 40.f;

        for (int i = 0; i < qtd; i++) {
            float randX = (int)(rand() % (int)(larguraFase - 200.f));
            float randY = alturaFase - 60.f;
			Alma* inimigo = new Alma(50.f + randX, randY, largura, altura); // posição aleatória dentro de uma área 
            inimigo->setAlvo(pJ1); // Define jogador como alvo
			listaE.incluir(static_cast<Entidade*>(inimigo), true); // talvez dê erro // não lembro por que pudesse dar erro, mas chuto que seja por causa do static_cast
            GC.incluirInimigo(inimigo); // registra no GC para colisão
        }
    }


    // Cria obstáculo 1 (plataformas)
    void Fase::criarPlataformas() {
        //sementear();
        int qtd = rand() % (maxPlataformas + 1 - 3) + 3;
        int i;
        float largura = 300.f;
        float altura = 40.f;

        for (i = 0; i < qtd; i++) {
            //sementear(); 

            // Coordenadas aleatórias não testadas. formato: (... - (d)) + distancia minima, onde d = distancia maxima + distancia minima
            float randX = (int)(rand() % (larguraFase - 250)) + 50.f;
            float randY = alturaFase - 60.f; // INT PARA FLOAT PODE DAR PROBLEMA

            float largura = 300.f;
            float altura = 40.f;

            Plataforma* plat = new Plataforma(randX, randY, largura, altura);
            listaE.incluir(static_cast<Entidade*>(plat), true); // talvez dê erro // não lembro por que pudesse dar erro, mas chuto que seja por causa do static_cast
            GC.incluirObstcaulo(plat); // registra no GC para colisão        
        }
    }

    // ainda não sei o que fazer com essa função. não vou retirar pois está no diagrama,
    // porém o que eu imagino que seja a utilidade dela (criar o background), vai ser feito
    // em cada fase individual por meio da classe Sala
    void Fase::criarCenario() {
        // Do something...
    }

    // Inclui jogadores na lista. Não deve ser chamada mais do que uma vez !!!
    void Fase::incluirJogadores(Jogador* pJog1, Jogador* pJog2) {
        pJ1 = pJog1; //
        pJ2 = pJog2;
        listaE.incluir(pJ1, false);
        GC.setJogador1(pJ1);
        if (pJ2) {
            listaE.incluir(pJ2, false);
            GC.setJogador2(pJ2);
        }
    }


    // CÓDIGO INSPIRADO NA FUNÇÃO SEMENTAR FORNECIDA NAS PROVAS DE TECPROG
    // Nota: não foi testado se está funcionando. Na dúvida, pesquise no google ou pegue o código 100% dos exemplos do professor (com cŕeditos é claro ;D)
    void Fase::sementear() {
        time_t t;
        srand(time(&t)); // talvez dê problema com tempo negativo (se existir essa coisa legal!!!)
    }
}