#pragma once
#include "Inimigo.h"

namespace Principal {
	class Rato : public Inimigo
	{
	private:
		float raio;  // distância máxima para detectar e perseguir o jogador
		float velAtual;


	public:
		Rato(float x, float y, float largura, float altura);// construtor para criar inimigo em posição específica
		~Rato();

		void executar();
		void danificar(Jogador* p);
		void salvar();
		void mover();

		void perseguir(sf::Vector2f pos_alvo, sf::Vector2f pos_inimigo); // move em direção ao jogador
	};
}
