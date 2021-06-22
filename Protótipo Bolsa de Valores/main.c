#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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

typedef struct{
	float value;
	int qtd;
	char name[6];
}Share;

Compra* listaCompra(){return NULL;}
Venda* listaVenda(){return NULL;}

Compra* insertCompra(Compra* inicio, float price, char nome[6], int lote){
	Compra* newCompra = (Compra*) malloc(sizeof(Compra));
	strcpy(newCompra->nome,nome);
	newCompra->price = price;
	newCompra->lote = lote;
	newCompra->nextCompra = inicio;
	newCompra->status = 1;
	return newCompra;
}

Venda* insertVenda(Venda* inicio, float price, char nome[6], int lote){
	Venda* newVenda = (Venda*) malloc(sizeof(Venda));
	strcpy(newVenda->nome,nome);
	newVenda->price = price;
	newVenda->lote = lote;
	newVenda->nextVenda = inicio;
	newVenda->status = 1;
	return newVenda;
}

void printCompras(Compra* compras){
	
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
	printf("\nC�digo do ativo | Valor do ativo  | Quantidade dispon�vel");
	for(base = compras; base != NULL; base = base->nextCompra){
		if(base->status != 0){
			printf("\n     %s      |", base->nome);
			printf("       %.2f     |",base->price);	
			printf("        %d",       base->lote);
			
		}	
	}
}

void printVendas(Venda* vendas){
	
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
	printf("\nC�digo do ativo | Valor do ativo  | Quantidade dispon�vel");
	for(base=vendas; base!=NULL; base=base->nextVenda){
		if(base->status != 0){
			printf("\n     %s      |", base->nome);
			printf("       %.2f     |",base->price);	
			printf("        %d",       base->lote);
			
		}	
	}
}

