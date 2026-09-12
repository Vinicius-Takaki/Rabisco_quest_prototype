# Rabisco Quest

Um jogo de plataforma 2D em C++ com SFML, feito para consolidar os conceitos aprendidos em aula.

## Sobre o jogo

Rabisco Quest é um platformer clássico bem simples: corra, pule, desvie de armadilhas e lama, e derrote inimigos pisando neles. O jogo tem duas fases com temas, inimigos e cenários diferentes, terminando com uma tela de vitória ao concluir a fase final.

## Controles

| Tecla | Ação |
|---|---|
| `A` | Mover para a esquerda |
| `D` | Mover para a direita |
| `W` | Pular (só funciona no chão) |
| `Esc` | Fechar o jogo |

## Fases

### Fase 1
- **Inimigos:** Rato (perseguidor simples) e Sapo (persegue e pula periodicamente)
- **Obstáculos:** Plataformas e Lama (reduz a velocidade do jogador ao encostar)
- **Cenário:** tema de floresta

### Fase 2
- **Inimigos:** Rato e Slime (persegue e atira projéteis à distância)
- **Obstáculos:** Plataformas e Armadilhas (causam dano ao encostar)
- **Cenário:** tema de montanha/gelo
- Ao alcançar o final da fase, o jogo exibe uma tela de vitória e encerra

## Mecânicas principais

- **Pulo em inimigos:** pisar na cabeça de um inimigo o derrota e concede pontos; encostar de lado ou por baixo causa dano ao jogador
- **Sistema de vidas:** o jogador tem vidas limitadas, exibidas como corações na tela; perder todas as vidas encerra a partida
- **Zona seguraa:** os primeiros metros de cada fase não geram inimigos nem obstáculos, dando um espaço inicial livre de perigo
- **Câmera dinâmica:** a câmera segue o jogador horizontalmente, respeitando os limites da fase

## Arquitetura do projeto

O jogo segue uma estrutura orientada a objetos organizada em torno de algumas classes-chave:

```
Ente (classe base abstrata)
 └── Entidade (posição, sprite, gravidade, vida)
      ├── Personagem
      │    ├── Jogador
      │    └── Inimigo
      │         ├── Rato
      │         ├── Sapo
      │         └── Slime
      └── Obstaculo
           ├── Plataforma
           ├── Lama
           └── Armadilha

Fase (classe base abstrata)
 ├── FasePrimeira
 └── FaseSegunda

Jogo (orquestra fases, câmera e janela)
```

### Gerenciadores

- **GerenciadorGrafico:** encapsula a janela SFML (padrão singleton)
- **GerenciadorColisao:** detecta e resolve colisões entre jogador, inimigos, obstáculos e projéteis
- **GerenciadorTexturas:** cache de texturas para evitar carregar a mesma imagem várias vezes

### Estruturas de dados

- **Lista\<T\>:** lista encadeada genérica implementada manualmente, usada para armazenar entidades
- **ListaEntidades:** encapsula a `Lista<Entidade>` com operações de alto nível (percorrer, desenhar, limpar mortos)

## Conceitos de programação orientada a objetos utilizados

- **Herança:** hierarquia `Ente → Entidade → Personagem/Obstaculo → classes específicas` (Jogador, Rato, Sapo, Slime, Plataforma, Lama, Armadilha), reaproveitando comportamento comum de posição, gravidade e sprite
- **Polimorfismo:** métodos `virtual` como `obstacularizar()`, `danificar()` e `getTexturaChao()` fazem cada classe reagir de um jeito diferente ao mesmo chamado
- **Classes abstratas:** `Ente`, `Entidade`, `Personagem`, `Inimigo`, `Obstaculo` e `Fase` têm métodos puros (`= 0`), forçando as classes filhas a implementá-los
- **Encapsulamento:** atributos como `corpo` e `vel` são privados/protegidos, acessados só por getters/setters
- **Singleton:** `GerenciadorGrafico` e `GerenciadorTexturas` garantem uma única instância global (uma janela, um cache de texturas)
- **Templates:** `Lista<TL>` é uma lista encadeada genérica, reaproveitável para qualquer tipo
- **Composição:** `Fase` tem uma `Sala` e um `GerenciadorColisao`; `Jogo` tem as fases e os jogadores
- **Gerenciamento manual de memória:** uso de `new`/`delete` com cuidado para evitar *dangling pointers* e *double-free*

## Tecnologias

- **Linguagem:** C++
- **Biblioteca gráfica:** [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
- **IDE:** Visual Studio

## Como compilar e rodar

1. Instale o [SFML](https://www.sfml-dev.org/download.php) compatível com sua versão do Visual Studio
2. Abra o arquivo `.sln` no Visual Studio
3. Configure o **Diretório de Trabalho** do projeto para `$(ProjectDir)` (Propriedades → Depuração), garantindo que as pastas `Sprites/` e `assets/` sejam encontradas corretamente
4. Compile em modo **Debug** ou **Release** (`Ctrl+Shift+B`)
5. Rode com `F5` ou `Ctrl+F5`

### Alternativa: compilando pelo VS Code

O projeto também pode ser compilado fora do Visual Studio, usando VS Code com MinGW (g++):

1. Instale o [MinGW-w64](https://www.mingw-w64.org/) e adicione a pasta `bin` ao `PATH` do sistema
2. No VS Code, instale a extensão **C/C++** (da Microsoft)
3. Baixe a versão do SFML compatível com MinGW (não a versão para Visual Studio) em [sfml-dev.org/download](https://www.sfml-dev.org/download.php)
4. Crie um arquivo `.vscode/tasks.json` configurando a task de build com g++, incluindo:
   - `-I<caminho>/SFML/include` (diretório de include)
   - `-L<caminho>/SFML/lib` (diretório de biblioteca)
   - `-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio` (bibliotecas a linkar)
5. Copie as DLLs do SFML (`SFML/bin`) para a pasta onde o executável será gerado
6. Compile com `Ctrl+Shift+B` e rode o executável gerado a partir do terminal, garantindo que o diretório de trabalho seja a raiz do projeto (onde está a pasta `Sprites/`)

> **Observação:** a pasta `SFML-2.6.2/` incluída neste repositório foi compilada para uso com Visual Studio (MSVC). Para compilar com MinGW/g++, é necessário baixar separadamente a versão do SFML correspondente ao MinGW, pois os binários não são compatíveis entre os dois compiladores.

## Demonstração
Clique aqui: https://youtu.be/3sLKRqhc8mM


<img width="1920" height="1080" alt="Base Profile Screenshot 2026 09 12 - 18 23 08 90" src="https://github.com/user-attachments/assets/cf782207-993c-4e52-a062-6b55a9770713" />


## Status do projeto

Este é um projeto em desenvolvimento contínuo, originado de um trabalho acadêmico de programação orientada a objetos. Algumas áreas seguem em evolução:

- [ ] Suporte a segundo jogador (estrutura já prevista em `Jogador`/`Fase`, mas não totalmente integrada)
- [ ] Tela de menu inicial
- [ ] Sistema de salvar/carregar progresso
- [ ] Ajuste fino de balanceamento (dificuldade, quantidade de inimigos)
- [ ] Suporte a tela cheia com proporção adaptável

## Créditos

Projeto desenvolvido como exercício de programação orientada a objetos em C++, utilizando a biblioteca [SFML](https://www.sfml-dev.org/).

Alguns assets visuais (sprites e/ou elementos gráficos) utilizados neste projeto têm como referência ou origem os pacotes gratuitos disponibilizados por [Kenney (kenney.nl)](https://www.kenney.nl), sob licença CC0.

