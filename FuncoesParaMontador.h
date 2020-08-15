#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "FilaEncadeada.h"
#include "ListaDinEnc.h"
#define MAX 300

typedef struct bytes{
	char H1[3]; //maior valor
	char H2[3];
	char H3[3];
	char H4[3];	// menor valor
}Fourbytes;



int bin_dec(char bin[],int tam); 
char* operacao(char operador[],char *recep);
void registrador(char rg[5], char *recep);
void ler_instrucoes(FILA_ENC *f, Lista *l1,int tamFila,Fourbytes *vet);
void funct(char *operador, char *recep);
void shamt(char *qtd, char *recep);
void limparvetor(char *,int tam); //para limpar eu passo o tamanho TOTAL-1 
void dec_bin(int d, char *recep,int tam); //decimal para binario com complemento de 2
void zerarvetor(char *vet,int tam); //para zerar eu passo o tamanho TOTAL do vetor
void bin32_hexa(char *, char *recep);//binario de 32 bits para hexadecimal de 8 hexas
void bin12_hexa(char *bin, char *recep);

//int main(){
//	FILA_ENC f1;
//	Lista l1;
//	cria_lista(&l1);
//	inserel(&l1,"main",1,0);
//	inserel(&l1,"next",2,5);
//	inserel(&l1,"exit",3,10);
//
//
//	cria_fila(&f1);
//	ins(f1,"add $s0, $zero, $zero");
//	ins(f1,"add $s1, $zero, $zero");
//	ins(f1,"addi $t0, $zero, 6");
//	ins(f1,"addi $t1, $zero, 12");
//	ins(f1,"addi $t2, $zero, 3");
//	ins(f1,"beq $t0, $zero, exit");
//	ins(f1,"add $s0, $s0, $t1");
//	ins(f1,"add $t1, $t1, $t2");
//	ins(f1,"addi $t0, $t0, -1");
//	ins(f1,"j next");
//	ler_instrucoes(&f1,&l1);	
//	
////	registrador(Rs,receptor);
////	operacao(Op,receptor);
////	printf ("%s",receptor);
//
//
//	return 0;
//}

int bin_dec(char bin[],int tam){
	int i,cont,valordecimal=0;
	
	for (i=tam-1,cont=0; i>0; cont++,i--){
		valordecimal += (bin[i-1]=='1' ? ((int)pow(2,cont)): 0);
	}
	return valordecimal;
	
}

char* operacao(char operador[], char *recep){ // passo o operador e um receptor de tam[7] pra função

	if (!strcmp(operador,"addi")){strcpy(recep,"001000");	
	}else if (!strcmp(operador,"lui")){strcpy(recep,"001111");
	}else if (!strcmp(operador,"andi")){strcpy(recep,"001100");
	}else if (!strcmp(operador,"ori")){strcpy(recep,"001101");
	}else if (!strcmp(operador,"xori")){strcpy(recep,"001110");
	}else if (!strcmp(operador,"slti")){strcpy(recep,"001010");
	}else if (!strcmp(operador,"beq")){strcpy(recep,"000100");
	}else if (!strcmp(operador,"bne")){strcpy(recep,"000101");
	}else if (!strcmp(operador,"lw")){strcpy(recep,"100011");
	}else if (!strcmp(operador,"sw")){strcpy(recep,"101011");
	}else if (!strcmp(operador,"j")){strcpy(recep,"000010");
	}else if (!strcmp(operador,"jal")){strcpy(recep,"000011");
	}else strcpy(recep,"000000");{
		if (!strcmp(operador,"add")){return ("100000");
			}else if (!strcmp(operador,"sub")){return ("100010");
			}else if (!strcmp(operador,"sll")){return ("000000");
			}else if (!strcmp(operador,"srl")){return ("000010");
			}else if (!strcmp(operador,"and")){return ("100000");
			}else if (!strcmp(operador,"or")){return ("010101");
			}else if (!strcmp(operador,"xor")){return ("100110");
			}else if (!strcmp(operador,"slt")){return ("101010");
			}else if (!strcmp(operador,"jr"))return ("001000");
	}
	return "000000"; //retornando o FUNCT 000000 caso a operação n seja tipo R
}

