
#include "Jogo.h"


namespace Principal {

    Jogo::Jogo()
        : pGG(GerenciadorGrafico::getGerenciadorGrafico(alturaJanela, larguraJanela)) {
        Ente::setGG(pGG);




    }

    Jogo::~Jogo() {
        if (pGG) {
            delete pGG;
            pGG = NULL;
        }
    }

    void Jogo::executar() {

        while (pGG->getJanela()->isOpen()) {
            sf::Event evento;
            while (pGG->getJanela()->pollEvent(evento)) {
                if (evento.type == sf::Event::Closed ||
                    (evento.type == sf::Event::KeyPressed &&
                        evento.key.code == sf::Keyboard::Escape))
                    pGG->getJanela()->close();
            }

            // inicializa a fase escolhida uma única vez
            if (!faseInicializada) {
                if (faseAtual == 1) {
                    fase1.incluirJogadores(&jogador1);
                    fase1.inicializaFase();
                }
                else if (faseAtual == 2) {
                    fase2.incluirJogadores(&jogador1);
                    fase2.inicializaFase();
                }
                faseInicializada = true;
            }

            pGG->limpaJanela();
            atualizarCamera();

            if (faseAtual == 1) {
                fase1.executar(pGG->getJanela());

                if (jogador1.getPosicao().x >= 3500.f) {
                    fase1.limpaFase();
                    faseAtual = 2;
                    faseInicializada = false;  // ← vai inicializar a fase 2 no próximo frame
                }

            }
            else if (faseAtual == 2) {
                fase2.executar(pGG->getJanela());
            }

            pGG->mostraJanela();
        }
    }

    void Jogo::atualizarCamera() {
        if (!jogador1.getVivo()) return;

        sf::RenderWindow* janela = pGG->getJanela();

        sf::View camera;
        camera.setSize(larguraJanela, alturaJanela);  // tamanho fixo da janela

        float camX = jogador1.getPosicao().x + 20.f;
        float metadeJanela = larguraJanela / 2.f;

        if (camX < metadeJanela)
            camX = metadeJanela;
        if (camX > larguraFase - metadeJanela)
            camX = larguraFase - metadeJanela;

        camera.setCenter(camX, alturaJanela / 2.f);
        janela->setView(camera);
    }
}
