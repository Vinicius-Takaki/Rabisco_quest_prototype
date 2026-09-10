#pragma once
#include "Personagem.h"
#include <SFML/Graphics.hpp>

namespace Principal {
    class Inimigo; 
    class Jogador : public Personagem {
    public:
        int pontos;
        Inimigo* pIn; // ponteiro para inimigo (usado na colisão futuramente) 
        bool naLama;
        sf::Vector2f velOriginal;
        sf::Clock clockDano;
    public:
        Jogador();
        ~Jogador();
        void colidir(Entidade* pIn); // reação ao colidir com inimigo
        void salvar();
        void mover(); // lê teclado e move o jogador
        void executar();
        void diminuirVelocidade(); //a forma que eu vi de diminuir a velocidade do jogador caso haja o efeito da lama
        void adicionarPontos(int p);
        void restaurarVelocidade();
       
		
        
    };
}
