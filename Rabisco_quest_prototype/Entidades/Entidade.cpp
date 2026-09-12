#include "Entidade.h"
#include "../Gerenciadores/GerenciadorTexturas.h" 
#include <iostream>

namespace Principal {
    Entidade::Entidade() : x(0.f), y(0.f), noChao(false), velY(0.f), vivo(true), temTextura(false) {
        corpo.setPosition(x, y);
    }

    Entidade::~Entidade() {}

    bool Entidade::carregarTextura(const std::string& caminho) {
        sf::Texture* tex = GerenciadorTexturas::getInstancia().obterTextura(caminho);
        if (!tex) {
            temTextura = false;
            return false;
        }

        sprite.setTexture(*tex);

        sf::Vector2f tamCorpo = corpo.getSize();
        sf::Vector2u tamTextura = tex->getSize();
        if (tamTextura.x > 0 && tamTextura.y > 0) {
            sprite.setScale(tamCorpo.x / static_cast<float>(tamTextura.x),
                tamCorpo.y / static_cast<float>(tamTextura.y));
        }
        sprite.setPosition(corpo.getPosition());
        temTextura = true;
        return true;
    }

    void Entidade::desenhar(sf::RenderWindow& window) {
        if (temTextura) {
            sprite.setPosition(corpo.getPosition());
            window.draw(sprite);
        }
        else {
            window.draw(corpo);
        }
    }

    void Entidade::salvarDataBuffer() {}

    sf::RectangleShape& Entidade::getCorpo() {
        return corpo;
    }

    void Entidade::aplicarGravidade() {
        if (!noChao) {
            if (velY < 10.f)
                velY += 0.5f;
        }
        corpo.move(0.f, velY);
        noChao = false;
    }

    sf::Vector2f Entidade::getPosicao() const {
        return corpo.getPosition();
    }

    void Entidade::setPosition(sf::Vector2f pos) {
        corpo.setPosition(pos);
        x = pos.x;
        y = pos.y;
        if (temTextura)
            sprite.setPosition(pos);
    }

    void Entidade::pousar() {
        velY = 0.f;
        noChao = true;
    }

    void Entidade::setVivo(bool v) {
        vivo = v;
    }

    bool Entidade::getVivo() const {
        return vivo;
    }

    sf::Vector2f Entidade::getTam() const {
        return corpo.getSize();
    }
}