#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nome[6];
	float price;
	int lote;
	int status;
	struct Compra* nextCompra;
}Compra;

typedef struct{
	char nome[6];
	float price;
	int lote;
	int status;
	struct Venda* nextVenda;
}Venda;

Compra* listaCompra(){return NULL;}
Venda* listaVenda(){return NULL;}

Compra* insert_Compra(Compra* inicio, float price, char nome[6], int lote){
	Compra* newCompra = (Compra*) malloc(sizeof(Compra));
	strcpy(newCompra->nome,nome);
	newCompra->price = price;
	newCompra->lote = lote;
	newCompra->nextCompra = inicio;
	newCompra->status = 1;
	return newCompra;
}

Venda* insert_Venda(Venda* inicio, float price, char nome[6], int lote){
	Venda* newVenda = (Venda*) malloc(sizeof(Venda));
	strcpy(newVenda->nome,nome);
	newVenda->price = price;
	newVenda->lote = lote;
	newVenda->nextVenda = inicio;
	newVenda->status = 1;
	return newVenda;
}

void print_Compras(Compra* compras){
	
	Compra* auxilia = (Compra*)malloc(sizeof(Compra));
	Compra* troca = (Compra*)malloc(sizeof(Compra));
	Compra* base;

	for(base = compras; base != NULL; base = base->nextCompra){
		
		auxilia = base->nextCompra;
		
		if(auxilia != NULL){		
			if(base->price > auxilia->price){
			troca->price = base->price;
			troca->lote = base->lote;
			strcpy(troca->nome,base->nome);
			troca->status = base->status;
			base->price = auxilia->price;
			base->lote = auxilia->lote;
			strcpy(base->nome,auxilia->nome);
			base->status = auxilia->status;
			auxilia->price = troca->price;
			auxilia->lote = troca->lote;
			strcpy(auxilia->nome,troca->nome);
			auxilia->status = troca->status;
			base = compras;
		}	
	}	
}
	printf("\nCódigo do ativo | Valor do ativo  | Quantidade disponível");
	for(base = compras; base != NULL; base = base->nextCompra){
		if(base->status != 0){
			printf("\n     %s      |", base->nome);
			printf("       %.2f     |",base->price);	
			printf("        %d",       base->lote);
			
		}	
	}
}

void print_Vendas(Venda* vendas){
	
	Venda* auxilia = (Venda*)malloc(sizeof(Venda));
	Venda* troca = (Venda*)malloc(sizeof(Venda));
	Venda* base;

	for(base = vendas; base != NULL; base = base->nextVenda){
		
		auxilia = base->nextVenda;
		
		if(auxilia != NULL){		
			if(base->price > auxilia->price){
			troca->price = base->price;
			troca->lote = base->lote;
			strcpy(troca->nome,base->nome);
			troca->status = base->status;
			
			base->price = auxilia->price;
			base->lote = auxilia->lote;
			strcpy(base->nome,auxilia->nome);
			base->status = auxilia->status;
			
			auxilia->price = troca->price;
			auxilia->lote = troca->lote;
			strcpy(auxilia->nome,troca->nome);
			auxilia->status = troca->status;
			base = vendas;
		}	
	}	
}
	printf("\nCódigo do ativo | Valor do ativo  | Quantidade disponível");
	for(base=vendas; base!=NULL; base=base->nextVenda){
		if(base->status != 0){
			printf("\n     %s      |", base->nome);
			printf("       %.2f     |",base->price);	
			printf("        %d",       base->lote);
			
		}	
	}
}

