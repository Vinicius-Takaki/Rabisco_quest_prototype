#include "Personagem.h"

namespace Principal {
    Personagem::Personagem() : num_vidas(0) { // CORRIGIDO: inicializa num_vidas
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