#pragma once
#include "../Entidade.h"

// =========================== //

namespace Principal { // Classe que define um espaço confinado da fase onde qualquer entidade pode se encontrar
    class Sala : public Ente {
    private:
        // Dimesoes da sala
        const int altura;
        const int largura;

        // Area da sala utilizada para prender entidades
        sf::RectangleShape area;

    public:
        Sala(int alturaFornecida, int larguraFornecida);
        Sala();
        ~Sala();

        void limitar(Entidade* ent); // Empurra entidade para dentro da sala

        void executar() {};
        void desenhar(sf::RenderWindow& window); // Desenha a sala. NOTA: a sala futuramente vai usar uma imagem como fundo, ao invés de uma forma sólida
    };
   
}