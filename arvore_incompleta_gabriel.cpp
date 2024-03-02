#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
class No{
	public:
		int valor;
		No *esquerda;
		No *direita;
		No(int n){
			valor=n;
			esquerda=NULL;
			direita=NULL;
		}
};

class Arvore{
	public:
		No *arv;
		int quantNos;
		int h;
		Arvore(){
			arv=NULL;
			quantNos=0;
			h=-1;
		}
		
		int isEmpty(){
	   		return (arv==NULL);
		   }
		
			
		void criaNo(char n){
			No *novo= new No(n);
			
		} 
		
		void inserirSemRecursao(No *arv,No *n){
			if (isEmpty() == 1) {
				arv = n;
			}
			else {
				No *auxiliar = arv;

				while (auxiliar != NULL) {
					if (auxiliar->valor < n->valor) {
						if (auxiliar->direita == NULL) {
							auxiliar->direita = n;
							break;
						}
						else {
							auxiliar = auxiliar->direita;
						}
					}

					if (auxiliar->valor > n->valor) {
						if (auxiliar->esquerda == NULL) {
							auxiliar->esquerda = n;
							break;
						}
						else {
							auxiliar = auxiliar->esquerda;
						}
					}
				}
			}
		}
		
		void inserirComRecursao(No *arv,No *n){
			if (isEmpty() == 1) {
				arv = n;
			}
			else {
				if (arv->valor < n->valor) {
					inserirComRecursao(arv->direita, n);
				} 
				else {
						inserirComRecursao(arv->esquerda, n);
					}
			}
		}
		
		int calculaQtdNos(No *arv) {
			if (arv != NULL) {
				int qtdNos = 1;

				if (arv->esquerda != NULL) {
					qtdNos += calculaQtdNos(arv->esquerda);
					}
				if (arv->direita != NULL) {
					qtdNos += calculaQtdNos(arv->direita);
					}

					return qtdNos;
				} 
				else {
					return 0;
				}
		}
		
		int calculaAlturaArvore(No *arv) {
			if (arv != NULL) {
				int alturaEsquerda = calculaAlturaArvore(arv->esquerda);
				int alturaDireita = calculaAlturaArvore(arv->direita);
				int alturaDef;

				if (alturaEsquerda >= alturaDireita) {
					alturaDef = alturaEsquerda;
				} 
				else {
					alturaDef = alturaDireita; 
				}

				return 1 + alturaDef;
			} 
			else {
				return 0;
				}
		}
		
		int arvcompleta(){
			
		}
		
		int arvcheia(){
			
			
		}
		
		void preordem(No *n){
			
			
			
	    }
	    
	    void posordem(No *n){
			
			
		}
		
		void inordem(No *n){
			
			
		 
	    }
};

main(){
	Arvore *arvore= new Arvore();
}

