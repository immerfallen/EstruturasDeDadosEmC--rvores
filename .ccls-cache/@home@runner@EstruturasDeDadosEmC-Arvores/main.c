#include <stdio.h>
#include <stdlib.h>

struct nodo {
int value;
struct nodo *esq;
struct nodo *dir;
};

typedef struct nodo Nodo;

Nodo* create(int valor){
	Nodo *n = (Nodo*)malloc(sizeof(Nodo));
	n->value=valor;
	n->esq = NULL;
	n->dir=NULL;

	return n;
}

void imprimir(Nodo *n)
{
	if(n==NULL){
		return;
	}
	imprimir(n->esq);
	printf("%d\n", n->value);	
	imprimir(n->dir);
}

void add(Nodo *n, int value ){
	if(value<n->value){
		if(n->esq==NULL){
			n->esq = create(value);
		} else{
			add(n->esq, value);
		}
		}
	else{
		if(n->dir == NULL){
			n->dir = create(value);
		} else{
			add(n->dir, value);
		}
	}	
}

void remover(Nodo *n, int value){

	Nodo *filho = n;
	Nodo *pai;
	do{
		pai=filho;
		if(value < filho->value){
			filho = filho->esq;
		} else if(value> filho->value){
			filho = filho->dir;
		}
	}while(filho !=NULL && filho->value != value);

	if(filho != NULL){
		if(filho->esq == NULL && filho->dir == NULL){ //CASO DO NODO NÃO POSSUIR FILHOS
			if(pai->esq == filho){
				pai->esq = NULL;
			}
			if(pai->dir == filho){
				pai->dir = NULL;
			}
		}
		if(filho->esq != NULL && filho->dir == NULL){ //CASO DO NODO FILHO TEM UM FILHO A ESQUERDA
			if(pai->esq == filho){
				pai->esq = filho->esq;
			}
			if(pai->dir == filho){
				pai->dir = filho->dir;
			}
		}

		if(filho->esq == NULL && filho->dir != NULL){ //CASO DO NODO FILHO TEM UM FILHO A DIREITA
			if(pai->esq == filho){
				pai->esq = filho->dir;
			}
			if(pai->dir == filho){
				pai->dir = filho->dir;
			}
		}

		if(filho->esq != NULL && filho->dir != NULL){ //CASO DO NODO FILHO TEM DOIS FILHOS
			if(filho->esq->dir ==NULL){
				filho->value = filho->esq->value;
			}
			else{
				Nodo *p = filho->esq;
				Nodo *aux = p;
				while(p->dir != NULL){
					aux = p;
					p=p->dir;
				}
				aux->dir = NULL;
				filho->value = p->value;
			}
		}
		
	}
	
}

int main() {

	Nodo *root = create(5);

	add(root, 2);
	add(root, 1);
	add(root, 3);
	add(root, 8);
	add(root, 4);

	
	remover(root, 5);

	imprimir(root);
	
  return 0;
}