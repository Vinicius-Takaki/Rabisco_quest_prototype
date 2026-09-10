#pragma once
#include "Lista.h"
#include "../Entidades/Entidade.h"
#include "../Entidades/Personagens/Inimigo.h"
#include "../Gerenciadores/GerenciadorColisao.h"
namespace Principal {
    class GerenciadorColisao;
    class ListaEntidades {
    private:
        Lista<Entidade> LEs;

    public:
        ListaEntidades();
        ~ListaEntidades();

        void incluir(Entidade* pE, bool d); // Inclui elemento na lista
        void percorrer(); // Percorre e executa elementos
        void desenhaTodos(sf::RenderWindow& janela); // Percorre e desenha elementos
        void limpar(); // Esvazia lista
        void limparMortos(GerenciadorColisao* pGC = nullptr); 
    };
}