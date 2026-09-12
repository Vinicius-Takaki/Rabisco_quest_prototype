#pragma once
#include "../Entidade.h"

namespace Principal {
    class Personagem : public Entidade {
    protected:

        //sf::Vector2f vel; irei colocar em entidade
        int num_vidas;  // quantidade de vidas

    public:
        Personagem();
        virtual ~Personagem();

        void salvarDataBuffer();
        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover() = 0;
        Personagem& operator--();       // perde uma vida
        int getNumVidas() const { return num_vidas; }

        //void pousar(); // chamada quando o personagem colidir com o chão, para resetar o pulo
        //void aplicarGravidade(); // aumenta velY e move o corpo para baixo
        //void setPosition(sf::Vector2f pos); // reposiciona o corpo
    };
}

