#include "ListaEntidade.h"
#include "../Entidades/Personagens/Inimigo.h"
#include "../Gerenciadores/GerenciadorColisao.h"


namespace Principal {
    ListaEntidades::ListaEntidades() {}
    ListaEntidades::~ListaEntidades() {}

    void ListaEntidades::incluir(Entidade* pE, bool d)
    {
        LEs.incluir(pE, d);
    }

    // Percorre e executa elementos
    void ListaEntidades::percorrer()
    {
        Lista<Entidade>::Elemento* pElem = LEs.getPrimeiro();
        while (pElem != nullptr)
        {
            Entidade* pE = pElem->getInfo();
            if (pE)
            {
                pE->executar();
            }
            pElem = pElem->getProx();
        }
    }

    // Percorre e desenha elementos
    void ListaEntidades::desenhaTodos(sf::RenderWindow& janela) {
        Lista<Entidade>::Elemento* pElem = LEs.getPrimeiro();
        while (pElem != nullptr)
        {
            Entidade* pE = pElem->getInfo();
            if (pE)
            {
                pE->desenhar(janela); //
            }
            pElem = pElem->getProx();
        }
    }

    void ListaEntidades::limpar() {
        LEs.limpar();
    }

    void ListaEntidades::limparMortos(GerenciadorColisao* pGC) {
        Lista<Entidade>::Elemento* pElem = LEs.getPrimeiro();
        Lista<Entidade>::Elemento* pProx = nullptr;
        while (pElem != nullptr) {
            pProx = pElem->getProx();
            Entidade* pE = pElem->getInfo();
            if (pElem->dinamico && pE && !pE->getVivo()) {
                // ADICIONADO: notifica GC antes de deletar
                if (pGC) {
                    Inimigo* ini = dynamic_cast<Inimigo*>(pE);
                    if (ini) pGC->removerInimigo(ini);
                }
                LEs.remover(pE);
            }
            pElem = pProx;
        }
    }
}
