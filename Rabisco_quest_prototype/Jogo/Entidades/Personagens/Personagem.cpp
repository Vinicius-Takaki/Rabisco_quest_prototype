#include "Personagem.h"

namespace Principal {
    Personagem::Personagem(){
    }

    Personagem::~Personagem() {}

    void Personagem::salvarDataBuffer() {}

    Personagem& Personagem::operator--()
    {
        num_vidas--;
        if (num_vidas < 0)
            setVivo(false);
        return *this;
    }
}


    /*void Personagem::setPosition(sf::Vector2f pos) {
        corpo.setPosition(pos); // Reposiciona o corpo e sincroniza x,y 
        x = pos.x;
        y = pos.y;
    }
    void Personagem::pousar() {
        velY = 0.f;
        noChao = true;
    }
    */







