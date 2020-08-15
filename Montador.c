#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FuncoesParaMontador.h"
#include <math.h>
#define MAX 300




int main(){
	Fourbytes *vetor=(Fourbytes*) malloc (sizeof(Fourbytes)*128);
	if (!vetor){printf ("erro na alocacao do vetor de bytes");	}
	char *str=(char*) malloc (sizeof (char)*MAX), aux[MAX],nomearquivo[50];
	int c,instcount=0,labelcount=0,i,e,j;
	FILE *ASMF,*SAIDA; //variável de ponteiro de arquivo
	FILA_ENC f1;
	NODO *nodofila;
	vetor[0].H1[0]='a';
	cria_fila(&f1);
	Lista l1; cria_lista(&l1);
	
	printf ("Insira o nome do arquivo asm: ");
	scanf ("%s",nomearquivo);

	if ( !(SAIDA = fopen("memoria.mif","w+")) ){
		printf ("Arquivo saida nao pode ser aberto");
	getch();
	exit(1);
	}
	
	for (i=0; i<128; i++){ //zerando os valores 
		for(j=0; j<2; j++){
			vetor[i].H1[j]='0';
			vetor[i].H2[j]='0';
			vetor[i].H3[j]='0';
			vetor[i].H4[j]='0';
		}
			vetor[i].H1[j]='\0';
			vetor[i].H2[j]='\0';
			vetor[i].H3[j]='\0';
			vetor[i].H4[j]='\0';		
	}
	
	if (( ASMF = fopen(nomearquivo, "r")) == NULL){ //ABERTURA DE ARQUIVO
	printf ("Arquivo invalido");
	getch();
	exit(1);
}
		
//	rewind(ASMF); //realoca o ponteiro pro inicio do arquivo
//	fseek(ASMF,0,SEEK_SET);//seta a posição do ponteiro

	while (!feof(ASMF)){ //feof = END OF FILE -> retorna verdadeiro se chegar ao fim do arquivo
		limparvetor(str,300);
		int i,x,entra=0;	 // Percorrendo o arquivo e armazenando o que importa numa fila encadeada
		
		fgets(str, MAX, ASMF); // fgets(char*, size, FILE); lê uma string ate (size-1) ou ate achar um '\n' 
		
		for (i=0,x=0; i<MAX; i++,x++){
			while (str[i]=='\t') i++; // se for tabulação, vou pro prox caractere

			if (str[i]=='#' || (str[i]=='\n' && i<2)){ //se for comentario ou se o primeiro caractere for um '\n', vou p prox linha
				break ;
			}else if (str[i]=='\n'){
				aux[x]='\0';
				entra=1;	
			}else {
				entra=1;
				aux[x]=str[i];
			}
		}
		
		if (entra){
		ins(f1,aux);
//		printf ("%s\n", aux);
		}
	}
	
	int tamanho=tam(f1);
	nodofila=f1->INICIO;
	

	for (e=0; e<tamanho; e++, nodofila=nodofila->next){ //criar a lista de labels
		char inst[MAX],aux[MAX];	
		int temop=0,i=0,x=0;
	
		strcpy(inst,nodofila->info); //consulto e coloco em inst o elemento da fila
		
		limparvetor(aux,300);	
	
	
		while (inst[i]!=' ' && inst[i]!=':'){ //pegar o operador ou o label percorrendo a linha
			if (inst[i]=='\n') break ; // vou parar se o elemento só tiver o '\n'
			aux[x]=inst[i];
			i++;
			x++;
		}
		
		if (inst[i]==':'){ // É LABEL
			inserel(&l1, aux, ++labelcount/*posicao de insercao na lista*/,instcount/*posicao do label na memoria*/);
	
			while (inst[i+1]!='\n' && inst[i+1]!='\0'){
				if (inst[i+1]==' ' || inst[i+1]=='\t'){
				i++;
				}else 
				goto TemOperador; //caso ainda tenha operador apos o label do arquivo, vai p lá
			}		
		}else {
			TemOperador:
			instcount++;
		}
	}
		

	ler_instrucoes(&f1,&l1,tamanho,vetor);
	
	//INSERIR OS DADOS NO ARQUIVO DE SAIDA
	fputs("WITH = 8;\n",SAIDA);
	fputs("DEPTH=512;\n\n",SAIDA);
	fputs("ADDRESS_RADIX = HEX;\n",SAIDA);
	fputs("DATA_RADIX = HEX;\n\n",SAIDA);
	fputs("CONTENT BEGIN\n",SAIDA);
	char endBIN[13];
	char endHEXA[4];
	int contador=0;
	for (i=0; i<128; i++){
		for (j=0; j<4; j++){
		
		fputs("\t",SAIDA);
		
		zerarvetor(endBIN,13);
		zerarvetor(endHEXA,4);
		dec_bin(contador++,endBIN,12);
		bin12_hexa(endBIN,endHEXA);
		fputs(endHEXA,SAIDA);
		fputs("   :",SAIDA);
		if (j==0){
			fputs(vetor[i].H1,SAIDA);
			fputs(";",SAIDA);
			fputs("\n",SAIDA);
//			printf ("%s %s\n",endHEXA,vetor[i].H1);
		}else if(j==1){
			fputs(vetor[i].H2,SAIDA);
			fputs(";",SAIDA);
			fputs("\n",SAIDA);
//			printf ("%s %s\n",endHEXA,vetor[i].H2);
		}else if(j==2){
			fputs(vetor[i].H3,SAIDA);
			fputs(";",SAIDA);
			fputs("\n",SAIDA);
//			printf ("%s %s\n",endHEXA,vetor[i].H3);
		}else{
			fputs(vetor[i].H4,SAIDA);
			fputs(";",SAIDA);
			fputs("\n",SAIDA);
//			printf ("%s %s\n",endHEXA,vetor[i].H4);
		}
		
//		printf ("end BIN = %s >>",endBIN);
//		printf ("end HEXA = %s\n",endHEXA);

//		printf ("%s",vetor[i].H2);
		}
	}
	fputs("END;",SAIDA);
	printf ("Arquivo de saida gerado com sucesso!\n Pressione qualquer tecla para encerrar...");
	
	fclose(ASMF);
	getch();
	return 0;
	
}

