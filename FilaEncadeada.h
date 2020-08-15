#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct nodo{
	char info[300];
	struct nodo *next;
}NODO;

typedef struct{
	NODO *INICIO;
	NODO *FIM;	
}DESCRITOR;

typedef DESCRITOR * FILA_ENC;

void cria_fila(FILA_ENC *f);
int eh_vazia(FILA_ENC f);
void ins(FILA_ENC f,char val[300]);
char* consulta(FILA_ENC f);
void ret(FILA_ENC f);
int tam(FILA_ENC f);

//int main(){/////////////////////////////////////////////////////////////
//FILA_ENC f1;
//
//cria_fila(&f1);
//NODO **aux;
//aux=&f1->INICIO;
//
//
//int i,j=tam(f1);
//for (i=0; i<j; i++){
//	printf ("%d,", (*aux)->info);
//	(*aux)=(*aux)->next;
//}
//
//	return 0;
//}//////////////////////////////////////////////////////////////////////

void cria_fila(FILA_ENC *f){
	*f = (DESCRITOR *) malloc (sizeof (DESCRITOR));
	if (!*f){printf ("Memoria nao alocada, encerrando!"); exit(0);	}
	
	(*f)->INICIO=(*f)->FIM=NULL;
}

int eh_vazia(FILA_ENC f){
	return (f->INICIO==NULL);
}

void ins(FILA_ENC f, char val[300]){
	NODO *novo=(NODO*) malloc (sizeof(NODO));
	if (!novo){printf ("Memoria nao alocada, encerrando..."); exit(1);	}
	novo->next=NULL;
	strcpy(novo->info,val);
	
	if (!f->INICIO){//se fila vazia
		f->INICIO=f->FIM=novo;
	}else {
		f->FIM->next=novo;
		f->FIM=novo;
	}
}

char* consulta(FILA_ENC f){
	if(eh_vazia(f)){
		printf ("\nfila vazia, n foi possivel consultar.");
		return NULL;
	}
	return (f->INICIO->info);
}

void ret(FILA_ENC f){
	NODO *aux=f->INICIO;
	if (eh_vazia(f)){
		printf ("\nretirada invalida, lista vazia");
		return ;
	}
	
	f->INICIO=f->INICIO->next;
	free(aux);
	if (eh_vazia(f)){
		f->FIM=NULL;
	}
}


int tam(FILA_ENC f){
	NODO *aux=f->INICIO;
	int i=0;
	while (aux){
		aux=aux->next;
		i++;
	}
	return i;
}