void transaction(Venda* venda, Compra* compra){
	Venda* auxVenda = venda;	
	Compra* auxCompra = compra;

	for(auxVenda ; auxVenda != NULL; auxVenda = auxVenda->nextVenda){
		for(auxCompra ; auxCompra != NULL; auxCompra = auxCompra->nextCompra){
			
			if( ( strcmp(auxCompra->nome,auxVenda->nome) == 0 ) && (auxVenda->status == 1 ) && (auxCompra->status == 1 ) && (auxVenda->price <= auxCompra->price ) ){
				
				if( auxVenda->lote < auxCompra->lote ){
					auxVenda->status = 0;
					auxCompra->lote = auxCompra->lote - auxVenda->lote;
					auxVenda->lote = 0;
					
				}
				
				else if( auxVenda->lote > auxCompra->lote ){
					auxCompra->status = 0;
					auxVenda->lote = auxVenda->lote - auxCompra->lote ;
					auxCompra->lote = 0;
					
				}
				
				else{
					auxVenda->status = 0;
					auxVenda->lote = 0;
					auxCompra->status = 0;
					auxCompra->lote = 0;					
				}
				
				//compra = auxCompra;
				//venda = auxVenda;
				
				if( strcmp( "BBAS3" , auxVenda->nome) == 0 ){
					FILE *pont_arq;
					pont_arq = fopen("cotaBBAS3.txt", "w");
					fprintf(pont_arq, "BBAS3 %.2f", auxVenda->price);
					fclose(pont_arq);
				}
				if( strcmp( "ITUB4" , auxVenda->nome) == 0 ){
					FILE *pont_arq;
					pont_arq = fopen("cotaITUB4.txt", "w");
					fprintf(pont_arq, "ITUB4 %.2f", auxVenda->price);
					fclose(pont_arq);
				}
				if( strcmp( "BBDC4" , auxVenda->nome) == 0 ){
					FILE *pont_arq;
					pont_arq = fopen("cotaBBDC4.txt", "w");
					fprintf(pont_arq, "BBDC4 %.2f", auxVenda->price);
					fclose(pont_arq);
				}
				if( strcmp( "BIDI3" , auxVenda->nome) == 0 ){
					FILE *pont_arq;
					pont_arq = fopen("cotaBIDI3.txt", "w");
					fprintf(pont_arq, "BIDI3 %.2f", auxVenda->price);
					fclose(pont_arq);
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
    	//printf("%.2f %d %s", valor, qtd, name);
    	//printf("\n");    	
    	i++;
	}
    fclose(f);
    //printf("%d\n", i);
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
    	//printf("%.2f %d %s", valor, qtd, name);
    	//printf("\n");    	
    	i++;
	}
    fclose(f);
    //printf("%d\n", i);
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
    	//printf("%.2f %d %s", valor, qtd, name);
    	//printf("\n");
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
    	//printf("%.2f %d %s", valor, qtd, name);
    	//printf("\n");
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
	int na = 0;
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
	pont_arq = fopen("teste.txt", "w");

	for(base = compras; base != NULL; base = base->nextCompra){
		if(base->status != 0){
			fprintf(pont_arq, "%.2f ", base->price);
			fprintf(pont_arq, "%d ", base->lote);
			fprintf(pont_arq, "%s\n", base->nome);
		}	
	}	
	
	///*
	fclose(pont_arq);		
	//*/
	
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
	///*
	int x = conta_Compras();
	float price1[x];
    int lote1[x];
    char name1[x][6];
    carrega_Compras(price1, lote1, name1, x);
    for(i=0; i<x; i++){
    	compra = insertCompra(compra,price1[i],name1[i],lote1[i]);}	
    	
    int y = conta_Vendas();
	float price2[y];
    int lote2[y];
    char name2[y][6];		
    carrega_Vendas(price2, lote2, name2, y);
    for(j=0; j<y; j++){
    	venda = insertVenda(venda,price2[j],name2[j],lote2[j]);}	
   	//*/
    
    
    
	printf("---------------------------------------");
	printf("\n            Isello's Broker");
	printf("\n---------------------------------------");
	printf("\n");
	///*
	printf("\n1 - Exibir ordens de venda");
	printf("\n2 - Exibir ordens de compra");				
	printf("\n3 - Criar ordem de venda");
	printf("\n4 - Criar ordem de compra");				
	printf("\n5 - Ver cotacoes atuais");
	printf("\n6 - Limpar tela");
	printf("\n0 - Sair");
	//*/
	while(option != 0){
		
		transaction(venda, compra);
		printf("\n");
		printf("\nInforme a opcao desejada ou digite 7 para mostrar as op��es dispon�veis: ");
		scanf("%d",&option);
		
		switch(option){
		
			case 1:
				printf("\n---------------------------------------");
				printf("\n----- Ordens de Venda -----");
				printf("\n---------------------------------------");
				printf("\n");
				printVendas(venda);
			break;
			
			case 2:
				printf("\n---------------------------------------");
				printf("\n----- Ordens de Compra -----");
				printf("\n---------------------------------------");
				printf("\n");
				printCompras(compra);
			break;
			
			case 3:
				printf("\n---------------------------------------");
				printf("\n----- Operacao de Venda -----");
				printf("\n---------------------------------------");
				printf("\n");
				printf("\nInforme o titulo que deseja vender: ");
				scanf("%s",&papel);
				printf("\nQuantidade que deseja vender: ");
				scanf("%d",&lote);				
				printf("\nPre�o de venda do papel: ");
				scanf("%f",&price);
				venda = insertVenda(venda,price,papel,lote);
				transaction(venda, compra);
			break;
			
			case 4:
				printf("\n---------------------------------------");
				printf("\n----- Operacao de Compra -----");
				printf("\n---------------------------------------");
				printf("\n");
				printf("\nInforme o titulo que deseja comprar: ");
				scanf("%s",&papel);
				printf("\nQuantidade que deseja comprar: ");
				scanf("%d",&lote);				
				printf("\nPre�o de compra do papel: ");
				scanf("%f",&price);
				compra = insertCompra(compra,price,papel,lote);
				transaction(venda, compra);
			break;
			
			case 5:
				printf("\n---------------------------------------");
				printf("\n----- Cota��es -----");
				printf("\n---------------------------------------");
				printf("\n");
				print_Cota();		
			break;
			
			case 6:
				system("cls");
			break;
						
			case 7:
				printf("\n1 - Exibir ordens de venda");
				printf("\n2 - Exibir ordens de compra");				
				printf("\n3 - Adicionar uma ordem de venda");
				printf("\n4 - Adicionar uma ordem de compra");				
				printf("\n5 - Ver cotacoes atuais");
				printf("\n6 - Limpar dados da tela");
				printf("\n0 - Sair");								
				
			break;
			
			case 0:
			guardar_OrdensCompra(compra);
			break;
			
			default:
				
				printf("\nEscolha uma op��o v�lida.");
				
			break;
		}
	}
	printf("\nVoc� saiu.");
	return 0;
}
