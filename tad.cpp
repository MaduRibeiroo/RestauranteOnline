#define MAXFILA 200

//duplamente encadeada pra pedido
struct TpPedido{
	char tipo[15], itens[50][50];
	int tempo, prioridade; //1 expresso(alta), 2 regular(media), 3 pre agendado(baixa)
	TpPedido *ant, *prox;
};

struct TpFila{
	int fim;
	TpPedido fila[MAXFILA];
};

void inicializar(TpFila &f){
	f.fim=-1;
}

int vazia(int fim){
	return fim == -1;
}

int cheia(int fim){
	return fim == MAXFILA-1;
}

void inserir(TpFila &f, TpPedido p){
	TpPedido aux;
	//verifica prioridade
	if(stricmp(p->tipo, "Regular") == 0)
		p->prioridade = 1;
	else
		if(stricmp(p->tipo, "Expresso") == 0)
			p->prioridade = 2;
		else
			if(stricmp(p->tipo, "Pré-Agendado") == 0)
				p->prioridade = 3;
	//insere o pedido na fila
	
}


