#include "Jogo.h"

namespace Principal {

    Jogo::Jogo()
        : pGG(GerenciadorGrafico::getGerenciadorGrafico(
            static_cast<unsigned int>(alturaJanela),
            static_cast<unsigned int>(larguraJanela))) {
        Ente::setGG(pGG);

        // Carrega e centraliza as imagens de fim de jogo (sem texto)
        texturaDerrota.loadFromFile("Sprites/TelaDerrota.png");
        texturaVitoria.loadFromFile("Sprites/TelaVitoria.png");
        spriteDerrota.setTexture(texturaDerrota);
        spriteVitoria.setTexture(texturaVitoria);

        sf::FloatRect bD = spriteDerrota.getLocalBounds();
        spriteDerrota.setOrigin(bD.width / 2.f, bD.height / 2.f);
        spriteDerrota.setPosition(larguraJanela / 2.f, alturaJanela / 2.f);

        sf::FloatRect bV = spriteVitoria.getLocalBounds();
        spriteVitoria.setOrigin(bV.width / 2.f, bV.height / 2.f);
        spriteVitoria.setPosition(larguraJanela / 2.f, alturaJanela / 2.f);
    }

    Jogo::~Jogo() {
        if (pGG) {
            delete pGG;
            pGG = NULL;
        }
    }

    void Jogo::executar() {
		// Loop principal do jogo
        while (pGG->getJanela()->isOpen()) {
            sf::Event evento;
            while (pGG->getJanela()->pollEvent(evento)) {
                if (evento.type == sf::Event::Closed ||
                    (evento.type == sf::Event::KeyPressed &&
                        evento.key.code == sf::Keyboard::Escape))
                    pGG->getJanela()->close();
            }

            pGG->limpaJanela();
			// Atualiza a lógica do jogo e desenha os elementos na tela
            if (jogoGanho) {
                sf::View viewPadrao;
                viewPadrao.setSize(larguraJanela, alturaJanela);
                viewPadrao.setCenter(larguraJanela / 2.f, alturaJanela / 2.f);
                pGG->getJanela()->setView(viewPadrao);

                pGG->getJanela()->draw(spriteVitoria);
                if (clockReiniciar.getElapsedTime().asSeconds() > 2.0f) {
                    fase1.limpaFase();
                    fase2.limpaFase();
                    faseAtual = 1;
                    faseInicializada = false;
                    jogador1.resetar();
                    jogoGanho = false;
                }
            }
            // Desenha a tela de derrota
            else if (jogoPerdido) {
                sf::View viewPadrao;
                viewPadrao.setSize(larguraJanela, alturaJanela);
                viewPadrao.setCenter(larguraJanela / 2.f, alturaJanela / 2.f);
                pGG->getJanela()->setView(viewPadrao);

                pGG->getJanela()->draw(spriteDerrota);
				// Reinicia o jogo após 2 segundos
                if (clockReiniciar.getElapsedTime().asSeconds() > 2.0f) {
                    fase1.limpaFase();
                    fase2.limpaFase();
                    faseAtual = 1;
                    faseInicializada = false;
                    jogador1.resetar();
                    jogoPerdido = false;
                }
            }
            else {
				// Atualiza a fase atual e inicializa se necessário
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

                atualizarCamera();

                if (faseAtual == 1) {
                    fase1.executar(pGG->getJanela());

                    if (jogador1.getPosicao().x >= 3500.f) {
                        fase1.limpaFase();
                        faseAtual = 2;
                        faseInicializada = false;
                    }
                }
                else if (faseAtual == 2) {
                    fase2.executar(pGG->getJanela());
					// Verifica se o jogador venceu ou chegou ao final da fase, e reinicia o jogo após 2 segundos depois de mostrar a tela de vitória
                    if (jogador1.getVenceu() || jogador1.getPosicao().x >= larguraFase - 50.f) {
                        jogoGanho = true;

						//resetar jogo depois de 2 segundos
						
                        clockReiniciar.restart();

                    }
                }
          

                if (!jogador1.getVivo() || jogador1.getNumVidas() <= 0) {
                    jogoPerdido = true;
                    clockReiniciar.restart();
                }
            }

            pGG->mostraJanela();
        }
    }

    void Jogo::atualizarCamera() {
        if (!jogador1.getVivo()) return;

        sf::RenderWindow* janela = pGG->getJanela();

        sf::View camera;
        camera.setSize(larguraJanela, alturaJanela);

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