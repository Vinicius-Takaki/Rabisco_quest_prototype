#pragma once
#include <SFML/Graphics.hpp>

namespace Principal {
    class GerenciadorGrafico;

    class Ente {
    protected:
        int id; // identificador único do ente
        static GerenciadorGrafico* pGG; 
        static sf::RenderWindow* pJanela;
        static int contador_id; // contador para gerar IDs únicos

    public:
        Ente();
        virtual ~Ente();

        virtual void executar() = 0;
        virtual void desenhar(sf::RenderWindow& window) = 0; // desenha na tela

        static void setGG(GerenciadorGrafico* pG);
        static void setJanela(sf::RenderWindow* j);
        static GerenciadorGrafico* getGG();
       
    };
}


