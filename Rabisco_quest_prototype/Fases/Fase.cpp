#include "Fase.h"
#include "../Entidades/Personagens/Rato.h"
#include "../Entidades/Entidade.h"
#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Ente.h"
#include "../Gerenciadores/GerenciadorGrafico.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
namespace Principal {
    Fase::Fase()
        : maxRatos(5), maxPlataformas(5), minhaSala(alturaFase, larguraFase),
        pJ1(nullptr) {
        sementear();

    }

    Fase::~Fase() {
        // ...
    }
    // Esvazia a lista e desaloca entidades
    void Fase::limpaFase() {
        // Primeiro limpar referências no GerenciadorColisao para evitar
        // dangling pointers (GC mantém ponteiros para entidades que serão
        // deletadas pela lista). Depois liberar as entidades.
        GC.limpar();
        listaE.limpar();
    }

    void Fase::criarRatosPenados() {
        int qtd = rand() % (maxRatos + 1 - 3) + 5;
        float largura = 40.f;
        float altura = 40.f;

        for (int i = 0; i < qtd; i++) {
            float randX = zonaSegura + (rand() % (int)(larguraFase - zonaSegura - 200.f));
            float randY = alturaFase/2.f;

            Rato* inimigo = new Rato(randX, randY, largura, altura);
            inimigo->setAlvo(pJ1);
            listaE.incluir(static_cast<Entidade*>(inimigo), true);
            GC.incluirInimigo(inimigo);
        }
    }
    // Fase.cpp
    void Fase::criarChao() {
        float largura = (float)larguraFase;
        float altura = 90.f;
        float x = 0.f;
        float y = alturaFase - altura;

        Plataforma* chao = new Plataforma(x, y, largura, altura);
        chao->carregarTextura(getTexturaChao());
        listaE.incluir(static_cast<Entidade*>(chao), true);
        GC.incluirObstcaulo(chao);
    }


    // Cria obstáculo 1 (plataformas)
    void Fase::criarPlataformas() {
        int qtd = rand() % (maxPlataformas + 1 - 3) + 3;
        float largura = 300.f;
        float altura = 40.f;

        float zonaLargura = (larguraFase - zonaSegura - 700.f) / qtd;

        for (int i = 0; i < qtd; i++) {
            float baseX = zonaSegura + i * zonaLargura;
            float randX = baseX + (rand() % (int)(zonaLargura - largura));
            float randY = alturaFase - 90.f - (rand() % 100 + 20);
			//Create a new Plataforma object and add it to the list and collision manager

            Plataforma* plat = new Plataforma(randX, randY, largura, altura);
            plat->carregarTextura(getTexturaChao());
            listaE.incluir(static_cast<Entidade*>(plat), true);
            GC.incluirObstcaulo(plat);
        }
    }
    // ainda não sei o que fazer com essa função. não vou retirar pois está no diagrama,
    // porém o que eu imagino que seja a utilidade dela (criar o background), vai ser feito
    // em cada fase individual por meio da classe Sala
    void Fase::criarCenario() {
        // Do something...
    }

    // Inclui jogadores na lista. Não deve ser chamada mais do que uma vez !!!
    void Fase::incluirJogadores(Jogador* pJog1) {
        pJ1 = pJog1; //
        listaE.incluir(pJ1, false);
        GC.setJogador1(pJ1);
 
    }
    

    void Fase::inicializarChao() {
        criarChao();
    }

    // CÓDIGO INSPIRADO NA FUNÇÃO SEMENTAR FORNECIDA NAS PROVAS DE TECPROG
    // Nota: não foi testado se está funcionando. Na dúvida, pesquise no google ou pegue o código 100% dos exemplos do professor (com cŕeditos é claro ;D)
    void Fase::sementear() {
        time_t t;
        srand(time(&t)); // talvez dê problema com tempo negativo (se existir essa coisa legal!!!)
    }

    void Fase::desenharVida(sf::RenderWindow* janela) {
        if (!janela) return;

        // Carrega a textura uma unica vez (idealmente isso deveria estar
        // em um membro da classe ou no GerenciadorTexturas, nao aqui dentro,
        // mas segue o exemplo minimo por enquanto)
        static sf::Texture texturaCoracao;
        static bool texturaCarregada = texturaCoracao.loadFromFile("Sprites/Coracao.png");

        const float heartSize = 20.f;
        const float padding = 6.f;

        auto desenharVidasJogador = [&](Jogador* pJ) {
            if (!pJ || !pJ->getVivo()) return;

            int vidas = pJ->getNumVidas();
            sf::Vector2f pos = pJ->getPosicao();
            sf::Vector2f tam = pJ->getTam();
            float centerX = pos.x + tam.x / 2.f;
            float totalWidth = vidas * (heartSize + padding) - padding;
            float startX = centerX - totalWidth / 2.f;
            float y = pos.y - heartSize - 8.f;

            for (int i = 0; i < vidas; ++i) {
                if (texturaCarregada) {
                    sf::Sprite coracao(texturaCoracao);
                    sf::Vector2u tamTex = texturaCoracao.getSize();
                    coracao.setScale(heartSize / tamTex.x, heartSize / tamTex.y);
                    coracao.setPosition(startX + i * (heartSize + padding), y);
                    janela->draw(coracao);
                }
                else {
                    // Fallback: se a textura nao carregar, desenha o retangulo antigo
                    sf::RectangleShape fallback(sf::Vector2f(heartSize, heartSize));
                    fallback.setFillColor(sf::Color::Red);
                    fallback.setPosition(startX + i * (heartSize + padding), y);
                    janela->draw(fallback);
                }
            }
            };

        desenharVidasJogador(pJ1);
    }
}