void transaction1(Venda* venda, Compra* compra){
	int k=0;
	float x=0;
	//Venda* auxVenda = venda;
	Venda* auxVenda;	
	//Compra* auxCompra = compra;
	Compra* auxCompra;
	
	for(auxCompra=compra ; auxCompra != NULL; auxCompra = auxCompra->nextCompra){
		for(auxVenda=venda ; auxVenda != NULL; auxVenda = auxVenda->nextVenda){
			
			if((strcmp(auxCompra->nome,auxVenda->nome) == 0 ) && (auxVenda->status == 1 ) && (auxCompra->status == 1) && (auxVenda->price <= auxCompra->price )){
				
				if( auxVenda->lote < auxCompra->lote ){
					k = auxVenda->lote;
					auxVenda->status = 0;
					auxCompra->lote = auxCompra->lote - auxVenda->lote;
					auxVenda->lote = 0;
				}
				
				else if( auxVenda->lote > auxCompra->lote ){
					k = auxCompra->lote;
					auxCompra->status = 0;
					auxVenda->lote = auxVenda->lote - auxCompra->lote ;
					auxCompra->lote = 0;
				}
				
				else{
					k = auxVenda->lote;
					auxVenda->status = 0;
					auxVenda->lote = 0;
					auxCompra->status = 0;
					auxCompra->lote = 0;					
				}
				
				if (auxVenda->price < auxCompra->price){
					x = (auxCompra->price - auxVenda->price)/2 + auxVenda->price;
				}else{
					x = auxVenda->price;
				}
				
				printf("\n\nOrdem executada!\n");
				printf("%d unidades do papel %s foram negociados por R$%.2f cada.", k, auxCompra->nome, x);
				//guarda_Cota(auxCompra->nome, x);
				//guardar_Transactions( auxCompra->nome, k, x);
				
				
				if( strcmp( "BBAS3" , auxVenda->nome) == 0 ){
					FILE *pont_arq;
					pont_arq = fopen("cotaBBAS3.txt", "w");
					fprintf(pont_arq, "BBAS3 %.2f", x);
					fclose(pont_arq);
					
					FILE *pont_arq1;
					pont_arq1 = fopen("transactions.txt", "a");
					fprintf(pont_arq1, "%s %d %.2f \n", auxCompra->nome, k, x);
					fclose(pont_arq1);
				}
				
				if( strcmp( "ITUB4" , auxVenda->nome) == 0 ){
					FILE *pont_arq;
					pont_arq = fopen("cotaITUB4.txt", "w");
					fprintf(pont_arq, "ITUB4 %.2f", x);
					fclose(pont_arq);
					FILE *pont_arq1;
					pont_arq1 = fopen("transactions.txt", "a");
					fprintf(pont_arq1, "%s %d %.2f \n", auxCompra->nome, k, x);
					fclose(pont_arq1);					
				}
				
				if( strcmp( "BBDC4" , auxVenda->nome) == 0 ){
					FILE *pont_arq;
					pont_arq = fopen("cotaBBDC4.txt", "w");
					fprintf(pont_arq, "BBDC4 %.2f", x);
					fclose(pont_arq);
					FILE *pont_arq1;
					pont_arq1 = fopen("transactions.txt", "a");
					fprintf(pont_arq1, "%s %d %.2f \n", auxCompra->nome, k, x);
					fclose(pont_arq1);					
				}
				
				if( strcmp( "BIDI3" , auxVenda->nome) == 0 ){
					FILE *pont_arq;
					pont_arq = fopen("cotaBIDI3.txt", "w");
					fprintf(pont_arq, "BIDI3 %.2f", x);
					fclose(pont_arq);
					FILE *pont_arq1;
					pont_arq1 = fopen("transactions.txt", "a");
					fprintf(pont_arq1, "%s %d %.2f \n", auxCompra->nome, k, x);
					fclose(pont_arq1);					
				}	
																										
			}
		}
	}
}


int conta_Compras() {  
    FILE *f;
    int i = 0;
    int qtd;
    float valor;
    char name[6];
    f = fopen ("ofertasCompras.txt", "rt");

    if (f == NULL) {
        printf ("Problema na abertura do arquivo");
        return;
    }

    while ( fscanf( f, "%f %d %s", &valor, &qtd, name) != EOF ){   	
    	i++;
	}
    fclose(f);
    return i;
}

int conta_Vendas() {  
    FILE *f;
    int i = 0;
    int qtd;
    float valor;
    char name[6];
    f = fopen ("ofertasVendas.txt", "rt");

    if (f == NULL) {
        printf ("Problema na abertura do arquivo");
        return;
    }

    while ( fscanf( f, "%f %d %s", &valor, &qtd, name) != EOF ){    	
    	i++;
	}
    fclose(f);
    return i;
}

void carrega_Compras(float *price, int *lote, char nome[][6], int conta) {  
    FILE *f;
    int i = 0;
    int qtd;
    float valor;
    char name[6];
    
    f = fopen ("ofertasCompras.txt", "rt");

    if (f == NULL) {
        printf ("Problema na abertura do arquivo");
        return;
    }

    while ( fscanf( f, "%f %d %s", &valor, &qtd, name) != EOF && i<conta ){
    	price[i] = valor;
    	lote[i] = qtd;
    	strcpy(nome[i],name);
    	i++;
	}
    fclose(f);
}

