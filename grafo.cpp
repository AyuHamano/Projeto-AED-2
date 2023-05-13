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
  int altura;

  NoArvore(Livro *valor) { 
    this->valor = valor;   
    this->altura = 0; //a implementar
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
  void adicionar(Livro *valor, bool ordenacao) {
    if(raiz == nullptr) {
        raiz = new NoArvore(valor);
    }
    else {
      if(ordenacao) { inserirTitulo(raiz, valor); }
      else inserirCodigo(raiz, valor);
        
		}
  }
  /*Insere ordenando pelo titulo*/
	void inserirTitulo(NoArvore *no, Livro *valor) {

    if(valor->titulo < no->valor->titulo) {
      inserirEsquerda(no, valor);
    }
    else if(valor->titulo > no->valor->titulo) {
		  inserirDireita(no, valor);
		}
  }

  /*Insere ordenando pelo codigo*/
  void inserirCodigo(NoArvore *no, Livro *valor) {

    if(valor->codigo < no->valor->codigo) {
      inserirEsquerda(no, valor);
    }
    else if(valor->codigo > no->valor->codigo) {
		  inserirDireita(no, valor);
		}
  }

  void inserirEsquerda(NoArvore *no, Livro *valor) {
    if(no->filhoEsquerda == NULL) { 
        no->filhoEsquerda = new NoArvore(valor);
    }
    else {
      inserirEsquerda(no->filhoEsquerda, valor);
    }
  }

  void inserirDireita(NoArvore *no, Livro *valor) {
    if(no->filhoDireita == NULL) { 
        no->filhoDireita = new NoArvore(valor);
    }
    else {
      inserirDireita(no->filhoDireita, valor);
    }
  }
/*************************************************************************/

  /*Funcoes de Altura*/
  int alturaNo(NoArvore *raiz) {
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = alturaNo(raiz->filhoEsquerda);
        int dir = alturaNo(raiz->filhoDireita);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
  }


  /**********************Funcoes de rotacoes (a implementar)************************************/
  
  NoArvore* rotacao_DD(NoArvore* desb) {//direitadireita(DD)
        NoArvore* aux = desb->filhoEsquerda;
        desb->filhoEsquerda = aux->filhoDireita;
        aux->filhoDireita = desb;
        return aux;
    }
 NoArvore* rotacao_EE(NoArvore* desb) { //esquerdaesquerda(EE)
        NoArvore* aux = desb->filhoDireita;
        desb->filhoEsquerda = aux->filhoEsquerda;
        aux->filhoEsquerda = desb;
        return aux;
    }
    NoArvore* rotacao_ED(NoArvore* desb) {//esquerdadireita(ED)
        desb->filhoEsquerda = rotacao_EE(desb->filhoEsquerda);
        return rotacao_DD(desb);
    }

    NoArvore* rotacao_DE(NoArvore* desb) {//diereitaesquerda(DE)
        desb->filhoDireita = rotacao_DD(desb->filhoDireita);
        return rotacao_ED(desb);
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
  Arvore arvoreTitulo; //arvore do titulo 
  Arvore arvoreCodigo; //arvore por codigo
  bool codigo = false, titulo = true;

  arvoreTitulo.raiz =
      new NoArvore(new Livro("O Senhor dos Anéis", "J. R. R. Tolkien", 1));

  arvoreTitulo.raiz->filhoDireita =
      new NoArvore(new Livro("O Hobbit", "J. R. R. Tolkien", 2));

  arvoreTitulo.raiz->filhoDireita->filhoDireita =
      new NoArvore(new Livro("O Silmarillion", "J. R. R. Tolkien", 3));

  arvoreTitulo.raiz->filhoDireita->filhoEsquerda =
      new NoArvore(new Livro("O escaravelho de ouro", "Edgar Allan Poe", 4));

  arvoreTitulo.raiz->filhoEsquerda = new NoArvore(
      new Livro("O Guia do Mochileiro das Galáxias", "Douglas Adams", 5));

  //teste de adicionar livro nas duas arvores
  arvoreTitulo.adicionar(new Livro("Metamorfose", "Franz Kafka", 6), titulo); 
  arvoreCodigo.adicionar(new Livro("Metamorfose", "Franz Kafka", 6), codigo); 
  arvoreTitulo.imprimir();
  arvoreCodigo.imprimir();

  return 0;
}