void registrador(char rg[5],char *recep){ // Passo o registrador e um receptor de tam[6] pra funcao
		
	if (!strcmp(rg,"zero")){strcpy(recep,"00000");
	}
	
	if (!strcmp(rg,"at")){strcpy(recep,"00001");	
	}
	
	if (!strcmp(rg,"v0")){strcpy(recep,"00010");
	}
		
	if (!strcmp(rg,"v1")){strcpy(recep,"00011");
	}
		
	if (!strcmp(rg,"a0")){strcpy(recep,"00100");
	}
		
	if (!strcmp(rg,"a1")){strcpy(recep,"00101");
	}
		
	if (!strcmp(rg,"a2")){strcpy(recep,"00110");
	}
			
	if (!strcmp(rg,"a3")){strcpy(recep,"00111");
	}
				
	if (!strcmp(rg,"t0")){strcpy(recep,"01000");
	}	
		
	if (!strcmp(rg,"t1")){strcpy(recep,"01001");
	}
				
	if (!strcmp(rg,"t2")){strcpy(recep,"01010");
	}		
		
	if (!strcmp(rg,"t3")){strcpy(recep,"01011");
	}		
		
	if (!strcmp(rg,"t4")){strcpy(recep,"01100");
	}		
		
	if (!strcmp(rg,"t5")){strcpy(recep,"01101");
	}		
		
	if (!strcmp(rg,"t6")){strcpy(recep,"01110");
	}		
		
	if (!strcmp(rg,"t7")){strcpy(recep,"01111");
	}
				
	if (!strcmp(rg,"s0")){strcpy(recep,"10000");
	}		
		
	if (!strcmp(rg,"s1")){strcpy(recep,"10001");
	}
			
	if (!strcmp(rg,"s2")){strcpy(recep,"10010");
	}		
		
	if (!strcmp(rg,"s3")){strcpy(recep,"10011");
	}
				
	if (!strcmp(rg,"s4")){strcpy(recep,"10100");
	}		
		
	if (!strcmp(rg,"s5")){strcpy(recep,"10101");
	}
				
	if (!strcmp(rg,"s6")){strcpy(recep,"10110");
	}
				
	if (!strcmp(rg,"s7")){strcpy(recep,"10111");
	}
				
	if (!strcmp(rg,"t8")){strcpy(recep,"11000");
	}		
		
	if (!strcmp(rg,"t9")){strcpy(recep,"11001");
	}
				
	if (!strcmp(rg,"k0")){strcpy(recep,"11010");
	}		
		
	if (!strcmp(rg,"k1")){strcpy(recep,"11011");
	}		
		
	if (!strcmp(rg,"gp")){strcpy(recep,"11100");
	}		
		
	if (!strcmp(rg,"sp")){strcpy(recep,"11101");
	}		
		
	if (!strcmp(rg,"fp")){strcpy(recep,"11110");
	}		
	
	if (!strcmp(rg,"ra")){strcpy(recep,"11111");
	}
		
	
}

