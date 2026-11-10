# Plants vs. Zombies — Projeto em C++

Implementação acadêmica de um jogo inspirado em **Plants vs. Zombies**, desenvolvida em **C++** com princípios de **programação orientada a objetos (POO)**. O projeto inclui uma versão no terminal e uma interface gráfica construída com **SFML 3**.

## Funcionalidades

- Tabuleiro com **3 linhas e 7 colunas**.
- **5 plantas**: Sunflower, Peashooter, Wall-Nut, Potato Mine e Cabbage-Pult.
- **3 tipos de zumbis**: Normal, Conehead e Gargantuar.
- Sistema de sóis para comprar plantas.
- Projéteis de ervilha e repolho, combate e resistência das plantas.
- Cortadores de grama para defesa das linhas.
- Progressão de **10 waves**.
- Telas de vitória e derrota.
- Interface gráfica em janela de **1920 × 1080**, com área de jogo centralizada.

## Tecnologias

- **C++**
- **SFML 3** para a interface gráfica
- **Make** para compilação
- Conceitos de **POO**, como classes, herança e polimorfismo

## Estrutura do projeto

```text
T1-POO/
├── include/               # Arquivos de cabeçalho
│   ├── enum/
│   ├── game/
│   ├── plants/
│   ├── projectiles/
│   └── zombies/
├── src/                   # Implementações em C++
│   ├── game/
│   ├── plants/
│   ├── projectiles/
│   ├── zombies/
│   ├── graphics_test.cpp  # Interface gráfica
│   └── main.cpp           # Entrada da versão de terminal
├── Makefile
└── .gitignore
```

## Como executar

### Pré-requisitos

- Compilador C++ compatível com o projeto
- `make`
- **SFML 3** instalada e disponível para compilação e vinculação

No terminal, entre na pasta `T1-POO`:

```bash
cd T1-POO
```

Compile a versão gráfica:

```bash
make graphics
```

Execute:

```bash
./pvz_graphics
```

> Os comandos foram utilizados em ambiente Linux/WSL. Para outros sistemas, pode ser necessário adaptar a instalação da SFML e o Makefile.

## Controles

| Ação | Controle |
| --- | --- |
| Selecionar uma planta | Teclas **1 a 5** ou clique na carta |
| Plantar | Clique esquerdo em uma célula vazia do tabuleiro |
| Sair | **Esc** |

**Ordem das plantas:** 1. Sunflower; 2. Peashooter; 3. Wall-Nut; 4. Potato Mine; 5. Cabbage-Pult.

## Objetivo

Defender as três linhas do tabuleiro, utilizando os sóis disponíveis para posicionar plantas e impedir o avanço dos zumbis ao longo das dez waves.

## Sobre o projeto

Projeto de estudo de **programação orientada a objetos**, com separação entre a lógica do jogo (tabuleiro, plantas, zumbis e projéteis) e sua representação gráfica.

> Projeto acadêmico inspirado em *Plants vs. Zombies*, sem afiliação com os titulares da franquia original.
