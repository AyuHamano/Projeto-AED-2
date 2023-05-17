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

  /** Altura do no */
  short altura;

  NoArvore(Livro *valor) { 
    this->valor = valor;   
    this->altura = 1; //a implementar
  }

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


/******************* funcao de adicionar um elemento nas arvores ******************************/
  void adicionar(Livro *valor) {
    if(raiz==NULL) {
      raiz = new NoArvore(valor);
    }
    else {
      inserirCodigo(raiz, valor);
    }
  }

  /*Insere ordenando pelo codigo*/
  void inserirCodigo(NoArvore *raiz, Livro *valor) {

    //esquerda 
    if(valor->codigo < raiz->valor->codigo) {
      if(raiz->filhoEsquerda == NULL) { 
          raiz->filhoEsquerda = new NoArvore(valor);
      }
      else {
		    inserirCodigo(raiz->filhoEsquerda, valor);
      }
		}
    //direita
    if(valor->codigo > raiz->valor->codigo) {
      if(raiz->filhoDireita == NULL) { 
          raiz->filhoDireita = new NoArvore(valor);
      }
      else {
		    inserirCodigo(raiz->filhoDireita, valor);
      }
    }
    //raiz->altura = maior(alturaNo(raiz->filhoEsquerda), alturaNo(raiz->filhoDireita)) + 1;
    atualizaAltura(raiz);
    raiz = balancearNo(raiz);
  }
/*************************************************************************/

/*Funcao de balanceamento*/
short calculaFatorBalanceado(NoArvore *no) {
  if(no) {
    return (alturaNo(no->filhoEsquerda) - alturaNo(no->filhoDireita));
  }
  else return 0;
}

NoArvore* balancearNo(NoArvore *no) {
  short bal = calculaFatorBalanceado(raiz);

  if(bal < -1 && calculaFatorBalanceado(raiz->filhoDireita) <=0) { raiz = rotacaoEsquerda(raiz); }

  else if(bal < -1 && calculaFatorBalanceado(raiz->filhoDireita) > 0) { raiz = rotacaoDireitaEsquerda(raiz); }

  else if(bal > 1 && calculaFatorBalanceado(raiz->filhoEsquerda) >=0) { raiz = rotacaoDireita(raiz); }

  else if(bal > 1 && calculaFatorBalanceado(raiz->filhoEsquerda) < 0) { raiz = rotacaoEsquerdaDireita(raiz); }

  return raiz;

}

/*Funcao de Altura*/

  /*retona a altura do no*/
  short alturaNo(NoArvore *no) {

    if(no == NULL) return 0;
    
    else return no->altura;
    
  }
  void atualizaAltura(NoArvore *no) {
    short alturaEsquerda = alturaNo(no->filhoEsquerda);
    short alturaDireita = alturaNo(no->filhoDireita);
    no->altura = maior(alturaEsquerda, alturaDireita) + 1;
  }

  short maior(short a, short b) {
    return (a > b)? a : b; //'a' é maior do que 'b'? se sim retorne 'a', senão retorne 'b'
  } 

  /**********************Funcoes de rotacoes (a implementar)**************************/
  /*explicação sobre balanceamento: https://www.youtube.com/watch?v=oIp82CfCDoQ */

  
  
  NoArvore* rotacaoDireita(NoArvore *no) {//direita direita(DD)
    NoArvore *aux1, *aux2;

    aux1 = no->filhoEsquerda;
    aux2 = aux1->filhoDireita;

    aux1->filhoDireita = no;
    no->filhoEsquerda = aux2; 

    //no->altura = maior(alturaNo(no->filhoEsquerda), alturaNo(no->filhoDireita)) + 1;
    //aux1->altura = maior(alturaNo(aux1->filhoEsquerda), alturaNo(aux1->filhoDireita)) + 1;
    atualizaAltura(no);
    atualizaAltura(aux1);

    return aux1;
  }
  NoArvore* rotacaoEsquerda(NoArvore *no) { //esquerda esquerda(EE)
    NoArvore *aux1, *aux2;

    aux1 = no->filhoDireita;
    aux2 = aux1->filhoEsquerda;

    aux1->filhoEsquerda = no;
    no->filhoDireita = aux2;

    //no->altura = maior(alturaNo(no->filhoEsquerda), alturaNo(no->filhoDireita)) + 1;
    //aux1->altura = maior(alturaNo(aux1->filhoEsquerda), alturaNo(aux1->filhoDireita)) + 1;
    atualizaAltura(no);
    atualizaAltura(aux1);
    return aux1;
  }

  NoArvore* rotacaoEsquerdaDireita(NoArvore* no) {//esquerda direita(ED)
    no->filhoEsquerda = rotacaoEsquerda(no->filhoEsquerda);
    return rotacaoDireita(no);
  }

  NoArvore* rotacaoDireitaEsquerda(NoArvore* no) {//diereita esquerda(DE)
    no->filhoDireita = rotacaoDireita(no->filhoDireita);
    return rotacaoEsquerdaDireita(no);
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
  Arvore arvore; //arvore do titulo 

  arvore.adicionar(new Livro("O Senhor dos Anéis", "J. R. R. Tolkien", 1));

  arvore.adicionar(new Livro("O Hobbit", "J. R. R. Tolkien", 2));

  arvore.adicionar(new Livro("O Silmarillion", "J. R. R. Tolkien", 3));

  arvore.adicionar(new Livro("O escaravelho de ouro", "Edgar Allan Poe", 4));

  arvore.adicionar(new Livro("O Guia do Mochileiro das Galáxias", "Douglas Adams", 5));

  arvore.adicionar(new Livro("Metamorfose", "Franz Kafka", 6)); 
  arvore.imprimir();

  return 0;
}
