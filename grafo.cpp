#include <iostream>
#include <string>
#include <cstring>

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
    return titulo + " - " + autor + " (" +  to_string(codigo) + ")";
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
  NoArvore *filhoEsquerda; //=nullptr;

  /** Ponteiro para o filho direito */
  NoArvore *filhoDireita; //=nullptr;

  /** Altura do no */
  short altura;

  NoArvore(Livro *valor) { 
    this->valor = valor;   
    this->altura = 0; 
	  this->filhoEsquerda=nullptr;
	  this->filhoDireita=nullptr;
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

     cout << string(indent, ' ') << string(*valor) <<  endl;

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
    if(raiz==nullptr) {
      raiz = new NoArvore(valor);
       cout<<"Livro adicionado com sucesso!"<<"/n";
    }
    else raiz = inserirLivro(raiz, valor);
  }

  NoArvore *inserirLivro(NoArvore *no, Livro *valor) {

    //esquerda 
    if(valor->codigo < no->valor->codigo) {
      if(no->filhoEsquerda == nullptr) { 
          no->filhoEsquerda = new NoArvore(valor);
           cout<<"Livro adicionado com sucesso!"<<"\n";
      }
      else {
        no->filhoEsquerda = inserirLivro(no->filhoEsquerda, valor);
      }
		}
    //direita
    if(valor->codigo > no->valor->codigo) {
      if(no->filhoDireita == nullptr) { 
          no->filhoDireita = new NoArvore(valor);
           cout<<"Livro adicionado com sucesso!"<<"\n";
      }
      else {
        no->filhoDireita = inserirLivro(no->filhoDireita, valor);
      }
    }
    //se não for nenhum, então já existe
    else {
       cout << "Código digitado já existe, tente novamente com outros dados" <<"\n";
    }

    atualizaAltura(no);
    return balancearNo(no);
    
  }

//---- ALTURA ----

  short alturaNo(NoArvore *no) {

    if(no == nullptr) return -1;
    
    else return no->altura;
    
  }
  //a testar
  void atualizaAltura(NoArvore *no) {
    short alturaEsquerda = alturaNo(no->filhoEsquerda);
    short alturaDireita = alturaNo(no->filhoDireita);
    no->altura = maior(alturaEsquerda, alturaDireita) + 1;
  }

  short maior(short a, short b) {
    return (a > b)? a : b; //'a' é maior do que 'b'? se sim retorne 'a', senão retorne 'b'
  } 


//---- ROTAÇÃO ----

  NoArvore* rotacaoDireita(NoArvore *no) {//direita direita(DD)
    NoArvore *aux1, *aux2;

    aux1 = no->filhoEsquerda;
    aux2 = aux1->filhoDireita;

    aux1->filhoDireita = no;
    no->filhoEsquerda = aux2; 

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
    return rotacaoEsquerda(no);
  }


//---- BALANCEAMENTO ----   
//explicação sobre balanceamento: https://www.youtube.com/watch?v=oIp82CfCDoQ 


  short calculaFatorBalanceado(NoArvore *no) {
    if(no) {
      return (alturaNo(no->filhoEsquerda) - alturaNo(no->filhoDireita));
    }
    else return 0;
  }

  NoArvore* balancearNo(NoArvore *no) {
    short bal = calculaFatorBalanceado(no);

    if(bal < -1 && calculaFatorBalanceado(no->filhoDireita) <=0) { no = rotacaoEsquerda(no); }

    else if(bal < -1 && calculaFatorBalanceado(no->filhoDireita) > 0) { no = rotacaoDireitaEsquerda(no); }

    else if(bal > 1 && calculaFatorBalanceado(no->filhoEsquerda) >=0) { no = rotacaoDireita(no); }

    else if(bal > 1 && calculaFatorBalanceado(no->filhoEsquerda) < 0) { no = rotacaoEsquerdaDireita(no); }

    return no;
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

  NoArvore *remover(NoArvore *raiz, int codigo) {

      if(codigo == raiz->valor->codigo) { 
        //Remove nos sem filhos
        if (raiz->filhoEsquerda==nullptr && raiz->filhoDireita==nullptr){
          free(raiz);
          return nullptr;
        }
        //Remove no com 2 filhos
        else if(raiz->filhoEsquerda != nullptr && raiz->filhoDireita != nullptr){
          NoArvore *aux;  
          aux = raiz->filhoEsquerda;
          while(aux->filhoDireita!=nullptr){
            aux = aux->filhoDireita;
          } 
          raiz->valor=aux->valor;
          codigo = aux->valor->codigo;
          raiz->filhoEsquerda = remover(raiz->filhoEsquerda, codigo);
          return raiz;
        }
        else{
          NoArvore *aux=nullptr;
          if (raiz->filhoEsquerda!=nullptr){
            aux=raiz->filhoEsquerda;
          }
          else {
            aux=raiz->filhoDireita;
          }
          free(raiz);
          return aux;
        }
      }
      else {
        if(codigo < raiz->valor->codigo) { //esquerda
          raiz->filhoEsquerda = remover(raiz->filhoEsquerda, codigo);
        }
        else raiz->filhoDireita = remover(raiz->filhoDireita, codigo); //direita
      }
      cout << "Livro removido com sucesso" << "\n";
    atualizaAltura(raiz);
    raiz = balancearNo(raiz);
      return raiz;
  }

  void imprimir() {
    if (raiz) {
      raiz->imprimir();
    }
  }
  
  void remocao (int codigo) {
    if(raiz==nullptr) {
      // verifica se o acervo esta vazio
        cout << "Livro nao encontrado no acervo" << "\n";
    }
    else {
      remover(raiz, codigo);
    }
  }
};

