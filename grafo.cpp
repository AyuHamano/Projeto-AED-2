#include <iomanip>
#include <iostream>

/**
 * Classe que representa o nó de uma árvore. Cada nó possui um valor e dois
 * ponteiros para os filhos esquerdo e direito.
 */
class NoArvore {
public:
  /** Valor para esse nó */
  int valor;

  /** Ponteiro para o filho esquerdo */
  NoArvore *filhoEsquerda = nullptr;

  /** Ponteiro para o filho direito */
  NoArvore *filhoDireita = nullptr;

  NoArvore(int valor) { this->valor = valor; }

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
  }

  /**
   * Imprime a árvore em ordem. Primeiro filhos a direita, depois o valor
   * desse nó, e depois os filhos a esquerda.
   */
  void imprimir(int indent = 0) {
    if (filhoDireita) {
      filhoDireita->imprimir(indent + 4);
    }

    std::cout << std::setw(indent) << valor << std::endl;

    if (filhoEsquerda) {
      filhoEsquerda->imprimir(indent + 4);
    }
  }
};

class Arvore {
public:
  NoArvore *raiz = nullptr;

  ~Arvore() { delete raiz; }

  void adicionar(int valor) {
    // Para implementar
  }

  void remover(int valor) {
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

  arvore.raiz = new NoArvore(10);
  arvore.raiz->filhoDireita = new NoArvore(20);
  arvore.raiz->filhoEsquerda = new NoArvore(5);

  arvore.imprimir();

  return 0;
}