void ler_instrucoes(FILA_ENC *f,Lista *l1,int tamFila,Fourbytes *vet){
	char inst[MAX],aux[MAX];
	char instBIN[33],instHEXA[9]; // variavel que armazenará a instrução com 32 bits
	int c,e,instcount=0,PC=0;
	
	vet[0].H1[0]='b';
	
	for(e=0;e<tamFila;e++){	//LAÇO PARA PERCORRER A FILA DE INSTRUÇÕES
	char OP[7],RS[6]="00000",RT[6]="00000",RD[6]="00000",SHAMT[6]="00000",*FUNCT=(char*)malloc (sizeof(char)*7), IMM[17];  //variaveis que armazenarao registradores, operadores e etc
	char ADDR[27]="00000000000000000000000000";
	int temop=0,i=0,x=0,tipoI,tipoJ,tipoR;
	limparvetor(aux,300);
	tipoI=0; tipoJ=0; tipoR=0;
	strcpy(inst,consulta(*f)); //consulto e coloco em inst o elemento da fila
	ret(*f);				   //retiro o elemento da fila
	
	
	
	while (inst[i]!=' ' && inst[i]!=':'){ //pegar o operador ou o label percorrendo a linha
		if (inst[i]=='\n') break ; // vou parar se o elemento só tiver o '\n'
		aux[x]=inst[i];
		i++;
		x++;
	}
	
	if (inst[i]==':'){ // É LABEL

		while (inst[i+1]!='\n' && inst[i+1]!='\0'){
			if (inst[i+1]==' ' || inst[i+1]=='\t'){
			i++;
			}else {
			temop=1;
			goto TemOperador; //caso ainda tenha operador apos o label do arquivo, vai p lá
			}
		}
		
	}else { //É OPERADOR
		TemOperador: // a execucao desviará pra esse label caso haja um label e uma instrução na mesma linha
		
		if (temop){
			int f;
			x=0;
			limparvetor(aux,300);
				
			while (inst[i+1]!=' ' && inst[i+1]!='\t'){
				aux[x]=inst[i+1];
				i++;
				x++;
			}
		}
		
		FUNCT=operacao(aux,OP); //OP RECEBE O VALOR EM BINARIO DO OPERADOR QUE ESTA EM AUX E JÁ PASSO O VALOR DE FUNCT
		char aux2[5];
		int tipo_op=bin_dec(OP,sizeof (OP));
		Lista l2=*l1;
		int poslst;

//		printf ("%s",aux);
		switch (tipo_op){ //Verei se é do tipo R, I ou J -- transformei o bin em decimal pq switch só funciona com inteiros

		
/*Tipo R*/	case 0: // TIPO R: OP[6],RS[5],RT[5],RD[5],SHAMT[5],FUNCT[6]
				tipoR=1;
				if (!strcmp(aux,"jr")){
					while (inst[i]!='$') i++;
					for(c=0; c<2; c++){aux2[c]=inst[++i]; }
					aux2[c]='\0';
					registrador(aux2,RS);
					break ;
				}

				while (inst[i]!='$') i++;
				for(c=0; c<4 && inst[i+1]!=',' && inst[i+1]!=' ' && inst[i+1]!='\t'; c++){aux2[c]=inst[++i]; }
				aux2[c]='\0'; //garantindo o fim correto do vetor aux
				registrador(aux2,RD); 
				
				while (inst[i]!='$') i++;
				for(c=0; c<4 && inst[i+1]!=',' && inst[i+1]!=' ' && inst[i+1]!='\t'; c++){aux2[c]=inst[++i]; }
				aux2[c]='\0';
				registrador(aux2,RS);
				
				if (!strcmp(aux,"add") || !strcmp(aux,"sub") || !strcmp(aux,"and") || !strcmp(aux,"or") || !strcmp(aux,"xor") || !strcmp(aux,"slt")){
					while (inst[i]!='$') i++;
					for(c=0; c<4 && inst[i+1]!='\n' && inst[i+1]!='\0' && inst[i+1]!=' '; c++){aux2[c]=inst[++i]; }
					aux2[c]='\0';
					registrador(aux2,RT);
					
					
				}else { // é alguma inst de deslocamento então SHAMT terá valor
					while (inst[i]!=',') i++;
					while (inst[i+1]==' ' || inst[i+1]=='\t') i++;
					
					for(c=0; c<4 && inst[i+1]!=' ' && inst[i+1]!='\n' && inst[i+1]!='\0'; c++){aux2[c]=inst[++i]; }
					aux2[c]='\0';
					shamt(aux2,SHAMT);

					
				}

					break ;
					
/*func J*/	case 2:// TIPO J: OP[6], ADDR[26]
				tipoJ=1;
				x=0;
				limparvetor(aux,300);
				while (inst[i]==' ' || inst[i]=='j') i++;
				while (inst[i]!=' ' && inst[i]!='\n' && inst[i]!='\0'){
					aux[x]=inst[i];
					i++;
					x++;
				}

				poslst=consposlabel(l2,aux); //pega o posicao do label na lista

				if (poslst!=-1){ //ADDR VAI RECEBER O ENDEREÇO BASE DE MEMORIA MAIS O DO LABEL
					for (x=0; x<poslst-1; x++){
					l2=l2->prox;
					}
					dec_bin(l2->memorialabel,ADDR,26);
				}
			
				
					break ;
/*func Jal*/case 3:// TIPO J: OP[6], ADDR[26]
				tipoJ=1;
				x=0;
				
				limparvetor(aux,300); zerarvetor(RS,6); zerarvetor(RT,6);
				while (inst[i]==' ' || inst[i]=='j' || inst[i]=='a' || inst[i]=='l') i++;
				while (inst[i]!=' ' && inst[i]!='\n' && inst[i]!='\0'){
					aux[x]=inst[i];
					i++;
					x++;
				}

				poslst=consposlabel(l2,aux); //pega o posicao do label na lista

				if (poslst!=-1){ //ADDR VAI RECEBER O ENDEREÇO BASE DE MEMORIA MAIS O DO LABEL
					for (x=0; x<poslst-1; x++){
					l2=l2->prox;
					}
					dec_bin(l2->memorialabel,ADDR,26);
				}
					break ;
					
/*Tipo I*/	default :// TIPO I: OP[6], RS[5], RT[5], IMM[16] 
				tipoI=1;
				
				limparvetor(aux2,5); limparvetor(RS,6); limparvetor(RT,6);
   				x=0;
   				char aux3[6]; limparvetor(aux3,6);
   				char aux4[15]; limparvetor(aux4,15);
				int imediato;
   				
   				if (!strcmp(aux,"addi") || !strcmp(aux,"ori") || !strcmp(aux,"andi") || !strcmp(aux,"xori") || !strcmp(aux,"slti")){ //ex: OP $Rt,$Rs,IMM
					while (inst[i]!='$') i++;
					for(c=0; c<4 && inst[i+1]!=',' && inst[i+1]!=' ' && inst[i+1]!='\t'; c++){aux2[c]=inst[++i]; }
					aux2[c]='\0';
					registrador(aux2,RT);
				
					while (inst[i]!='$') i++;
					for(c=0; c<4 && inst[i+1]!=',' && inst[i+1]!=' ' && inst[i+1]!='\t'; c++){aux2[c]=inst[++i]; }
					aux2[c]='\0';
					registrador(aux2,RS);
	
					while (inst[i]!=',') i++;
					i++;
					while (inst[i]==' ' || inst[i]=='\t') i++;
					
					while (inst[i]!='\n' && inst[i]!=' ' && inst[i]!='\0'){
						aux3[x]=inst[i];
						x++;
						i++;
					}
					
					zerarvetor(IMM,17);
					imediato=atoi(aux3);
					dec_bin(imediato,IMM,16);
					
//					printf ("%s ",RS);
//					printf ("%s ",RT);
//					printf ("%s ",IMM);
				}else if (!strcmp(aux,"lw") || !strcmp(aux,"sw")){// ex: OP $Rt,IMM($Rs)
						while (inst[i]!='$') i++;
						for(c=0; c<4 && inst[i+1]!=',' && inst[i+1]!=' ' && inst[i+1]!='\t'; c++){aux2[c]=inst[++i]; }
						aux2[c]='\0';
						registrador(aux2,RT);
						
						while (inst[i]!=',') i++;
						i++;
						while (inst[i]==' ' || inst[i]=='\t') i++;
						
						while (inst[i]!='('){
							aux3[x]=inst[i];
							x++;
							i++;
						}
						zerarvetor(IMM,17);
						imediato=atoi(aux3);
						dec_bin(imediato,IMM,16);
						limparvetor(aux2,5); x=0;
						
						while (inst[i]=='$' || inst[i]=='(' )i++;
						while (inst[i]!=')') aux2[x++]=inst[i++];
						
						registrador(aux2,RS);
									

				}else if (!strcmp(aux,"beq") || !strcmp(aux,"bne")){// ex: OP $Rs,$Rt,label(label um nome que corresponde a um IMM)
						while (inst[i]!='$') i++;
						for(c=0; c<4 && inst[i+1]!=',' && inst[i+1]!=' ' && inst[i+1]!='\t'; c++){aux2[c]=inst[++i]; }
						aux2[c]='\0';
						registrador(aux2,RS);
						
						while (inst[i]!='$') i++;
						for(c=0; c<4 && inst[i+1]!=',' && inst[i+1]!=' ' && inst[i+1]!='\t'; c++){aux2[c]=inst[++i]; }
						aux2[c]='\0';
						registrador(aux2,RT);
		
						while (inst[i]!=',') i++;
						i++;
						while (inst[i]==' ' || inst[i]=='\t') i++;
						
						while (inst[i]!='\n' && inst[i]!=' ' && inst[i]!='\0'){
							aux4[x]=inst[i];
							x++;
							i++;
						}	
//						if (e==10) printf ("%s",aux4);
						poslst=consposlabel(*l1,aux4);
						
						if (poslst!=-1){ 
							for (x=0; x<poslst-1; x++){
							l2=l2->prox;
							}
//						printf ("%d",l2->memorialabel);
						imediato=l2->memorialabel;
//						if (e==10) printf ("%d",imediato);					
						zerarvetor(IMM,17);
//						printf ("%s",imediato);
						dec_bin(imediato,IMM,16);
//						
//if (e==10){printf ("%s",OP); printf ("%s",RS); printf ("%s",RT);  printf ("%s",IMM);}
						
						}	
				}else {
					while (inst[i]!='$') i++;
					for(c=0; c<4 && inst[i+1]!=',' && inst[i+1]!=' ' && inst[i+1]!='\t'; c++){aux2[c]=inst[++i]; }
					aux2[c]='\0';
					registrador(aux2,RT);
					
					strcpy(RS,"00000");
					
					while (inst[i]!=',') i++;
					i++;
					while (inst[i]==' ' || inst[i]=='\t') i++;
					
					while (inst[i]!='\n' && inst[i]!=' ' && inst[i]!='\0'){
						aux4[x]=inst[i];
						x++;
						i++;
					}
					
				zerarvetor(IMM,17);
				imediato=atoi(aux4);
				dec_bin(imediato,IMM,16);					

				}
					 break ;
		}
	instcount++;
	PC=instcount*4;
	}	
if (tipoI){
	limparvetor(instBIN,32); limparvetor(instHEXA,9);
	strcat(instBIN,OP);
	strcat(instBIN,RS);
	strcat(instBIN,RT);
	strcat(instBIN,IMM);
	bin32_hexa(instBIN,instHEXA);

		for (i=0; i<2; i++){
			vet[instcount-1].H1[i]=instHEXA[i];
		}
		for (i=2,x=0; i<4; i++,x++){
			vet[instcount-1].H2[x]=instHEXA[i];
		}
		for (i=4,x=0; i<6; i++,x++){
			vet[instcount-1].H3[x]=instHEXA[i];
		}
		for (i=6,x=0; i<8; i++,x++){
			vet[instcount-1].H4[x]=instHEXA[i];
		}

}else if (tipoJ){
	limparvetor(instBIN,32); limparvetor(instHEXA,9);
	strcat(instBIN,OP);
	strcat(instBIN,ADDR);
	bin32_hexa(instBIN,instHEXA);
	
		for (i=0; i<2; i++){
			vet[instcount-1].H1[i]=instHEXA[i];
		}
		for (i=2,x=0; i<4; i++,x++){
			vet[instcount-1].H2[x]=instHEXA[i];
		}
		for (i=4,x=0; i<6; i++,x++){
			vet[instcount-1].H3[x]=instHEXA[i];
		}
		for (i=6,x=0; i<8; i++,x++){
			vet[instcount-1].H4[x]=instHEXA[i];
		}

	
}else if (tipoR){
	limparvetor(instBIN,32); limparvetor(instHEXA,9);
	strcat(instBIN,OP);
	strcat(instBIN,RS);
	strcat(instBIN,RT);
	strcat(instBIN,RD);
	strcat(instBIN,SHAMT);
	strcat(instBIN,FUNCT);
	bin32_hexa(instBIN,instHEXA);
		
		for (i=0; i<2; i++){
			vet[instcount-1].H1[i]=instHEXA[i];
		}
		for (i=2,x=0; i<4; i++,x++){
			vet[instcount-1].H2[x]=instHEXA[i];
		}
		for (i=4,x=0; i<6; i++,x++){
			vet[instcount-1].H3[x]=instHEXA[i];
		}
		for (i=6,x=0; i<8; i++,x++){
			vet[instcount-1].H4[x]=instHEXA[i];
		}

	
}

}

}

