// LISTA DINAMICA SIMPLESMENTE ENCADEADA COM DESCRITOR 
// Descritor possibilita o acesso direto às extremidades da lista, e ainda o eventual armazenamento de dados comuns a mesma 

struct TpPont{
	char Nome[20];
	TpPont *prox;
};

struct TpDescritor{
	TpPont *inicio, *fim;
	int qtde;
};

TpPont &NovaCaixa (char nome[20]){
	TpPont *Caixa = new TpPont;
	Caixa -> prox = NULL;
	strcpy(Caixa->nome, nome);
	return Caixa;
}

void Inicializar(TpDescritor &Desc){
	Desc.inicio = Desc.fim = NULL;
	Desc.qtde = 0;
}

void InserirOrdenado(TpDescritor &Desc){
	TpPont *NC;
	char AuxNome[20];
	clrscr();
	printf("\nInserir Ordenado\n");
	printf("\nNome: ");
	fflush(stdin);
	gets(AuxNome);
	while(strcmp(AuxNome, "\0")!=0){
		NC  = NovaCaixa(AuxNome);
		if(Desc.qtde == 0)
			Desc.inicio = Desc.fim = NC;
		else
			if(stricmp(AuxNome, Desc.inicio -> nome) <= 0){
				NC -> prox = Desc.inicio;
				Desc.Inicio = NC;
			}
			else 
				if(stricmp(AuxNome, Desc.fim -> nome)){
					Desc.fim -> prox = NC;
					Desc.fim = NOC;
				}
				else{
					ant = Desc.inicio;
					p = Desc.inicio -> prox;
					while(stricmp(AuxNome , p-> nome)>0){
						ant = p;
						p = p -> prox;
					}
					ant -> prox = NC;
					NC -> prox = p;
				}
				Desc.qtde ++;
	}
}

int main (void){
	TpDescritor D;
	Inicializa(D);
	InsereOrdenado(D);
	Exibir(D);
	Excluir(D);
	Exibir(D);
	ExibirContrarioRecursivo(D);
	LiberarListaTodaIterativo(D);
	LiberarListaTodaRecursivo(D);
	Exibir(D);
	return 0;
}
