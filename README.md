# Jogo da Cobrinha em C

Este é um jogo da cobrinha desenvolvido em C para rodar no terminal do Windows. O objetivo é controlar a cobrinha e comer o máximo de "comidas" possível sem bater nas paredes ou em si mesma.

## Captura de Tela

![Demonstração do Jogo](Jogo-da-cobrinha-em-C/jogo.mp4)

## Funcionalidades
- Movimentação da cobrinha com as teclas `W`, `A`, `S`, `D`
- Geração aleatória de comida
- Crescimento da cobrinha ao comer
- Aumento progressivo da velocidade
- Detecção de colisões (parede e corpo)
- Exibição da pontuação

## Requisitos
- Compilador de C (ex: `GCC` ou `MinGW`)
- Sistema operacional Windows (necessário devido ao uso de `windows.h` e `SetConsoleCursorPosition`)

## Como Compilar e Executar

1. Clone este repositório:
   ```bash
   git clone https://github.com/AndreCA1/Jogo-da-cobrinha-em-C
   ```
2. Navegue até o diretório do projeto:
   ```bash
   cd Jogo-da-cobrinha-em-C
   ```
3. Compile o programa:
   ```bash
   gcc Jogo_Da_Cobrinha.cpp -o snake.exe
   ```
4. Execute o jogo:
   ```bash
   ./snake.exe
   ```

## Controles
- `W` - Mover para cima
- `A` - Mover para a esquerda
- `S` - Mover para baixo
- `D` - Mover para a direita

## Estrutura do Código
O código está estruturado em diferentes funções para modularidade:
- `cursor(int x, int y)`: Move o cursor para a posição desejada no terminal.
- `desenha()`: Desenha a cobrinha na tela.
- `atualizaposicao()`: Atualiza a posição da cobrinha a cada movimento.
- `desenhacomida()`: Gera uma nova comida aleatoriamente no mapa.
- `Verifica()`: Checa se a cobrinha colidiu consigo mesma.
- `mostrapontos(int pontos)`: Exibe a pontuação atual do jogador.
- `comeucomida(int cordx, int cordy)`: Verifica se a cobrinha comeu a comida e aumenta o tamanho.

## Melhorias Futuras
- Adição de um sistema de menu inicial
- Implementação de diferentes níveis de dificuldade
- Salvamento de recordes

## Autor
- **Andre Carvalho**

Sinta-se à vontade para contribuir com melhorias ou abrir issues caso encontre bugs!

---
