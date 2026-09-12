#pragma once
#include "Inimigo.h"
//
// A DEFINIRRR
//

namespace Principal {
	class Sapo :
		public Inimigo
	{
	private:
		float raio; // distância máxima para perseguir o jogador
		float tamanho;
		sf::Clock clockPulo; // para controlar o tempo entre pulos
		int temp_pulo; // tempo mínimo entre pulos, em segundos
		float velAtual;
	public:
		Sapo(float x, float y, float  largura, float altura);
		~Sapo();
		void executar();
		void mover();
		void perseguir(sf::Vector2f pos_alvo, sf::Vector2f pos_inimigo);
		void danificar(Jogador* p); // método para causar dano ao jogador
		void salvar();
	};
}