void shamt(char *qtd, char *recep){

	if (!strcmp(qtd,"0")){strcpy(recep,"00000");
	}else

	if (!strcmp(qtd,"1")){strcpy(recep,"00001");
	}else

	if (!strcmp(qtd,"2")){strcpy(recep,"00010");
	}else

	if (!strcmp(qtd,"3")){strcpy(recep,"00011");
	}else

	if (!strcmp(qtd,"4")){strcpy(recep,"00100");
	}else

	if (!strcmp(qtd,"5")){strcpy(recep,"00101");
	}else

	if (!strcmp(qtd,"6")){strcpy(recep,"00110");
	}else

	if (!strcmp(qtd,"7")){strcpy(recep,"00111");
	}else

	if (!strcmp(qtd,"8")) {strcpy(recep,"01000");
	}else

	if (!strcmp(qtd,"9")){strcpy(recep,"01001");
	}else

	if (!strcmp(qtd,"10")) {strcpy(recep,"01010");
	}else

	if (!strcmp(qtd,"11")){strcpy(recep,"01011");
	}else

	if (!strcmp(qtd,"12")){strcpy(recep,"01100");
	}else

	if (!strcmp(qtd,"13")){strcpy(recep,"01101");
	}else

	if (!strcmp(qtd,"14")){strcpy(recep,"01110");
	}else

	if (!strcmp(qtd,"15")){strcpy(recep,"01111");
	}else

	if (!strcmp(qtd,"16")){strcpy(recep,"10000");
	}else

	if (!strcmp(qtd,"17")){strcpy(recep,"10001");
	}else

	if (!strcmp(qtd,"18")){strcpy(recep,"10010");
	}else

	if (!strcmp(qtd,"19")){strcpy(recep,"10011");
	}else

	if (!strcmp(qtd,"20")){strcpy(recep,"10100");
	}else

	if (!strcmp(qtd,"21")){strcpy(recep,"10101");
	}else

	if (!strcmp(qtd,"22")){strcpy(recep,"10110");
	}else

	if (!strcmp(qtd,"23")){strcpy(recep,"10111");
	}else

	if (!strcmp(qtd,"24")){strcpy(recep,"11000");
	}else

	if (!strcmp(qtd,"25")){strcpy(recep,"11001");
	}else

	if (!strcmp(qtd,"26")){strcpy(recep,"11010");
	}else

	if (!strcmp(qtd,"27")){strcpy(recep,"11011");
	}else

	if (!strcmp(qtd,"28")){strcpy(recep,"11000");
	}else

	if (!strcmp(qtd,"29")){strcpy(recep,"11101");
	}else

	if (!strcmp(qtd,"30")){strcpy(recep,"11110");
	}else

	if (!strcmp(qtd,"31")){strcpy(recep,"11111");
	}else 
		strcpy(recep,"00000");
}

