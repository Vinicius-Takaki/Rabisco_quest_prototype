#include "GerenciadorGrafico.h"
#include "../Ente.h"
#include <iostream>
using namespace std;

namespace Principal {
    Principal::GerenciadorGrafico* GerenciadorGrafico::pGerenciador = NULL;

    // Construtora para dimensões de tela customizadas
    GerenciadorGrafico::GerenciadorGrafico(unsigned altura, unsigned largura)
     : alturaJanela(altura), larguraJanela(largura) {
        if(!janela) {
            janela = new sf::RenderWindow(sf::VideoMode(
                largura, altura), 
                "Super Irmãs Maria: Cassadoras de Fantasmas!");
            janela->setFramerateLimit(60); // MUITO IMPORTANTE, NÃO ESQUECER DE DEFINIR O LIMITE DE FRAMERATE
        }
        else    
            cerr << "ERRO! \n Tentativa de inicializar janela já existente" << endl;
    }

    GerenciadorGrafico::~GerenciadorGrafico() {
        if (janela->isOpen())
            janela->close();
        janela = NULL;
    }

    // Função que garante o padrão de projeto singleton. Dimensões customizadas.
    GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico(unsigned altura, unsigned largura) {
        // Padrão de projeto singleton

        // Garante que haja apenas um gerenciador gráfico por vez

        if (pGerenciador == NULL) {
            pGerenciador = new GerenciadorGrafico(altura, largura);
            return pGerenciador;
        }
        return pGerenciador;
    }

    // Função que garante o padrão de projeto singleton. Dimensões geréricas.
    GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico() {
        // Padrão de projeto singleton

        // Garante que haja apenas um gerenciador gráfico por vez

        if (pGerenciador == NULL) {
            pGerenciador = new GerenciadorGrafico(700u, 900u);
            return pGerenciador;
        }
        return pGerenciador;
    }
    
    // Desenha ente na janela
    void GerenciadorGrafico::desenharEnte(Ente* pE) {
        pE->desenhar(*janela);
    }

    void GerenciadorGrafico::limpaJanela() {
        janela->clear();
    }

    void GerenciadorGrafico::mostraJanela() {
        janela->display();
    }

    sf::RenderWindow* GerenciadorGrafico::getJanela() const {
        return janela;
    }

    const unsigned int GerenciadorGrafico::getAltura() const {
        return alturaJanela;
    }

    const unsigned int GerenciadorGrafico::getLargura() const {
        return larguraJanela;
    }

    // FECHAR NA CLASSE JOGO
    /*
    void GerenciadorGrafico::fechaJanela() {
        sf::Event evento;
        while (janela->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed ||
                evento.type == sf::Event::KeyPressed && 
                evento.key.code == sf::Keyboard::Escape)

                janela->close();
            }
        }
    }
    */

}