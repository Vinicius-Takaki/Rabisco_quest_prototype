#include "Inimigo.h"

namespace Principal {
    Inimigo::Inimigo() : nivel_maldade(rand() % 3 + 1), alvo(nullptr) {}
    Inimigo::~Inimigo() {}
    void Inimigo::salvarDataBuffer() {}
	void Inimigo::setAlvo(Jogador* jogador) { alvo = jogador; }
}