void limparvetor(char *vet,int tam){
	int i=0;
	for (i=0; i<tam; i++){
		vet[i]='\0';
	}
}

void zerarvetor(char *vet,int tam){
	int i;
	tam-=1;
	for (i=0; i<tam; i++){
		vet[i]='0';
	}
	vet[i]='\0';
}

void dec_bin(int dec, char *recep,int tamanhovet){ //decimal para binario com complemento de 2
	int i,x,aux=dec,tam=tamanhovet;
	tam=tam-1;

//	printf ("%s",recep);
	 //se for negativo vou ter q fazer comp de 2, daí já somo um ao negativo
	
	for (aux=dec,i=0 ; aux/2!=0 ;i++){
	aux=aux/2;
	}
//	printf ("%d",-9%2);
	i++;
	aux=dec;
	
	if (dec<0) aux+=1;
	
	while (i){
		if ((aux % 2)==0){
			recep[tam]='0';
	
		}else {
			recep[tam]='1';
		}
		i--;
		tam--;
		aux/=2;
	}
	if (dec<0){
	for (i=0; i<tamanhovet; i++){
	recep[i]= recep[i]=='0' ? '1' : '0';
		
	}
}

}

void bin32_hexa(char *bin, char *recep){//binario de 32 bits para hexadecimal de 8 hexas
	int i,j,c;
	char aux[5];
	
	for (i=0; i<8; i++){
		for (j=i*4,c=0; j<(i*4)+4; j++,c++){
			aux[c]=bin[j];
 
	}
	
	if (!strcmp(aux,"0000")){recep[i]='0';	
	}else if (!strcmp(aux,"0001")){recep[i]='1';
	}else if (!strcmp(aux,"0010")){recep[i]='2';
	}else if (!strcmp(aux,"0011")){recep[i]='3';
	}else if (!strcmp(aux,"0100")){recep[i]='4';
	}else if (!strcmp(aux,"0101")){recep[i]='5';
	}else if (!strcmp(aux,"0110")){recep[i]='6';
	}else if (!strcmp(aux,"0111")){recep[i]='7';
	}else if (!strcmp(aux,"1000")){recep[i]='8';
	}else if (!strcmp(aux,"1001")){recep[i]='9';
	}else if (!strcmp(aux,"1010")){recep[i]='A';
	}else if (!strcmp(aux,"1011")){recep[i]='B';
	}else if (!strcmp(aux,"1100")){recep[i]='C';
	}else if (!strcmp(aux,"1101")){recep[i]='D';
	}else if (!strcmp(aux,"1110")){recep[i]='E';
	}else if (!strcmp(aux,"1111")){recep[i]='F';
	}
	}
}

