#include <iostream>
#include <string>
#include <cstring>
using std::string;

/**
 * Classe que representa um livro. Cada livro possui um título, um autor e
 * um código.
 */
class Livro {
public:
  string titulo;
  string autor;
  int codigo;

  /**
   * Construtor da classe. Recebe o título, o autor e o código do livro.
   */
  Livro(string titulo, string autor, int codigo) {
    this->titulo = titulo;
    this->autor = autor;
    this->codigo = codigo;
  }

  /**
   * Operador de conversão para string. Permite que um objeto da classe Livro
   * seja convertido para string implicitamente. Exemplo:
   *
   * Livro livro("O Senhor dos Anéis", "J. R. R. Tolkien", 1);
   * string str = livro;
   *
   * Ou, de forma implícita:
   *
   * std::cout << livro << std::endl;
   */
  operator string() const {
    return titulo + " - " + autor + " (" + std::to_string(codigo) + ")";
  }
};

/**
 * Classe que representa o nó de uma árvore. Cada nó possui um valor e dois
 * ponteiros para os filhos esquerdo e direito.
 */
class NoArvore {
public:
  /** Valor para esse nó */
  Livro *valor;

  /** Ponteiro para o filho esquerdo */
  NoArvore *filhoEsquerda = nullptr;

  /** Ponteiro para o filho direito */
  NoArvore *filhoDireita = nullptr;

  NoArvore(Livro *valor) { this->valor = valor; }

  /**
   * Destrutor recursivo. Chama o destrutor para os filhos esquerdo e
   * direito.
   *
   * O destrutor é chamado automaticamente pelo compilador quando o objeto
   * não é mais necessário (sai de escopo), ou quando é manualmente deletado.
   * Exemplo, usando o operador delete: `delete arvore;`
   */
  ~NoArvore() {
    delete filhoEsquerda;
    delete filhoDireita;
    delete valor;
  }

  /**
   * Imprime a árvore em ordem. Primeiro filhos a direita, depois o valor
   * desse nó, e depois os filhos a esquerda.
   */
  void imprimir(int indent = 0) {
    if (filhoDireita) {
      filhoDireita->imprimir(indent + 4);
    }

    std::cout << string(indent, ' ') << string(*valor) << std::endl;

    if (filhoEsquerda) {
      filhoEsquerda->imprimir(indent + 4);
    }
  }
};

class Arvore {
public:
  NoArvore *raiz = nullptr;

  ~Arvore() { delete raiz; }


  /**funcao de adicionar um elemento na arvore*/
  void adicionar(Livro *valor) {
    if(raiz == nullptr) {
        raiz = new NoArvore(valor);
    }
    else {
        inserirLivro(raiz, valor);
		}
  }
	
	void inserirLivro(NoArvore *no, Livro *valor) {

    //insere a esquerda
    if(valor->titulo < no->valor->titulo) {

      if(no->filhoEsquerda == NULL) { 
        no->filhoEsquerda = new NoArvore(valor);
      }
      else {
      inserirLivro(no->filhoEsquerda, valor);
      }
    }

    //insere a direita
    else if(valor->titulo > no->valor->titulo) {
		    
			if(no->filhoDireita == NULL) {
				no->filhoDireita = new NoArvore(valor);
			}
			else {
				inserirLivro(no->filhoDireita, valor);
			}
		}
  }
  /**************************************************************/

  void remover(Livro *valor) {
    // Para implementar
  }

  void imprimir() {
    if (raiz) {
      raiz->imprimir();
    }
  }
};

int main() {
  Arvore arvore;

  arvore.raiz =
      new NoArvore(new Livro("O Senhor dos Anéis", "J. R. R. Tolkien", 1));

  arvore.raiz->filhoDireita =
      new NoArvore(new Livro("O Hobbit", "J. R. R. Tolkien", 2));

  arvore.raiz->filhoDireita->filhoDireita =
      new NoArvore(new Livro("O Silmarillion", "J. R. R. Tolkien", 3));

  arvore.raiz->filhoDireita->filhoEsquerda =
      new NoArvore(new Livro("O escaravelho de ouro", "Edgar Allan Poe", 4));

  arvore.raiz->filhoEsquerda = new NoArvore(
      new Livro("O Guia do Mochileiro das Galáxias", "Douglas Adams", 5));

  //teste  adicionar
  arvore.adicionar(new Livro("Metamorfose", "Franz Kafka", 6)); //ficará à esquerda 
  arvore.imprimir();

  return 0;
}
