#pragma once
#include "Obstaculo.h"

namespace Principal {
	class Lama : public Obstaculo {
	private:
		float largura;
	public:
		Lama(float x, float y, float largura, float altura);
		~Lama();
		void executar();
		void salvar();
		void obstacularizar(Jogador* p);
	};
}