void bin12_hexa(char *bin, char *recep){
	int i,j,c;
	char aux[5];
	limparvetor(aux,4);
	
	for (i=0; i<3; i++){
		for (j=i*4,c=0; j<(i*4)+4; j++,c++){
			aux[c]=bin[j];
//			printf ("%s ",bin);
	}
	
	if (!strcmp(aux,"0000")){recep[i]='0';	
	}else if (!strcmp(aux,"0001")){recep[i]='1';
	}else if (!strcmp(aux,"0010")){recep[i]='2';
	}else if (!strcmp(aux,"0011")){recep[i]='3';
	}else if (!strcmp(aux,"0100")){recep[i]='4';
	}else if (!strcmp(aux,"0101")){recep[i]='5';
	}else if (!strcmp(aux,"0110")){recep[i]='6';
	}else if (!strcmp(aux,"0111")){recep[i]='7';
	}else if (!strcmp(aux,"1000")){recep[i]='8';
	}else if (!strcmp(aux,"1001")){recep[i]='9';
	}else if (!strcmp(aux,"1010")){recep[i]='A';
	}else if (!strcmp(aux,"1011")){recep[i]='B';
	}else if (!strcmp(aux,"1100")){recep[i]='C';
	}else if (!strcmp(aux,"1101")){recep[i]='D';
	}else if (!strcmp(aux,"1110")){recep[i]='E';
	}else if (!strcmp(aux,"1111")){recep[i]='F';
	}
	}
}
