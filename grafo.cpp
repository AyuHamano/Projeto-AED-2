#include <cstring>
#include <iostream>
#include <string>

using std::string;
using namespace std;

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
   *  cout << livro <<  endl;
   */
  operator string() const {
    return " (" + to_string(codigo) + ") " + titulo + " - " + autor;
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
  int altura = 0;

  NoArvore(Livro *valor) {
    this->valor = valor;
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

    cout << string(indent, ' ') << string(*valor) << endl;

    if (filhoEsquerda) {
      filhoEsquerda->imprimir(indent + 4);
    }
  }
};

class Arvore {
public:
  NoArvore *raiz = nullptr;
  ~Arvore() { delete raiz; }

  //---- FUNÇÕES DA ÁRVORE - INSERIR, BALANCEAR, BUSCAR E REMOVER
  //---- ADIÇÃO DE UM LIVRO

  void adicionar(Livro *valor) {
    if (raiz == nullptr) {
      raiz = new NoArvore(valor);
    } else
      raiz = inserirLivro(raiz, valor);
  }

  NoArvore *inserirLivro(NoArvore *no, Livro *valor) {

    // esquerda
    if (valor->codigo < no->valor->codigo) {
      if (no->filhoEsquerda == nullptr) {
        no->filhoEsquerda = new NoArvore(valor);
      } else {
        no->filhoEsquerda = inserirLivro(no->filhoEsquerda, valor);
      }
    }
    // direita
    if (valor->codigo > no->valor->codigo) {
      if (no->filhoDireita == nullptr) {
        no->filhoDireita = new NoArvore(valor);
      } else {
        no->filhoDireita = inserirLivro(no->filhoDireita, valor);
      }
    }

    atualizaAltura(no);
    return balancearNo(no);
  }

  //---- ALTURA ----

  short alturaNo(NoArvore *no) {

    if (no == nullptr)
      return -1;

    else
      return no->altura;
  }
  // a testar
  void atualizaAltura(NoArvore *no) {
    short alturaEsquerda = alturaNo(no->filhoEsquerda);
    short alturaDireita = alturaNo(no->filhoDireita);
    no->altura = maior(alturaEsquerda, alturaDireita) + 1;
  }

  short maior(short a, short b) {
    return (a > b) ? a : b; //'a' é maior do que 'b'? se sim retorne 'a', senão
                            // retorne 'b'
  }

  //---- ROTAÇÃO ----

  NoArvore *rotacaoDireita(NoArvore *no) { // direita direita(DD)
    NoArvore *aux1, *aux2;

    aux1 = no->filhoEsquerda;
    aux2 = aux1->filhoDireita;

    aux1->filhoDireita = no;
    no->filhoEsquerda = aux2;

    atualizaAltura(no);
    atualizaAltura(aux1);

    return aux1;
  }
  NoArvore *rotacaoEsquerda(NoArvore *no) { // esquerda esquerda(EE)
    NoArvore *aux1, *aux2;

    aux1 = no->filhoDireita;
    aux2 = aux1->filhoEsquerda;

    aux1->filhoEsquerda = no;
    no->filhoDireita = aux2;

    atualizaAltura(no);
    atualizaAltura(aux1);
    return aux1;
  }

  NoArvore *rotacaoEsquerdaDireita(NoArvore *no) { // esquerda direita(ED)
    no->filhoEsquerda = rotacaoEsquerda(no->filhoEsquerda);

    return rotacaoDireita(no);
  }

  NoArvore *rotacaoDireitaEsquerda(NoArvore *no) { // diereita esquerda(DE)
    no->filhoDireita = rotacaoDireita(no->filhoDireita);
    return rotacaoEsquerda(no);
  }

  //---- BALANCEAMENTO ----
  // explicação sobre balanceamento: https://www.youtube.com/watch?v=oIp82CfCDoQ

  short calculaFatorBalanceado(NoArvore *no) {
    if (no) {
      return (alturaNo(no->filhoEsquerda) - alturaNo(no->filhoDireita));
    } else
      return 0;
  }

  NoArvore *balancearNo(NoArvore *no) {
    short bal = calculaFatorBalanceado(no);

    if (bal < -1 && calculaFatorBalanceado(no->filhoDireita) <= 0) {
      no = rotacaoEsquerda(no);
    }

    else if (bal < -1 && calculaFatorBalanceado(no->filhoDireita) > 0) {
      no = rotacaoDireitaEsquerda(no);
    }

    else if (bal > 1 && calculaFatorBalanceado(no->filhoEsquerda) >= 0) {
      no = rotacaoDireita(no);
    }

    else if (bal > 1 && calculaFatorBalanceado(no->filhoEsquerda) < 0) {
      no = rotacaoEsquerdaDireita(no);
    }

    return no;
  }

  Livro *buscaPorTitulo(string titulo) { return buscaPorTitulo(titulo, raiz); }

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

  Livro *buscaPorCodigo(int codigo) { return buscaPorCodigo(codigo, raiz); }

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

