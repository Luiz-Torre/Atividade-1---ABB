#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

arvore *LerArvore(FILE *arq);
void ImprimirPreOrdem(arvore *a);
void ImprimirOrdem(arvore *a);
void ImprimirPosOrdem(arvore *a);
void ImprimirLargura(arvore *a, int aux, int nivel);
int CalcAltura (arvore *a);
int VerificaExistencia(arvore *a, int valor_desejado);


int main(){
    FILE * arq;
    int op;
    int valor_desejado, verifica, altura,aux_balanceada, aux_cheia, num_no;
    char nome_arquivo[50];
    while (op!= 8)
    {    
    
    printf("\n\nO que você deseja fazer? Digite: \n1- Para ler a arvore de um arquivo\n2-Para imprimir a arvore.\n3- Verificar se um elemento existe na arvore\n4-Imprimir o Nivel de Um no\n5-Imprimir as folhas menores que um valor\n6-Inserir um no X na arvore\n7-Remover um no X da arvore\n8-Sair\n");
    scanf("%d",&op);

    switch (op)
    {
    case 1:
        puts("Informe o nome do arquivo a ser lido");
        scanf("%s", nome_arquivo);
        arq = fopen(nome_arquivo, "rt");
        if (arq == NULL)
        {
            printf("Erro ao criar o arquivo\n");
            return 1;
        }
        arvore *a ;
        a = LerArvore(arq);
        fclose(arq);
        break;
    
    case 2:
        printf("\nImpressão Pre ordem: \n");
        ImprimirPreOrdem(a);
        printf("\n\nImpressão em ordem: \n");
        ImprimirOrdem(a);
        printf("\n\nImpressão pós ordem: \n");
        ImprimirPosOrdem(a);
        altura = CalcAltura(a);
        printf("\n\nImpressão em largura: \n");
        for (int nivel = 0; nivel < altura; nivel++){
            printf("Nivel %d : ", nivel);
            ImprimirLargura(a, 0, nivel);
            printf("\n"); 
        }
        break;
    case 3:
        puts("Informe o elemento que deseja saber existencia");
        scanf("%d", &valor_desejado);
        verifica = VerificaExistencia(a, valor_desejado);
        if(verifica ==1){
            printf("O numero existe");
        }
        else{
            printf("O numero não existe");
        }
    case 9:
        break;
    default:
        printf ("Valor invalido!\n");
    }
   
    }
    return 0;
}

arvore *LerArvore(FILE *arq){
    char c;
    int num;
    arvore *a;
    a = NULL;
    fscanf(arq,"%c",&c);
    fscanf(arq,"%d",&num);

    if(num==-1){
        fscanf(arq,"%c",&c);
        return NULL;
    }

    else{
        a = (arvore*)malloc(sizeof(arvore));
        a->info= num;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq,"%c",&c);
        

        return a;

    }
}

void ImprimirPreOrdem(arvore *a){
     if(a!=NULL){
         printf("%d ",a->info);
         ImprimirPreOrdem(a->esq);
         ImprimirPreOrdem(a->dir);
     }
 }
void ImprimirOrdem(arvore *a){
     if(a!=NULL){
        ImprimirPreOrdem(a->esq);
        printf("%d ",a->info);
        ImprimirPreOrdem(a->dir);
     }
 }

 void ImprimirPosOrdem(arvore *a){
     if(a!=NULL){
        ImprimirPreOrdem(a->esq);
        ImprimirPreOrdem(a->dir);
        printf("%d ",a->info);

     }
 }
 void ImprimirLargura(arvore *a, int aux, int nivel){

     if(a!=NULL){
    if (aux == nivel)
      printf("%d ", a -> info);
    else{
      ImprimirLargura(a -> esq, aux + 1, nivel);
      ImprimirLargura(a -> dir, aux + 1, nivel);}
  }
}
    

int CalcAltura (arvore *a){
	int altura_direita = 0, altura_esquerda = 0;

	if(a == NULL){
        return 0;
    }
	else{
		altura_esquerda = CalcAltura(a->esq);
		altura_direita = CalcAltura(a->dir);
		
    if (altura_esquerda>altura_direita){
        return altura_esquerda + 1;
    }
		else{
            return altura_direita + 1;     
        } 
	}
}

int VerificaExistencia(arvore *a, int valor_desejado){
    if (a != NULL){

        if(valor_desejado>a->info){

        VerificaExistencia(a->dir,valor_desejado);
    }
        if(valor_desejado<a->info){
            VerificaExistencia(a->esq,valor_desejado);
        }
        if(valor_desejado == a->info){
            return 1;
        }
    }
    else{

       return 0;
    }
}