// Menu com as funções realizadas pelo sistema
void menu(){
   cout << "***MENU DA BIBLIOTECA***" << "\n";
   cout << "1 - Inserir livro no acervo" << "\n";
   cout << "2 - Buscar livro por codioo no acervo" << "\n";
   cout << "3 - Buscar livro por título no acervo" << "\n";
   cout << "4 - Remover livro do acervo" << "\n";
   cout << "5 - Sair" << "\n";
}

int main() {
  Arvore arvore;
  int codigo, op;
  string titulo, autor;
  FILE *teste;

  arvore.adicionar(new Livro("O Senhor dos Anéis", "J. R. R. Tolkien", 1));

  arvore.adicionar(new Livro("O Hobbit", "J. R. R. Tolkien", 2));

  arvore.adicionar(new Livro("O Silmarillion", "J. R. R. Tolkien", 3));

  arvore.adicionar(new Livro("O escaravelho de ouro", "Edgar Allan Poe", 4));

  arvore.adicionar(new Livro("O Guia do Mochileiro das Galáxias", "Douglas Adams", 5));

  arvore.adicionar(new Livro("Metamorfose", "Franz Kafka", 6)); 
  arvore.imprimir(); 

  teste = fopen("./casosTeste.txt", "r");
  if (teste == NULL)
{
    printf("Problemas na leitura do arquivo\n");
    return; // Está dando erro e impedindo o programa de compilar
}
  do{
    menu();
     cin >> op;
    switch(op){

      //Função de inserção
      case 1:
         cout << "Digite o código do Livro que deseja inserir:" << "\n";
         cin >> codigo;
         cout << "Digite o título do Livro que deseja inserir:" << "\n";
         cin >> titulo;
         cout << "Digite o autor do Livro que deseja inserir:" << "\n";
         cin >> autor;
        arvore.adicionar(new Livro(titulo, autor, codigo));

       break;
      
      //Função de busca por código
      case 2: { 
        cout << "Digite o código do Livro que deseja buscar:" << "\n";
        cin >> codigo;
        Livro *livro = arvore.buscaPorCodigo(codigo);
        if (livro == nullptr) {
          cout << "Não possuimos um livro com esse título no acervo" << endl;
        } else {
          cout << "Livro encontrado: " << string(*livro) << endl;
        }

        break;
      }
       //Função de busca por título
      case 3: { 
        cout << "Digite o título do Livro que deseja buscar:" << "\n";
        cin >> titulo;
        Livro *livro = arvore.buscaPorTitulo(titulo);
        if (livro == nullptr) {
          cout << "Não possuimos um livro com esse título no acervo" << endl;
        } else {
          cout << "Livro encontrado: " << string(*livro) << endl;
        }
        
        break;
      }
      //Função de remoção
      case 4:
         cout << "Codigo do Livro que deseja remover:" << "\n";
         cin >> codigo;
         arvore.remocao(codigo);
       break;

      //Saída do menu
      case 5:
          cout << "Obrigada por utilizar o nosso sistema de biblioteca" << "\n";

       break;

      default:
         cout << "Entre com uma opção válida" << "\n";

       break;
    }
  } while(op!=5);

  return 0;
}