  NoArvore *remover(NoArvore *raiz, int codigo, bool *outRemovido) {
    if (codigo == raiz->valor->codigo) {
      // Remove nos sem filhos
      if (raiz->filhoEsquerda == nullptr && raiz->filhoDireita == nullptr) {
        delete raiz;

        *outRemovido = true;

        return nullptr;
      }
      // Remove no com 2 filhos
      else if (raiz->filhoEsquerda != nullptr &&
               raiz->filhoDireita != nullptr) {
        NoArvore *aux;
        aux = raiz->filhoEsquerda;
        while (aux->filhoDireita != nullptr) {
          aux = aux->filhoDireita;
        }
        raiz->valor = aux->valor;
        codigo = aux->valor->codigo;
        raiz->filhoEsquerda = remover(raiz->filhoEsquerda, codigo, outRemovido);
        return raiz;
      } else {
        NoArvore *aux = nullptr;
        if (raiz->filhoEsquerda != nullptr) {
          aux = raiz->filhoEsquerda;
        } else {
          aux = raiz->filhoDireita;
        }

        // Seta filhos para null para não serem liberados pelo destrutor
        raiz->filhoEsquerda = nullptr;
        raiz->filhoDireita = nullptr;
        delete raiz;

        *outRemovido = true;

        return aux;
      }
    } else {
      if (codigo < raiz->valor->codigo) { // esquerda
        raiz->filhoEsquerda = remover(raiz->filhoEsquerda, codigo, outRemovido);
      } else
        raiz->filhoDireita =
            remover(raiz->filhoDireita, codigo, outRemovido); // direita
    }

    atualizaAltura(raiz);
    raiz = balancearNo(raiz);
    return raiz;
  }

  void imprimir() {
    if (raiz) {
      raiz->imprimir();
    }
  }

  bool remocao(int codigo) {
    if (raiz == nullptr) {
      // verifica se o acervo esta vazio
      return false;
    } else {
      bool removido = false;
      raiz = remover(raiz, codigo, &removido);
      return removido;
    }
  }
};

// Menu com as funções realizadas pelo sistema
void menu() {
  cout << "***MENU DA BIBLIOTECA***" << endl;
  cout << "1 - Inserir livro no acervo" << endl;
  cout << "2 - Buscar livro por codioo no acervo" << endl;
  cout << "3 - Buscar livro por título no acervo" << endl;
  cout << "4 - Remover livro do acervo" << endl;
  cout << "5 - Sair" << endl;
}

int main() {
  Arvore arvore;
  int codigo, op;
  string titulo, autor;
  Livro *livro;

  bool saiu = false;

  menu();

  while (!saiu && cin >> op) {
    cin.ignore();

    switch (op) {

    // Função de inserção
    case 1:
      cout << "Digite o código do Livro que deseja inserir:" << endl;
      cin >> codigo;
      cin.ignore();

      cout << "Digite o título do Livro que deseja inserir:" << endl;
      std::getline(cin, titulo, '\n');

      cout << "Digite o autor do Livro que deseja inserir:" << endl;
      std::getline(cin, autor, '\n');

      if (arvore.buscaPorCodigo(codigo)) {
        cout << "Já possuimos um livro com esse código no acervo" << endl;
        break;
      }

      livro = new Livro(titulo, autor, codigo);
      arvore.adicionar(livro);

      cout << "Livro inserido com sucesso!" << endl << string(*livro) << endl;

      break;

    // Função de busca por código
    case 2:
      cout << "Digite o código do Livro que deseja buscar:" << endl;
      cin >> codigo;
      cin.ignore();

      livro = arvore.buscaPorCodigo(codigo);
      if (livro == nullptr) {
        cout << "Não possuimos um livro com esse título no acervo" << endl;
      } else {
        cout << "Livro encontrado: " << string(*livro) << endl;
      }

      break;

      // Função de busca por título
    case 3:
      cout << "Digite o título do Livro que deseja buscar:" << endl;
      std::getline(cin, autor, '\n');

      livro = arvore.buscaPorTitulo(titulo);
      if (livro == nullptr) {
        cout << "Não possuimos um livro com esse título no acervo" << endl;
      } else {
        cout << "Livro encontrado: " << string(*livro) << endl;
      }

      break;

    // Função de remoção
    case 4: {
      cout << "Codigo do Livro que deseja remover:" << endl;
      cin >> codigo;
      cin.ignore();

      bool removido = arvore.remocao(codigo);

      if (!removido) {
        cout << "Não possuimos um livro com esse código no acervo" << endl;
      } else {
        cout << "Livro removido com sucesso" << endl;
      }

      break;
    }

    // Saída do menu
    case 5:
      saiu = true;
      break;

    case 99:
      arvore.imprimir();
      break;

    default:
      cout << "Entre com uma opção válida" << endl;
      break;
    }

    menu();
  }

  cout << "Obrigada por utilizar o nosso sistema de biblioteca" << endl;

  return 0;
}
