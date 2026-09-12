# Rabisco Quest

Jogo de plataforma 2D desenvolvido em C++ com SFML.

## Sobre o jogo

O jogador percorre duas fases repletas de inimigos e obstáculos. O objetivo é chegar ao fim da fase 2 e coletar o diamante para vencer.

### Inimigos
- **Rato** — inimigo básico presente nas duas fases
- **Sapo** — inimigo médio exclusivo da fase 1
- **Slime** — chefão exclusivo da fase 2, arremessa projéteis

### Obstáculos
- **Plataforma** — superfície onde o jogador pode andar
- **Lama** — diminui a velocidade do jogador
- **Armadilha** — causa dano ao jogador ao ser acionada
- **Diamante** — objetivo final da fase 2

### Controles
| Tecla | Ação |
|-------|------|
| `A` | Mover para a esquerda |
| `D` | Mover para a direita |
| `W` | Pular |
| `Esc` | Sair do jogo |

## Dependências

- [SFML 2.6.x](https://www.sfml-dev.org/download.php)
- Visual Studio 2022

## Como rodar

1. Instale o SFML 2.6 — [download aqui](https://www.sfml-dev.org/download.php)
2. Clone o repositório:
   ```
   git clone https://github.com/lucash533/game-tecprog.git
   ```
3. Abra o arquivo `Rabisco_quest_prototype.vcxproj` no Visual Studio
4. Configure o projeto para apontar para sua instalação do SFML:
   - Clique com botão direito no projeto → **Propriedades**
   - **C/C++ → Diretórios de Inclusão Adicionais**: adicione `<caminho_do_sfml>/include`
   - **Vinculador → Diretórios de Biblioteca Adicionais**: adicione `<caminho_do_sfml>/lib`
5. Compile e execute (`F5`)

> As DLLs do SFML necessárias já estão incluídas no repositório.

## Estrutura do projeto

```
Rabisco_quest_prototype/
├── Entidades/
│   ├── Personagens/     # Jogador, inimigos (Rato, Sapo, Slime...)
│   ├── Obstaculos/      # Plataforma, Lama, Armadilha, Diamante
│   └── Bloco/           # Sala (background e limites da fase)
├── Fases/               # Fase, FasePrimeira, FaseSegunda
├── Gerenciadores/       # GerenciadorColisao, GerenciadorGrafico
├── Listas/              # Lista<T>, ListaEntidades
├── Sprites/             # Texturas e imagens do jogo
├── Ente.h / Ente.cpp    # Classe base de todas as entidades
├── Jogo.h / Jogo.cpp    # Loop principal do jogo
└── main.cpp             # Ponto de entrada
```


Desenvolvido por: Vinícius Takaki Rodrigues


