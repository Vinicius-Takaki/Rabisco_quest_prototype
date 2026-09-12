#include "GerenciadorTexturas.h"
#include <iostream>
#include <filesystem>

namespace Principal {
    GerenciadorTexturas* GerenciadorTexturas::pInstancia = nullptr;

    GerenciadorTexturas& GerenciadorTexturas::getInstancia() {
        if (!pInstancia)
            pInstancia = new GerenciadorTexturas();
        return *pInstancia;
    }

    sf::Texture* GerenciadorTexturas::obterTextura(const std::string& caminho) {
        auto it = texturas.find(caminho);
        if (it != texturas.end())
            return &it->second;

        sf::Texture nova;
        if (!nova.loadFromFile(caminho)) {
            std::cerr << "Aviso: nao foi possivel carregar '" << caminho << "'." << std::endl;
            try {
                namespace fs = std::filesystem;
                fs::path p(caminho);
                std::cerr << "  Working dir: " << fs::current_path() << std::endl;
                std::cerr << "  Caminho fornecido existe? " << (fs::exists(p) ? "sim" : "nao") << std::endl;
                std::error_code ec;
                auto abs = fs::absolute(p, ec);
                if (!ec)
                    std::cerr << "  Caminho absoluto: " << abs << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "  Erro ao inspecionar filesystem: " << e.what() << std::endl;
            }
            return nullptr;
        }

        auto resultado = texturas.emplace(caminho, std::move(nova));
        return &resultado.first->second;
    }
}