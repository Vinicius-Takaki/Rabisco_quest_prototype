#include <cstddef>
#pragma once

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //
// !!!!!!! PRECISA ATUALIZAR AS PERMISÕES DO ELEMENTO DA LISTA !!!!!!! //
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //
// por causa do diagrama maldito (vou cagar nas calças)

namespace Principal {

    template <class TL>
    class Lista {
    public:
        // Classe aninhada Elemento de objetos da lista
        class Elemento { // 
        public: // PRECISA MUDAR PARA PRIVATE !!!
            Elemento* pProx;
            TL* pInfo;
            bool dinamico;

        public:
            Elemento(bool d);
            ~Elemento();

            void incluir(TL* p); // Inclui elemento na lista
            void setProx(Elemento* pE); // Define elemento como próximo da lista
            Elemento* getProx() const; // Retorna o próximo elemento

            TL* getInfo() const { return pInfo; } // Retorna valor guardado no elemento
        };

        // Demais atributos privados
    private:
        Elemento* pPrimeiro;
        Elemento* pUltimo;

    public:
        Lista();
        virtual ~Lista();
        Elemento* getPrimeiro() const { return pPrimeiro; }
        Elemento* getUltimo() const { return pUltimo; }
        void incluir(TL* p, bool d); // Inclui elemento na lista
        void limpar(); // Esvazia e desaloca lista
        void remover(TL* elemento);
        //void executar();
    };

    // ============================================= //
    // =============== IMPLEMENTAÇÃO =============== //
    // ============================================= //

    // Implementação das funções do Elemento
    template<class TL>
    Lista<TL>::Elemento::Elemento(bool d)
        : pProx(nullptr), pInfo(nullptr), dinamico(d) {
        // do something...
    }

    template<class TL>
    Lista<TL>::Elemento::~Elemento() {
        if (pInfo) {
            if (dinamico) // ATENTAR-SE A D !!! (pode ser que cause problemas mais tarde)
                delete pInfo;
        }
        //if (pInfo)
        //    delete pInfo;
        pProx = nullptr;
        pInfo = nullptr;
    }

    // Retorna prox
    template<class TL>
    typename Lista<TL>::Elemento* Lista<TL>::Elemento::getProx() const {
        return pProx;
    }

    // Define prox
    template<class TL>
    void Lista<TL>::Elemento::setProx(Elemento* pE) {
        pProx = pE;
    }

    // Define o elemento apontado por pInfo
    template<class TL>
    void Lista<TL>::Elemento::incluir(TL* p) {
        pInfo = p;
    }


    // Implementação das funções da Lista
    template<class TL>
    Lista<TL>::Lista()
        : pPrimeiro(nullptr), pUltimo(nullptr) {
       
    }

    template<class TL>
    Lista<TL>::~Lista() {
        limpar();
    }

    // Inclui info na lista
    template<class TL>
    void Lista<TL>::incluir(TL* p, bool d) {
        Elemento* pE = new Elemento(d);
        if (!pE)
            return; // !!!
        pE->incluir(p);

        // Confere se há algum elemento na lista
        if (!(pPrimeiro && pUltimo)) {
            pPrimeiro = pE;
            pUltimo = pE;
        }
        else {
            pUltimo->setProx(pE); // Não foi sugerido pelo auto-completar, pode acarretar problemas
            pUltimo = pE;
        }
    }

    // Esvazia lista e desaloca elementos
    template<class TL>
    void Lista<TL>::limpar() {
        Elemento* pAux = pPrimeiro;

        while (pAux != nullptr) {
            Elemento* pPrev = pAux;
            pAux = pAux->getProx();
            delete pPrev; // elemento dinamico será desalocado na propria destrutoria de Elemento
        }

        pPrimeiro = nullptr;
        pUltimo = nullptr;
    }


    // Se eu me lembro corretamente, era uma função para auxiliar a remover objetos mortos.
    // Porém, dando uma olhada por cima, talvez não seja necessária
    // (pode remover os elementos na percorrer() da lista entidades com base no atributo 'morto')
    // MAS, por via das dúvidas, manterei ela aqui por hora
    template<class TL>
    void Lista<TL>::remover(TL* elemento) {


        
        /*Elemento* pAtual = pPrimeiro;
        Elemento* pAnterior = nullptr;

        while (pAtual->getInfo() != elemento &&
            pAtual != nullptr) {
            pAnterior = pAtual;
            pAtual = pAtual->getProx();
        }
        if (pAtual->getInfo() == elemento) {
            pAnterior->setProx(pAtual->getProx());
            if (pAtual->dinamico)
                delete pAtual->getInfo();
            delete pAtual;
        }*/
                Elemento* pAtual = pPrimeiro;
        Elemento* pAnterior = nullptr;

        while (pAtual != nullptr && pAtual->getInfo() != elemento) {
            pAnterior = pAtual;
            pAtual = pAtual->getProx();
        }

        // CORRIGIDO: sai sem crash se não encontrou
        if (pAtual == nullptr) return;

        // CORRIGIDO: trata remoção do primeiro elemento
        // versão antiga sempre chamava pAnterior->setProx sem checar nullptr
        if (pAnterior == nullptr)
            pPrimeiro = pAtual->getProx();
        else
            pAnterior->setProx(pAtual->getProx());

        // CORRIGIDO: atualiza pUltimo se removeu o último elemento
        if (pAtual == pUltimo)
            pUltimo = pAnterior;

        // CORRIGIDO: destrutor de Elemento já deleta pInfo se dinamico == true
        // versão antiga deletava aqui E no destrutor — double free
        delete pAtual;
    
    }
}