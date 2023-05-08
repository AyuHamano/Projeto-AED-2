# Projeto-AED-2 

Além de uma aplicação sobre árvores binárias de busca balanceadas, os algoritmos básicos de árvores binárias de busca e de um tipo de árvore de busca balanceada (AVL, RB, B, etc) deve ser implementados nesse projeto


## O trabalho deve ser dividido em duas partes: 

1 . A primeira parte consiste na implementação da Árvore Binária de Busca e de sua variação balanceada. 

2 . A segunda parte deverá ser implementada a  aplicação e pelo menos 10000 casos de teste devem ser usados para uso da estrutura de dados implementada, mostrando como ela pode ser utilizada para melhorar o desempenho de operações de busca, inserção e remoção de dados na aplicação.


## Compilação

Para compilar o projeto basta compilar o arquivo `grafo.cpp`. Você pode utilizar
o seu compilador de preferência, porém o GNU C Compiler é recomendado (GCC).


**Para instalar o GCC em uma máquina Windows opte por instalar pelo [MSYS2](https://www.msys2.org/).**

```bash
g++ -o grafo grafo.cpp
```

Adicionalmente é indicado adicionar opções para desenvolvimento:
- `-g3`: adiciona marcas de debug no arquivo compilado. Útil para ter
    informações de linha que deram algum bug. E para ter suporte completo para
    debugadores
- `-Wall`: gera avisos para possíveis bugs e melhorias de código
- `-Wextra`: adiciona ainda mais avisos úteis
- `-fsanitize=address,undefined`: Melhora mensagens de erro e descobre problemas
    relacionados a memória e comportamentos indefinidos
- `--std=c++11`: define versão do C++ a ser compilado, C++11 (versão de 2011) é
    uma versão estável e suportada na maioria dos computadores.

Adicionando todas as flags o comando para compilação ficaria:
```bash
g++ -g3 -Wall -Wextra -fsanitize=address,undefined --std=c++11 -o grafo grafo.cpp
```

### Makefile

Receitas para GNU Make estão disponíveis no arquivo Makefile. A ferramenta Make
auxilia a manter os comandos consistentes entre o time. Você pode dar uma olhada
nas receitas no próprio arquivo Makefile que está comentado.

As receitas disponíveis são:

- `make grafo`: Ao executar esse comando no terminal o arquivo `grafo.cpp` será
    compilado para o arquivo `grafo`
- `make executar`: Compila o arquivo grafo e executa este
- `make clean`: Remove arquivos compilados do projeto (limpar)
