#pragma once
#include "Obstaculo.h"

namespace Principal {
	class Armadilha :
		public Obstaculo {
	protected:
		short int danosidade;
	public:
		Armadilha(float x, float y, float largura, float altura);
		~Armadilha();
		void executar();
		void obstacularizar(Jogador* p); //a reação do jogador ao pisar na armadilha é artodoar o jogador e dar dano
		void salvar();
	};
}