void carrega_Vendas(float *price, int *lote, char nome[][6], int conta) {  
    FILE *g;
    int i = 0;
    int qtd;
    float valor;
    char name[6];
    
    g = fopen ("ofertasVendas.txt", "rt");

    if (g == NULL) {
        printf ("Problema na abertura do arquivo");
        return;
    }

    while ( fscanf( g, "%f %d %s", &valor, &qtd, name) != EOF && i<conta ){
    	price[i] = valor;
    	lote[i] = qtd;
    	strcpy(nome[i],name);
    	i++;
	}
    fclose(g);
}

void print_Cota(){
	
	FILE *pont_arq;
	char texto_str[20];
	pont_arq = fopen("cotaBBAS3.txt", "r");
	while(fgets(texto_str, 20, pont_arq) != NULL)
	printf("%s\n", texto_str);
	fclose(pont_arq);
	
	FILE *pont_arq1;
	pont_arq1 = fopen("cotaBBDC4.txt", "r");
	while(fgets(texto_str, 20, pont_arq1) != NULL)
	printf("%s\n", texto_str);
	fclose(pont_arq1);	
	
	FILE *pont_arq2;
	pont_arq2 = fopen("cotaBIDI3.txt", "r");
	while(fgets(texto_str, 20, pont_arq2) != NULL)
	printf("%s\n", texto_str);
	fclose(pont_arq2);		
	
	FILE *pont_arq3;
	pont_arq3 = fopen("cotaITUB4.txt", "r");
	while(fgets(texto_str, 20, pont_arq3) != NULL)
	printf("%s\n", texto_str);
	fclose(pont_arq3);	
}

void guardar_OrdensCompra(Compra *compras){
	Compra* auxilia = (Compra*)malloc(sizeof(Compra));
	Compra* troca = (Compra*)malloc(sizeof(Compra));
	Compra* base;

	for(base = compras; base != NULL; base = base->nextCompra){
		auxilia = base->nextCompra;
		
		if(auxilia != NULL){
				
			if(base->price > auxilia->price){
			troca->price = base->price;
			troca->lote = base->lote;
			strcpy(troca->nome,base->nome);
			troca->status = base->status;
			base->price = auxilia->price;
			base->lote = auxilia->lote;
			strcpy(base->nome,auxilia->nome);
			base->status = auxilia->status;
			auxilia->price = troca->price;
			auxilia->lote = troca->lote;
			strcpy(auxilia->nome,troca->nome);
			auxilia->status = troca->status;
			base = compras;
			}	
	    }	
	}
	
	FILE *pont_arq;
	pont_arq = fopen("ofertasCompras.txt", "w");

	for(base = compras; base != NULL; base = base->nextCompra){
		if(base->status != 0){
			fprintf(pont_arq, "%.2f ", base->price);
			fprintf(pont_arq, "%d ", base->lote);
			fprintf(pont_arq, "%s\n", base->nome);
		}	
	}	
	fclose(pont_arq);		
}

void guardar_OrdensVenda(Venda *vendas){
	Venda* auxilia = (Venda*)malloc(sizeof(Venda));
	Venda* troca = (Venda*)malloc(sizeof(Venda));
	Venda* base;

	for(base = vendas; base != NULL; base = base->nextVenda){
		auxilia = base->nextVenda;
		
		if(auxilia != NULL){
				
			if(base->price > auxilia->price){
			troca->price = base->price;
			troca->lote = base->lote;
			strcpy(troca->nome,base->nome);
			troca->status = base->status;
			base->price = auxilia->price;
			base->lote = auxilia->lote;
			strcpy(base->nome,auxilia->nome);
			base->status = auxilia->status;
			auxilia->price = troca->price;
			auxilia->lote = troca->lote;
			strcpy(auxilia->nome,troca->nome);
			auxilia->status = troca->status;
			base = vendas;
			}	
	    }	
	}
	
	FILE *pont_arq;
	pont_arq = fopen("ofertasVendas.txt", "w");

	for(base = vendas; base != NULL; base = base->nextVenda){
		if(base->status != 0){
			fprintf(pont_arq, "%.2f ", base->price);
			fprintf(pont_arq, "%d ", base->lote);
			fprintf(pont_arq, "%s\n", base->nome);
		}	
	}	
	fclose(pont_arq);		
}

