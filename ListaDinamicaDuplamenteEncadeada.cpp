// LISTA DINAMICA DUPLAMENTE ENCADEADA

struct TpPont{ 
	char nome[20];
	TpPont *ant, *prox;
};

TpPont *NovaCaix(char nome[20]){
	TpPont *caixa = new TpPont;
	caixa -> prox = NULL;
	strcpy(caixa -> nome, nome);
	caixa ->ant = NULL;
	return caixa;
}

TpPont *InsereOrdenado(TpPont *lista){
	TpPont *nc;
	char auxNome[20];
	clrscr();
	printf("\nInsere Nome\n");
	printf("\nNome: ");
	fflush(stdin);
	gets(nome);
	while(strcmp(auxNome, "\0")!= 0){
		nc = NovaCaixa(auxNome);
		if(lista == NULL)
			lista = nc;
		else{
			if(strcmp(auxNome, lista -> nome)<= 0){
				nc -> prox = lista;
				lista -> ant = nc;
				lista = nc;
			}
			else{
				aux = lista -> prox;
				while(aux -> prox != NULL && stricmp(auxNOme, aux -> nome) > 0)
					aux = aux -> prox;
				if(stricmp(aux, aux -> nome) >= 0){
					nc -> ant = aux;
					aux -> prox = nc;
				}
				else{
					nc -> prox = aux;
					nc -> ant = aux -> ant;
					aux -> ant -> prox = nc;
					aux -> ant = nc;
				}
			}
		}
	}
	
}
