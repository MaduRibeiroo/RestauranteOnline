#include<stdio.h>
#include<stdlib.h>
#define K 2
#define TF 6
struct kdtree{
	int ponto[k];
	struct kdtree *esq, *dir;
}; typedef struct kdtree KdTree;

KdTree *CriaNo(int ponto[K]){
	KdTree *no = (KdTree*)malloc(sizeof(KdTree));
	for(i=0; i<K; i++)
		no->ponto[i] = ponto[i];
	no->esq = no->dir = NULL;
	return no;
}

void Ordena(int pontos[TF][K], int d, int ini, int fim){
	int i, TL = fim, aux[K];
	while (TL> ini){
		for(i = ini; i<TL; i++)
			if(pontos[i][d]>pontos[i+1][d]){
				for(j = 0; j<K, j++)
					aux[j] = pontos[i][j];
					
				for(j = 0; j<K, j++)
					pontos[i][j] = pontos[i+1][j];
					
				for(j = 0; j<K, j++)
					pontos[i+1][j] = aux[j];
			}
		TL--;
	}
}

void InsereKdTree(KdTree **raiz, int pontos[TF][K], int n, int ini, int fim){
	int d, meio;
	if(ini<fim){
		d = n%k;
		Ordena(pontos, d, ini, fim);
		meio = (ini+fim)/2;
		*raiz = CriaNo(pontos[meio]);
		InsereKdTree(&(*raiz)->esq, pontos, n+1, ini, meio-1);
		InsereKdTree(&(*raiz)->dir, pontos, n+1, meio+1, fim);
	}
}

void ExibeKdTree(KdTree *raiz, int n){
	if(raiz!=Null){
		ExibeLdtree(raiz->dir, n+1);
		for(i=0; i<n; i++)
			printf("      ");
		printf("(%d,%d)\n", raiz->ponto[0], raiz->ponto[1]);
		ExibeLdtree(raiz->esq, n+1);
	}
	
}

int main(){
	int pontos[TF][K] = ()
	KdTree *raiz = NULL;
	Ordena(pontos, 0, 0 TF-1);
	InsereKdTree(&raiz, pontos, 0, 0, TF-1)
}
