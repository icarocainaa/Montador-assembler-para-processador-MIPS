#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct label {
	char info[30];
	int posicaolabel;
	int memorialabel;
	struct label *prox;
}LABEL;

typedef LABEL *Lista;

void cria_lista(Lista *l);
int eh_vazial(Lista l);
int taml(Lista l);
void inserel(Lista *l, char nomelabel[], int pos,int pos_label);
void retiral(Lista *l, int pos);
int consposlabel(Lista l, char nomelabel[]);

//int main(){ // ----------------------------------------------------------------------------------------------------------
//
//Lista l1,l2;
//int i;
//
//cria_lista(&l1);
//inserel(&l1,"matrix",1,4);
//inserel(&l1,"Neo",2,5);
//inserel(&l1,"morpheu",3,11);
////printf ("%d",taml(l1));
////printf ("Posicao do label: %d",consposlabel(l1, "Neo"));
//
//
//
//	return 0;
//}//----------------------------------------------------------------------------------------------------------

void cria_lista(Lista *l){
	*l=NULL;
}

void inserel(Lista *l, char nomelabel[], int pos_ins,int pos_label){
	
	LABEL *novo = (LABEL *) malloc (sizeof (LABEL));
	if (!novo){printf ("Memoria nao alocada, encerrando..."); exit(0);	}
	strcpy(novo->info,nomelabel);
	novo->posicaolabel=pos_ins;
	novo->prox=NULL;
	novo->memorialabel=pos_label*4;
//	itoa(pos_label*4, novo->memorialabel,10);
//	printf ("memoria label: %s",novo->memorialabel);

	if (!*l){ //se lista vazia
		if (pos_ins!=1){printf ("Lista vazia, posicao de insercao alterada para 1.\n");}
		*l=novo;
	
	}else if (pos_ins==1){//inserir na primeira posicao
		novo->prox = *l;
		*l=novo;
	
	}else { // inserir numa outra posicao qualquer
		int i;
		LABEL *aux=*l;
		
		while (pos_ins < 1 || pos_ins > taml(*l)+1){ //verificando validade da posicao
		printf ("posicao de insercao na lista invalida,encerrando! ");
		exit(5);
	}
		for (i=0; i<pos_ins-2; i++){
			aux=aux->prox;
		}
		novo->prox=aux->prox;
		aux->prox=novo;
	}
	
}

int eh_vazial(Lista l){
	return (l==NULL);
	
}

int taml(Lista l){
	int i=0;
	LABEL *aux;
	
	for (aux=l; aux; aux=aux->prox,i++);

	return i;
	
	
}

void retiral(Lista *l, int pos){
	LABEL *aux=*l,*aux1=*l;
	int i;
	
	if (pos > taml(*l) || pos < 1){//validando posicao
		printf ("Posicao de remocao invalida, encerrando o programa.");
		exit(0);
	}
	
	if (pos==1){
		*l=(*l)->prox;
		free(aux1);
	}else {
	for (i=0; i<pos-2; i++){
		aux=aux->prox;
		aux1=aux1->prox;
		}
	aux1=aux1->prox;
	aux->prox = aux1->prox;
	free (aux1);
	}
}

int consposlabel(Lista l,char nomelabel[]){
	LABEL *aux=l;
	int i, d=taml(l);
	
	for (i=0; i<d; i++){
		if (!strcmp(nomelabel, aux->info)){
			return aux->posicaolabel;
		}else {
			aux=aux->prox;
		}
	}

	printf ("Label nao pertence a lista");
	return -1;
}

