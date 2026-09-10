#pragma once
#include "../Ente.h"
#include <SFML/Graphics.hpp>
#include <sstream>

namespace Principal {
    // Entidade adiciona forma visual e posição ao Ente
    class Entidade : public Ente {
    protected:
        float x, y;  // posição
        sf::RectangleShape corpo;  // forma retangular que representa o objeto na tela
        //std::ostream buffer; //Implementar depos, não sei o que fazer com isso
        bool noChao; // controla se pode pular e se aplica gravidade
        float velY;  // velocidade vertical atual (afetada pela gravidade)
		bool vivo; // controla se a entidade está ativa no jogo (pode ser usada para remover inimigos mortos, por exemplo)
        sf::Vector2f vel; // fiz isso para ser herdada em projetil e personagens


    public:
        Entidade();
        virtual ~Entidade();

        virtual void executar() = 0;
        virtual void desenhar(sf::RenderWindow& window); // desenha o corpo na janela
        virtual void salvar() = 0;

        void salvarDataBuffer();
        void setPosition(sf::Vector2f pos); 
        sf::RectangleShape& getCorpo(); // retorna referência ao corpo 
        sf::Vector2f getPosicao() const;  // retorna posição atual do corpo
		virtual void aplicarGravidade(); // Agora com comportamento real aqui, para ser chamado no executar() dos personagens
		void pousar(); // chamada quando o personagem colidir com o chão, para resetar o pulo
		bool getVivo() const; // retorna se a entidade está viva
        sf::Vector2f getTam() const;
		void setVivo(bool v); // define se a entidade está viva ou não
		//int getID() const { return id; } 
    };
}