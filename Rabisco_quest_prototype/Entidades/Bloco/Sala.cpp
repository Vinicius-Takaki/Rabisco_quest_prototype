#include "Sala.h"
#include <algorithm>
#include "../../Gerenciadores/GerenciadorTexturas.h"
#include <cmath> 
using namespace std;

namespace Principal {
    // Construtora com parâmetro
    Sala::Sala(int alturaFornecida, int larguraFornecida)
        : altura(alturaFornecida), largura(larguraFornecida) {
        area.setPosition(sf::Vector2f(0.f, 0.f));
        area.setSize(sf::Vector2f(static_cast<float>(largura), static_cast<float>(altura))); // CORRIGIDO: cast explícito int->float
        area.setFillColor(sf::Color(100, 100, 100));
    }

    // Construtora sem parâmetro
    Sala::Sala() : altura(100), largura(100) {
        area.setPosition(sf::Vector2f(0.f, 0.f));
        area.setSize(sf::Vector2f(static_cast<float>(largura), static_cast<float>(altura))); // CORRIGIDO: cast explícito int->float
        area.setFillColor(sf::Color(100, 100, 100));
    }

    Sala::~Sala() {
    }
    void Sala::setTexturaFundo(const std::string& caminho) {
        sf::Texture* tex = GerenciadorTexturas::getInstancia().obterTextura(caminho);
        if (!tex) {
            temFundo = false;
            return;
        }

        tex->setRepeated(true);
        fundoSprite.setTexture(*tex, true);

        // Largura da imagem já escalada
        sf::Vector2u tamTex = tex->getSize();
        if (tamTex.x == 0 || tamTex.y == 0) {
            temFundo = false;
            return;
        }


        float escala = static_cast<float>(altura) / tamTex.y;
        float larguraEscalada = tamTex.x * escala;

        int repeticoesX = static_cast<int>(std::ceil(largura / larguraEscalada)) + 1;

        fundoSprite.setTextureRect(sf::IntRect(0, 0, tamTex.x * repeticoesX, tamTex.y));
        fundoSprite.setScale(escala, escala);
        fundoSprite.setPosition(0.f, 0.f);

        temFundo = true;
    }

    // Empurra entidade para dentro da sala
    void Sala::limitar(Entidade* ent) {
        sf::FloatRect areaEnt = ent->getCorpo().getGlobalBounds();
        sf::FloatRect areaSala = area.getGlobalBounds();

        // Confere a margem de não-colisão e anula negativos
        float erroEsquerda = max(0.f, areaSala.left - areaEnt.left);
        float erroCima = max(0.f, areaSala.top - areaEnt.top);
        float erroDireita = max(0.f, (areaEnt.left + areaEnt.width) - (areaSala.left + areaSala.width));
        float erroBaixo = max(0.f, (areaEnt.top + areaEnt.height) - (areaSala.top + areaSala.height));

        // Determina se a entidade está fora da sala
        bool erro = (erroBaixo || erroCima || erroDireita || erroEsquerda);

        // Corrige a posição da entidade e aterrissa ela caso esteja no chao
        if (erro) {
            ent->setPosition(sf::Vector2f(areaEnt.left + (erroEsquerda - erroDireita),
                areaEnt.top + (erroCima - erroBaixo)));

            if (erroBaixo)
                ent->pousar();

        }
    }

    void Sala::desenhar(sf::RenderWindow& window) {
        if (temFundo) {
            // Desenhar o fundo fixo na tela (sem seguir a camera)
            const sf::Texture* tex = fundoSprite.getTexture();
            if (tex) {
                // salvar view atual
                sf::View viewAtual = window.getView();
                // usar view padrao (coordenadas da tela)
                window.setView(window.getDefaultView());

                // ajustar escala do sprite para cobrir a janela
                sf::Vector2u tamJanela = window.getSize();
                sf::Vector2u tamTex = tex->getSize();
                if (tamTex.x > 0 && tamTex.y > 0) {
                    // garantir que usamos a area inteira da textura
                    fundoSprite.setTextureRect(sf::IntRect(0, 0, tamTex.x, tamTex.y));
                    fundoSprite.setScale(static_cast<float>(tamJanela.x) / static_cast<float>(tamTex.x),
                        static_cast<float>(tamJanela.y) / static_cast<float>(tamTex.y));
                }
                fundoSprite.setPosition(0.f, 0.f);
                window.draw(fundoSprite);

                // restaurar view anterior (camera)
                window.setView(viewAtual);
                return;
            }
        }

        window.draw(area);
    }
}
