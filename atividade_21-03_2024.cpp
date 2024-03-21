#include <iostream>
#include <math.h>
#include <queue>
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
      this->inserirComRecursao(this->raiz, criarNo(valor));
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
      preOrdem(noAtual->right);
    }
  }

  No *buscaSemRecursao(int valor) {
    No *atual = this->raiz;
    while (atual != NULL) {
      if (atual->valor == valor) {
        return atual;
      } else {
        if (atual->valor > valor) {
          atual = atual->right;
        } else {
          if (atual->valor < valor) {
            atual = atual->left;
          }
        }
      }
    }

    return NULL;
  }

  /*
        função para remover nós da Árvore binária
  */

  No *removerNoFolha(No *no_atual, int valor_a_ser_removido) {
    free(no_atual);
    cout << "Elemento folha removido: " << valor_a_ser_removido;
    return NULL;
  }

  No *removerNoComUmFilho(No *no_atual, int valor_a_ser_removido) {
    return NULL;
  }
  No *menorNo(No *no_atual) {
    No *atual = no_atual;
    while (atual->left != NULL) {
      atual = atual->left;
    }
    return atual;
  }
  No *maximoNo(No *noAtual) {
    No *atual = noAtual;
    while (atual->right != NULL) {
      atual = atual->right;
    }
    return atual;
  }

  No *remover(No *no_atual, int valor_a_ser_removido) {
    if (no_atual == NULL) {
      printf("Valor nao encontrado!\n");
      return NULL;
    } else {
      // procura o nó a remover

      if (no_atual->valor == valor_a_ser_removido) {
        // remove nós folhas (nós sem filhos)
        if (no_atual->left == NULL && raiz->right == NULL) {
          return removerNoFolha(no_atual, valor_a_ser_removido);
        }
        //  nos com 2 filhos
        else if (no_atual->left != NULL && no_atual->right != NULL) {
          /*
            // PROCURAR O MENOR NO NA SUB ARVORE A DIREITA
            No *menorNoEncontrado = menorNo(no_atual->right);
            // substitui o valor do no excluido pelo valor do menor no
            encontrado no_atual->valor = menorNoEncontrado->valor;
            // PRA EVITAR DUPLICACAO, REMOVER O NO DO MENOR VALOR DA SUBARVORE
            DIREITA

              No *penultimo = no_atual->right;
              while (penultimo->left ->left!= NULL) {
                penultimo = penultimo->left;
              }
              penultimo->left = NULL;
              delete menorNoEncontrado;

             return no_atual;
           */

          /*

         // >>>>>>>>>>>>>>>>>>>>>MAXIMO NO DA SUBARVORE<<<<<<<<<<<<<<<<<<

           // PROCURAR O MENOR NO NA SUB ARVORE ESQUERDA
           No *maiorNoEncontrado = maximoNo(no_atual->left);
           // substitui o valor do no excluido pelo valor do menor no encontrado
           no_atual->valor = maiorNoEncontrado->valor;
           // PRA EVITAR DUPLICACAO, REMOVER O NO DO MENOR VALOR DA SUBARVORE
         DIREITA

             No *penultimo = no_atual->left;
             while (penultimo->right ->right!= NULL) {
               penultimo = penultimo->right;
             }
             penultimo->right = NULL;
             delete maiorNoEncontrado;

            return no_atual;
           */

        }

        // remover nós que possuem 1
        else if (no_atual->left != NULL || no_atual->right != NULL) {

          No *aux = NULL;
          if (no_atual->left != NULL) {
            aux = no_atual->left;
            cout << "\nRemovendo o NO com valor " << no_atual->valor
                 << " que tem um NO filho A esquerda  com valor "
                 << no_atual->left->valor << endl
                 << endl;
          } else if (no_atual->right != NULL) {
            aux = no_atual->right;
            cout << "\nRemovendo o NO com valor " << no_atual->valor
                 << "  que tem um NO filho direta  com valor "
                 << no_atual->right->valor << endl
                 << endl;
          }
          free(no_atual);
          return aux;
        }

      } else {

        if (valor_a_ser_removido < no_atual->valor)
          no_atual->left = remover(no_atual->left, valor_a_ser_removido);
        else {
          no_atual->right = remover(no_atual->right, valor_a_ser_removido);
        }
        return no_atual;
      }
    }
    return no_atual;
  }

  void percorrerPorNivel() {
    if (raiz == NULL) {
      cout << "Arvore vazia." << endl;
      return;
    }

    queue<No *> fila;
    fila.push(raiz);

    cout << "Pesquisa por Nivel: ";
    while (!fila.empty()) {
      int tamanhoNivel = fila.size(); // Número de nós no nível atual

      for (int i = 0; i < tamanhoNivel; i++) {
        No *noAtual = fila.front();
        fila.pop();

        cout << noAtual->valor << " ";

        if (noAtual->left != NULL) {
          fila.push(noAtual->left);
        }
        if (noAtual->right != NULL) {
          fila.push(noAtual->right);
        }
      }
      cout << "| "; // Separador de níveis
    }
    cout << endl;
  }

  bool vereficarSeArvoresSaoIguais(No *noAtual1, No *noAtual2) {
    if (noAtual1 == NULL && noAtual2 == NULL) {
      cout << "As arvores sao Vazias" << endl;
      return true;
    }

    queue<No *> filaArvore1;
    filaArvore1.push(noAtual1);

    queue<No *> filaArvore2;
    filaArvore2.push(noAtual2);

    while (!filaArvore1.empty()) {
      int tamanhoNivelArvore1 =filaArvore1.size(); // Número de nós no nível atual
      int tamanhoNivelArvore2 = filaArvore2.size();
      
      if (tamanhoNivelArvore1 != tamanhoNivelArvore2) {
        return false;
      }

      for (int i = 0; i < tamanhoNivelArvore1; i++) {
        No *noAtual1 = filaArvore1.front();
        filaArvore1.pop();

        No *noAtual2 = filaArvore2.front();
        filaArvore2.pop();

        if (noAtual1->valor != noAtual2->valor) {
          return false;
        }

        // filhos do nos do nivel atual -Arvore 1
        if (noAtual1->left != NULL) {
          filaArvore1.push(noAtual1->left);
        }
        if (noAtual1->right != NULL) {
          filaArvore1.push(noAtual1->right);
        }
        // filhos do nos do nivel atual -Arvore 2
        if (noAtual2->left != NULL) {
          filaArvore2.push(noAtual2->left);
        }
        if (noAtual2->right != NULL) {
          filaArvore2.push(noAtual2->right);
        }
      }
      // cout << "| "; // Separador de níveis
    }
    // cout<<"fim da funcao"<<endl;
    return true;
  }


};

