#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace Principal {
    class GerenciadorTexturas {
    private:
        static GerenciadorTexturas* pInstancia;
        std::map<std::string, sf::Texture> texturas;

        GerenciadorTexturas() {}

    public:
        static GerenciadorTexturas& getInstancia();
        sf::Texture* obterTextura(const std::string& caminho);
    };
}