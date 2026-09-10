#include "Pisadeira.h"
#include "../../Gerenciadores/GerenciadorColisao.h"
#include "../../Gerenciadores/GerenciadorGrafico.h"

#include <cmath>

namespace Principal {
    Pisadeira::Pisadeira(float x, float y, float largura, float altura)
        : raio(150.0f), raioTiro(300.0f), tamanho(50.0f), temp_Tiro(2.0f),
        tiro(nullptr), pGC(nullptr) {
        nivel_maldade = 3;
        forca = nivel_maldade * 5;
        corpo.setSize(sf::Vector2f(tamanho, tamanho));
        corpo.setFillColor(sf::Color::Yellow);
        corpo.setPosition(sf::Vector2f(x, y));
        vel = sf::Vector2f(3.0f, 0.0f);
    }

    Pisadeira::~Pisadeira() {
        if (tiro) {
            tiro->setAtivo(false);
            tiro = nullptr;
        }
    }

    void Pisadeira::executar() {
        mover();
        aplicarGravidade();
        fazerProjetil();
        atualizarProjetil();
    }

    void Pisadeira::mover() {
        if (alvo != nullptr) {
            sf::Vector2f pos_alvo = alvo->getCorpo().getPosition();
            sf::Vector2f pos_inimigo = corpo.getPosition();
            if (fabs(pos_alvo.x - pos_inimigo.x) <= raio &&
                fabs(pos_alvo.y - pos_inimigo.y) <= raio)
                perseguir(pos_alvo);
        }
    }

    void Pisadeira::perseguir(sf::Vector2f pos_alvo) {
        sf::Vector2f pos_inimigo = corpo.getPosition();
        if (pos_alvo.x - pos_inimigo.x > 0)
            corpo.move(vel.x, 0);
        else if (pos_alvo.x - pos_inimigo.x < 0)
            corpo.move(-vel.x, 0);
    }

    void Pisadeira::fazerProjetil() {
        if (tiro != nullptr) return;
        if (alvo == nullptr) return;

        sf::Vector2f pos_alvo = alvo->getCorpo().getPosition();
        sf::Vector2f pos_inimigo = corpo.getPosition();

        float dx = pos_alvo.x - pos_inimigo.x;
        float dy = pos_alvo.y - pos_inimigo.y;


        float distancia = sqrt(dx * dx + dy * dy);

        if (distancia <= raioTiro && clock_Tiro.getElapsedTime().asSeconds() > temp_Tiro) {


            sf::Vector2f direcao(dx / distancia * forca, dy / distancia * forca);

            tiro = new Projetil(pos_inimigo.x, pos_inimigo.y, direcao);
            if (pGC) pGC->incluirProjetil(tiro);
            clock_Tiro.restart();
        }
    }


    void Pisadeira::atualizarProjetil() {
        if (tiro == nullptr) return;
        if (tiro->getAtivo()) {
            tiro->executar();
            if (Ente::getGG() && Ente::getGG()->getJanela())
                tiro->desenhar(*Ente::getGG()->getJanela());
        }
        else {
            tiro = nullptr;
        }
    }



    void Pisadeira::danificar(Jogador* p) {
        p->colidir(this);
    }

    void Pisadeira::salvar() {}

}