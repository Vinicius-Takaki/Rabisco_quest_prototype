#pragma once
#include "Obstaculo.h"

namespace Principal {
    class Plataforma : public Obstaculo {
    public:
        // construtor para criar plataforma em posição específica, com largura e altura definidas (altura valor a definir)
        Plataforma(float x, float y, float largura, float altura); 
        ~Plataforma();

        void executar(); //não sei o que pode ser executado em uma plataforma
        void obstacularizar(Jogador* p);
        void obstacularizar(Entidade* p); // versão genérica para lidar com outros tipos de entidades
        void salvar();
    };
}

