//Lista dinamica duplamente encadeada 

struct TpPont{
	char Nome[20];
	TpPont *ant, *prox;
};

TpPont*novaCaixa(char Nome[20]){
	TpPont *Caixa = new TpPont;
	Caixa -> prox = NULL;
	strcpy(Caixa->nome, nome);
	Caixa->ant = NULL;
	return Caixa;
}

TpPont *InserirOrdenado(TpPont *Lista){
	TpPont *NC, *aux;
	chat AuxNome[20];
	clrscr();
	printf("\n*** INSERIR NOMES ***\n");
	printf("\nNome:");
	fflush(stdin);
	gets(nome);
	
	
	while(strcmp(AuxNome,"/0")=0){
		NC = NovaCaixa(AuxNome);
		if(Lista == NULL)
			Lista = NC;
		else
			if(stricmp(AuxNome, Lista -> Nome)<=0){
				NC->prox = Lista;
				Lista->ant = NC;
				Lista = NC;
			}
			else
				aux = Lista->prox;
				while(aux->prox != NULL && stricmp(AuxNome, aux ->nome)>0)
					aux = aux->prox;
				if(stricmp(AuxNome, aux->Nome)>0){
					NC->ant = aux;
					aux->prox = NC;
				}
				else{
					
					
					
					
				}
			printf("\nNome:");
			fflush(stdin);
			gets(AuxNome);
	}
	return Lista;
}

int main(void){
	TpPont *L = NULL;
	L =InserirOrdenado(L);
	Exibir(L);
	L = Excluir(L);
	Exibir(L);
	ExibirInvertidoRecursivo(L);
	ExibirInvertidoIterativo(L);
	L = DestruirListaIterativo(L);
	L = DestruirListaRecursivo(L);
	Exibir(L);
	return 0;
}