int main() {
  Arvore *arvore = new Arvore();
  arvore->inserir(11);
  arvore->inserir(15);
  arvore->inserir(16);

  arvore->inserir(14);
  arvore->inserir(8);

  arvore->inserir(7);
  arvore->inserir(9);

  Arvore *arvore2 = new Arvore();
  arvore2->inserir(11);
  arvore2->inserir(15);
  arvore2->inserir(16);

  arvore2->inserir(14);
  arvore2->inserir(8);

   arvore2->inserir(7);
  arvore2->inserir(9);
  
  cout<<"ARVORE 1: "<<endl;
  arvore->percorrerPorNivel();
  cout<<"ARVORE 2: "<<endl;
  arvore2->percorrerPorNivel();

  cout<<"\n\nARVORE 1 E ARVORE 2 SAO IGUAIS? \n"<<endl;
  if (arvore->vereficarSeArvoresSaoIguais(arvore->raiz, arvore2->raiz)==true) {
    cout << ">>> as arvores sao iguais!"<<endl;;
  } else {
    cout << ">>>> as arvores sao diferentes !"<<endl;;
  }

 

  // arvore->preOrdem(arvore->raiz);
  // cout << "\n";
  // arvore->remover(arvore->raiz, 9);
  // arvore->preOrdem(arvore->raiz);
  // cout << "\n\n\n\n\n";

  // ordem: V-E-D
  // cout << "\n Percurso Pre Ordem :  ";
  // arvore->preOrdem(arvore->raiz);

  // ordem: E-V-D
  // cout << "\n Percurso In Ordem :  ";
  // arvore->inOrdem(arvore->raiz);

  // ordem: E-D-V
  // cout << "\nPercurso Pos Ordem :  ";
  // arvore->posOrdem(arvore->raiz);

  // ordem: E-D-V
  // cout << "\nteste :  ";
  // arvore->teste(arvore->raiz);

  // cout << " \n altura: " << arvore->calculaAlturaArvore(arvore->raiz);
  // cout << " \n Quantodade de nos: " << arvore->calculaqtdNos(arvore->raiz);

  /*
  if (arvore->arvcheia()) {
    // cout << "\n Arvore cheia!";
  } else {
    // cout << "\n Arvore nao cheia!";
  }

  if (arvore->arvcompleta()) {
    // cout << "\n Arvore completa!";

  } else {
    // cout << "\n Arvore nao completa!\n";
  }
*/

  // arvore->percorrerPorNivel();
  // arvore->inserir(17);
  // arvore->remover(arvore->raiz,16);
  // arvore->percorrerPorNivel();
  // arvore->remover(arvore->raiz, 16);
  // arvore->percorrerPorNivel();

  // arvore->percorrerPorNivel();
  // arvore->remover(arvore->raiz, 11);
  // arvore->percorrerPorNivel();

  return 0;
}