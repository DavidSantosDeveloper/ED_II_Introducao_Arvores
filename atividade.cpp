#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

class No {
public:
  int valor;
  No *left;
  No *right;
  No(int n) {
    valor = n;
    left = NULL;
    right = NULL;
  }
};

class Arvore {
public:
  No *raiz;
  int quantNos;
  int h;
  Arvore() {
    raiz = NULL;
    quantNos = 0;
    h = -1;
  }

  int isEmpty() { return (raiz == NULL); }

  No *criarNo(int n) {
    No *novo = new No(n);
    return novo;
  }

  void inserir(int valor) {
    if (this->raiz == NULL) {
      this->raiz = this->criarNo(valor);
    } else {
      this->inserirSemRecursao(this->raiz, criarNo(valor));
    }
  }
  void inserirSemRecursao(No *noAtual, No *novoNo) {
    while (true) {
      if (novoNo->valor < noAtual->valor) {
        if (noAtual->left == NULL) {
          noAtual->left = novoNo;
          break;
        } else {
          noAtual = noAtual->left;
        }
      } else {
        if (noAtual->right == NULL) {
          noAtual->right = novoNo;
          break;
        } else {
          noAtual = noAtual->right;
        }
      }
    }
  }

  void inserirComRecursao(No *noAtual, No *novoNo) {
    if (novoNo->valor == noAtual->valor) {
      return; // Ignora a inserção de valores duplicados
    }



    if (novoNo->valor < noAtual->valor) {
      if (noAtual->left == NULL) {
        noAtual->left = novoNo;
      } else {
        this->inserirComRecursao(noAtual->left, novoNo);
      }
    } else {
      if (noAtual->right == NULL) {
        noAtual->right = novoNo;
      } else {
        this->inserirComRecursao(noAtual->right, novoNo);
      }
    }
  }

  int calculaqtdNos(No *noAtual) {
    if (noAtual == NULL) {
      return 0;
    } else {
      return 1 + calculaqtdNos(noAtual->left) + calculaqtdNos(noAtual->right);
    }
  }

  int calculaAlturaArvore(No *noAtual) {

    int altura_subarvore_esquerda = 0;
    int altura_subarvore_direita = 0;
    int altura_da_arvore = 0;
    // Percorrimento por POS-ORDEM (Escolha)

    if (noAtual != NULL) {
      if (noAtual->left != NULL) {
        altura_subarvore_esquerda++;
        calculaAlturaArvore(noAtual->left);
      } else if (noAtual->right != NULL) {
        altura_subarvore_direita++;
        calculaAlturaArvore(noAtual->right);
      }

      (altura_subarvore_esquerda > altura_subarvore_direita)
          ? altura_da_arvore = altura_subarvore_esquerda + 1
          : altura_da_arvore = altura_subarvore_direita + 1;

      return altura_da_arvore;
    }

    // Caso em que a arvore quando for vazia
    return -1;
  }

  bool arvcompleta() {
    // 1+ piso de log n na base 2== altura -> arvore completa

    int piso_log_n_base_2 = floor(log2(this->calculaqtdNos(this->raiz)));

    int resultado = 1 + piso_log_n_base_2;

    if (resultado == this->calculaAlturaArvore(this->raiz)) {
      return true;
    } else
      return false;
  }

  bool arvcheia() {
    // 2**h-1== qtde de nos -> arvore cheia
    return pow(2, calculaAlturaArvore(this->raiz)) - 1 == quantNos;
  }

  void preOrdem(No *noAtual) {
    // ordem: V-E-D
    if (noAtual != NULL) {
      cout << noAtual->valor << " ";
      posOrdem(noAtual->left);
      posOrdem(noAtual->right);
    }
  }

  void posOrdem(No *noAtual) {
    // ordem: E-D-V
    if (noAtual != NULL) {
      posOrdem(noAtual->left);
      posOrdem(noAtual->right);
      cout << noAtual->valor << " ";
    }
  }

  void inOrdem(No *noAtual) {
    // ordem: E-V-D
    if (noAtual != NULL) {
      posOrdem(noAtual->left);
      cout << noAtual->valor << " ";
      posOrdem(noAtual->right);
    }

  }
void teste(No *noAtual) {
// ordem: E-V-D
if (noAtual != NULL) {
  cout << noAtual->valor << " ";
  posOrdem(noAtual->right);
 }
}
};

int main() {
  Arvore *arvore = new Arvore();
  arvore->inserir(11);
  arvore->inserir(14);
  arvore->inserir(16);
  arvore->inserir(15);

  arvore->inserir(8);

  arvore->inserir(7);
  arvore->inserir(9);








  // ordem: V-E-D
  cout << "\n Percurso Pre Ordem :  ";
  arvore->preOrdem(arvore->raiz);

  // ordem: E-V-D
  cout << "\n Percurso In Ordem :  ";
  arvore->inOrdem(arvore->raiz);

  // ordem: E-D-V
  cout << "\nPercurso Pos Ordem :  ";
  arvore->posOrdem(arvore->raiz);

  // ordem: E-D-V
  cout << "\nteste :  ";
  arvore->teste(arvore->raiz);


  cout << " \n altura: " << arvore->calculaAlturaArvore(arvore->raiz);
  cout << " \n Quantodade de nos: " << arvore->calculaqtdNos(arvore->raiz);

  if(arvore-> arvcheia()){
    cout<<"\n Arvore cheia!";
  }
  else{
    cout<<"\n Arvore nao cheia!";
  }
  
  
  if(arvore->arvcompleta()){
    cout<<"\n Arvore completa!";

  }
  else{
    cout<<"\n Arvore nao completa!";
  }

  return 0;
}
