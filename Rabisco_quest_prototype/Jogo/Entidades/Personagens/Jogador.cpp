#include "Jogador.h"
#include "Inimigo.h"
#include <SFML/Graphics.hpp>

namespace Principal {
    Jogador::Jogador() : pontos(0), naLama(false) {
		//id = Principal::ID_JOGADOR;
		num_vidas = 3;
        corpo.setSize(sf::Vector2f(40, 40));
        corpo.setFillColor(sf::Color::White);
        corpo.setPosition(sf::Vector2f(100.f, 275.f));

        //velocidade horizontal 5.0f
        vel = sf::Vector2f(5.0f, 0.0f);
        velOriginal = vel;
    }

    Jogador::~Jogador() {}

    void Jogador::executar() {
        if (!getVivo()) return;
        mover();
        aplicarGravidade();
        // CORRIGIDO: restaura velocidade automaticamente se não foi renovado pela lama
        if (!naLama)
            restaurarVelocidade();
        naLama = false; // reseta todo frame — lama renova se ainda colidir

    }
    void Jogador::mover() {
        // Movimentação horizontal
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Referencia: https://www.youtube.com/watch?v=WrJpux-vpcI&list=PLR17O9xbTbIBBoL3lli44N8LdZVvg-_uZ&index=2
            corpo.move(-vel.x, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            corpo.move(vel.x, 0.0f);

        // Pulo (Teclando W e estando no chão)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && noChao) {
            velY = -12.0f;  // Força que empurra o jogador para cima apenas quando estiver no chão
            noChao = false; // saiu do chão
        }
    }
    void Jogador::adicionarPontos(int p) {
		pontos += p; // Adiciona os pontos ganhos ao total
   }

    void Jogador::salvar() {}
    void Jogador::colidir(Entidade* pIn) {
        if (clockDano.getElapsedTime().asSeconds() < 0.5f) return;

        if (pIn) {
            float direcao = corpo.getPosition().x - pIn->getPosicao().x;
            if (direcao > 0)
                corpo.move(50.f, -5.f); 
            else
                corpo.move(-50.f, -5.f);
        }
        operator--();
        clockDano.restart();
    }

    void Jogador::diminuirVelocidade() {
        vel.x = velOriginal.x * 0.2f;
        naLama = true;
    }
    void Jogador::restaurarVelocidade() {
        vel = velOriginal;
    }
 }
