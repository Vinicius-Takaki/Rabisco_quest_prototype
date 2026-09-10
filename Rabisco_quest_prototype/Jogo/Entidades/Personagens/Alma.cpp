#include "Alma.h"
#include <cmath>

namespace Principal {
    
    Alma::Alma(float x, float y, float altura, float largura) : raio(300.0f) /*alvo(nullptr)*/
    {
        corpo.setSize(sf::Vector2f(altura, largura));
        corpo.setFillColor(sf::Color::Red);
        corpo.setPosition(sf::Vector2f(x, y));
        vel = sf::Vector2f(2.0f * nivel_maldade, 0.0f * nivel_maldade);
    }

    Alma::~Alma() {}


    void Alma::executar() { mover(); aplicarGravidade(); }

    void Alma::mover()
    {
        if (alvo != nullptr)
        {
            sf::Vector2f pos_alvo = alvo->getCorpo().getPosition();
            sf::Vector2f pos_inimigo = corpo.getPosition();
            // só persegue se o jogador estiver dentro do raio de detecção
            if (fabs(pos_alvo.x - pos_inimigo.x) <= raio && fabs(pos_alvo.y - pos_inimigo.y) <= raio) //Referencia: https://www.youtube.com/watch?v=HXFTzs7jzJ8&list=PLR17O9xbTbIBBoL3lli44N8LdZVvg-_uZ&index=3
            {
                perseguir(pos_alvo, pos_inimigo);
            }
        }


    }
    // Move horizontalmente na direção do jogador
    void Alma::perseguir(sf::Vector2f pos_alvo, sf::Vector2f pos_inimigo) //Referencia: https://www.youtube.com/watch?v=HXFTzs7jzJ8&list=PLR17O9xbTbIBBoL3lli44N8LdZVvg-_uZ&index=3
    { 
        if (pos_alvo.x - pos_inimigo.x > 0)
            corpo.move(vel.x, 0);  // jogador está à direita
        else if (pos_alvo.x - pos_inimigo.x < 0)
            corpo.move(-vel.x, 0); // jogador está à esquerda
    }

    void Alma::danificar(Jogador* p) 
    {
        p->colidir(this);
    }
    void Alma::salvar() {}
}

