
# Comando usado como compilador, estamos usando GCC para C++
CC := g++

# Flags de compilação
# -g3: gera informações de debug
# -Wall: mostra todos os avisos
# -Wextra: mostra mais avisos
# -fsanitize=address,undefined: checa por erros de memória e undefined behavior
# -std=c++11: usa o padrão C++11
CFLAGS := -g3 -Wall -Wextra -fsanitize=address,undefined -std=c++11


# ---
# Receitas: Comandos para compilar arquivos rode como `make grafo`
# ---

# Receita para executar o arquivo grafo
# Depende do arquivo grafo ser compilado
.PHONY: executar
executar: grafo
	./grafo

# Receita para compilar o arquivo grafo
# Depende do arquivo grafo.cpp, qualquer alteração no arquivo fará ele ser recompilado
grafo: grafo.cpp
	$(CC) $(CFLAGS) -o grafo grafo.cpp


# Receita para limpar os arquivos gerados
.PHONY: clean
clean:
	rm -f grafo