void guardar_Transactions( char name[], int lote, float x){
	//
	FILE *pont_arq;
	
	pont_arq = fopen("transactions.txt", "a");
	
	fprintf(pont_arq, "%s %d %f \n", name, lote, x);
	
	fclose(pont_arq);
  
}

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	int option=7;
	int i;
	int j;
	char papel[6];
	int lote;
	float price;	
	Venda* venda;
	Compra* compra;
	venda = listaVenda();
	compra = listaCompra();
	
	int x = conta_Compras();
	float price1[x];
    int lote1[x];
    char name1[x][6];
    carrega_Compras(price1, lote1, name1, x);
    for(i=0; i<x; i++){
    	compra = insert_Compra(compra,price1[i],name1[i],lote1[i]);}	
    	
    int y = conta_Vendas();
	float price2[y];
    int lote2[y];
    char name2[y][6];		
    carrega_Vendas(price2, lote2, name2, y);
    for(j=0; j<y; j++){
    	venda = insert_Venda(venda,price2[j],name2[j],lote2[j]);}
	
	//print_Vendas(venda);
	//print_Compras(compra);			
    
	printf("---------------------------------------");
	printf("\n     ----- Isello's Broker -----");
	printf("\n---------------------------------------");
	printf("\n");
	///*
	printf("\n1 - Exibir ordens de venda");
	printf("\n2 - Exibir ordens de compra");				
	printf("\n3 - Criar ordem de venda");
	printf("\n4 - Criar ordem de compra");				
	printf("\n5 - Ver cotações atuais");
	printf("\n0 - Sair");

	//*/
	while(option != 0){
		transaction1(venda, compra);
		
		printf("\n");
		printf("\nInforme a opção desejada ou digite 9 para voltar ao início: ");
		scanf("%d",&option);
		
		switch(option){
			transaction1(venda, compra);

		
			case 1:
				printf("\n---------------------------------------");
				printf("\n----- Ordens de Venda -----");
				printf("\n---------------------------------------");
				printf("\n");
				transaction1(venda, compra);
					
				print_Vendas(venda);
			break;
			
			case 2:
				printf("\n---------------------------------------");
				printf("\n----- Ordens de Compra -----");
				printf("\n---------------------------------------");
				printf("\n");
				transaction1(venda, compra);			
				print_Compras(compra);
			break;
			
			case 3:
				printf("\n---------------------------------------");
				printf("\n----- Operação de Venda -----");
				printf("\n---------------------------------------");
				printf("\n");
				printf("\nInforme a ação que deseja vender: ");
				scanf("%s",&papel);
				printf("\nQuantidade que deseja vender: ");
				scanf("%d",&lote);				
				printf("\nPreço de venda da ação: ");
				scanf("%f",&price);
				venda = insert_Venda(venda,price,papel,lote);
				transaction1(venda, compra);
			
			break;
			
			case 4:
				printf("\n---------------------------------------");
				printf("\n----- Operação de Compra -----");
				printf("\n---------------------------------------");
				printf("\n");
				printf("\nInforme a ação que deseja comprar: ");
				scanf("%s",&papel);
				printf("\nQuantidade que deseja comprar: ");
				scanf("%d",&lote);				
				printf("\nPreço de compra da ação: ");
				scanf("%f",&price);
				compra = insert_Compra(compra,price,papel,lote);
				transaction1(venda, compra);
			break;
			
			case 5:
				printf("\n---------------------------------------");
				printf("\n----- Cotações -----");
				printf("\n---------------------------------------");
				printf("\n");
				print_Cota();		
			break;
		
			case 9:
				system("cls");
				printf("---------------------------------------");
				printf("\n     ----- Isello's Broker -----");
				printf("\n---------------------------------------");
				printf("\n");
				printf("\n1 - Exibir ordens de venda");
				printf("\n2 - Exibir ordens de compra");				
				printf("\n3 - Adicionar uma ordem de venda");
				printf("\n4 - Adicionar uma ordem de compra");				
				printf("\n5 - Ver cotações atuais");
				printf("\n9 - Limpar dados da tela");
				printf("\n0 - Sair");								
				
			break;
			
			case 0:
			guardar_OrdensCompra(compra);
			guardar_OrdensVenda(venda);
			break;
			
			default:
				
				printf("\nEscolha uma opção válida.");
				
			break;
		}
	}
	printf("\nVocê saiu.");
	return 0;
}

