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
    this->altura = -1; //a implementar
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

enum tipoOrdenacao {
  titulo,
  codigo
};

class Arvore {
public:
  NoArvore *raiz = nullptr;

  tipoOrdenacao ordenacao;

  ~Arvore() { delete raiz; }

  Arvore(tipoOrdenacao ordenacao) {
    this->ordenacao;
  }

  Livro *buscaPorTitulo(string titulo) {
    return buscaPorTitulo(titulo, raiz);
  }

  Livro *buscaPorTitulo(string titulo, NoArvore *no) {
    if (no == nullptr) {
      return nullptr;
    }

    int compararTitulos = no->valor->titulo.compare(titulo);

    if (compararTitulos == 0) {
      return no->valor;
    }

    Livro *livroEsq = buscaPorTitulo(titulo, no->filhoEsquerda);
    if (livroEsq != nullptr) {
      return livroEsq;
    }

    Livro *livroDir = buscaPorTitulo(titulo, no->filhoDireita);
    if (livroDir != nullptr) {
      return livroDir;
    }

    return nullptr;
  }

  Livro *buscaPorCodigo(int codigo) {
    return buscaPorCodigo(codigo, raiz);
  }

  Livro *buscaPorCodigo(int codigo, NoArvore *no) {
    if (no == nullptr) {
      return nullptr;
    }

    if (codigo == no->valor->codigo) {
      return no->valor;
    } else if (codigo < no->valor->codigo) {
      return buscaPorCodigo(codigo, no->filhoEsquerda);
    } else {
      return buscaPorCodigo(codigo, no->filhoDireita);
    }
  }

  int comparaOrd (NoArvore *a, Livro *b) {
    if(ordenacao == tipoOrdenacao :: codigo) {
      return a->valor->codigo - b->codigo;
    }
    else {
      return a->valor->titulo.compare(b->titulo);
    }
  }


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
    //calcula a altura do no
    no->altura = maiorAltura(alturaNo(raiz->filhoEsquerda), alturaNo(raiz->filhoDireita)) + 1;
    no = balancearNo(no);
  }

  void inserirDireita(NoArvore *no, Livro *valor) {
    if(no->filhoDireita == NULL) { 
        no->filhoDireita = new NoArvore(valor);
    }
    else {
      inserirDireita(no->filhoDireita, valor);
    }
    //calcula a altura do no
    no->altura = maiorAltura(alturaNo(raiz->filhoEsquerda), alturaNo(raiz->filhoDireita)) + 1;
    no = balancearNo(no);
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
  short bal = calculaAlturaNo(no);

  if(bal < -1 && calculaFatorBalanceado(no->filhoDireita) <=0) { no = rotacaoEsquerda(no); }

  else if(bal < -1 && calculaFatorBalanceado(no->filhoDireita) > 0) { no = rotacaoDireitaEsquerda(no); }

  else if(bal > 1 && calculaFatorBalanceado(no->filhoEsquerda) >=0) { no = rotacaoDireita(no); }

  else if(bal > 1 && calculaFatorBalanceado(no->filhoEsquerda) < 0) { no = rotacaoEsquerdaDireita(no); }

  return no;

}

/*Funcao de Altura*/

  /*retona a altura do no*/
  short alturaNo(NoArvore *no) {
    if(no == NULL){
        return -1;
    }
    else{
        return no->altura;
    }
  }

  short maiorAltura(short altura1, short altura2) {
    if(altura1 > altura2) { return altura1; }

    else { return altura2; }
  }

  short calculaAlturaNo(NoArvore *no) {
    if(no == NULL){
        return -1;
    }
    else{
        int esq = alturaNo(no->filhoEsquerda);
        int dir = alturaNo(no->filhoDireita);

        if(esq > dir) { return esq + 1; }
        else {return dir + 1;}
    }
  }


  /**********************Funcoes de rotacoes (a implementar)**************************/
  /*explicação sobre balanceamento: https://www.youtube.com/watch?v=oIp82CfCDoQ */

  
  NoArvore* rotacaoDireita(NoArvore *no) {//direita direita(DD)
    NoArvore *aux1, *aux2;

    aux1 = no->filhoEsquerda;
    aux2 = aux1->filhoDireita;

    aux1->filhoDireita = no;
    no->filhoEsquerda = aux2; 

    no->altura = maiorAltura(alturaNo(no->filhoEsquerda), alturaNo(no->filhoDireita)) + 1;
    aux1->altura = maiorAltura(alturaNo(aux1->filhoEsquerda), alturaNo(aux1->filhoDireita)) + 1;

    return aux1;
  }
  NoArvore* rotacaoEsquerda(NoArvore *no) { //esquerda esquerda(EE)
    NoArvore *aux1, *aux2;

    aux1 = no->filhoDireita;
    aux2 = aux1->filhoEsquerda;

    aux1->filhoEsquerda = no;
    no->filhoDireita = aux2;

    no->altura = maiorAltura(alturaNo(no->filhoEsquerda), alturaNo(no->filhoDireita)) + 1;
    aux1->altura = maiorAltura(alturaNo(aux1->filhoEsquerda), alturaNo(aux1->filhoDireita)) + 1;
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
  Arvore arvoreTitulo(tipoOrdenacao :: titulo); //arvore do titulo 
  Arvore arvoreCodigo(tipoOrdenacao :: codigo); //arvore por codigo
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
