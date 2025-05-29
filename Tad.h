//duplamente encadeada pra pedido
struct TpPedido{
	char tipo[15], itens[100];
	int tempo, prioridade; //1 expresso(alta), 2 regular(media), 3 pre agendado(baixa)
	TpPedido *ant, *prox;
};

//descritor e cozinheiro(simplesmente)
struct TpCozinheiro{
	int id;
	char estado;
	TpPedido *listaPedidos;
	TpCozinheiro *prox;
};

struct TpDesc{	
	TpCozinheiro *inicio, *fim;
	int tamanho;
};



struct TpFila {
    TpPedido *inicio, *fim;
};

TpPedido *NovoPedido(char tipo[15], char itens[100], int tempo) {
    TpPedido *p = new TpPedido;
    strcpy(p->tipo, tipo);
    strcpy(p->itens, itens);
    p->tempo = tempo;

    if (stricmp(tipo, "Expresso") == 0) 
		p->prioridade = 1;
    else{
		if (stricmp(tipo, "Regular") == 0) 
			p->prioridade = 2;
    	else 
			p->prioridade = 3;
	}
    p->ant = p->prox = NULL;

    return p;
}

void InserirPedidoOrdenado(TpPedido* &lista, TpPedido* novo) {
    TpPedido *atual = lista;

    if (lista == NULL) {
        lista = novo;
    } else {
        while (atual != NULL && atual->prioridade <= novo->prioridade) {
            atual = atual->prox;
        }

        if (atual == lista) {
            novo->prox = lista;
            lista->ant = novo;
            lista = novo;
        }
		else 
			if (atual == NULL) {
				TpPedido *fim = lista;
				while (fim->prox != NULL) fim = fim->prox;
				fim->prox = novo;
				novo->ant = fim;
			} 
			else {
				novo->prox = atual;
				novo->ant = atual->ant;
				atual->ant->prox = novo;
				atual->ant = novo;
        	}
    }
}

void InicializarCozinheiros(TpDesc &desc, int qtd) {
    desc.inicio = NULL;
    desc.fim = NULL;
    desc.tamanho = 0;

    for (int i = 1; i <= qtd; i++) {
        TpCozinheiro *novo = new TpCozinheiro;
        novo->id = i;
        novo->estado = 'L'; 
        novo->prox = NULL;
        novo->listaPedidos = NULL;

        if (desc.inicio == NULL) {
            desc.inicio = desc.fim = novo;
        } else {
            desc.fim->prox = novo;
            desc.fim = novo;
        }

        desc.tamanho++;
    }
}



void ImprimirFila(TpFila f) {
    TpPedido* p = f.inicio;
    while (p != NULL) {
        printf("Tipo: %s | Itens: %s | Tempo: %d | Prioridade: %d\n", 
            p->tipo, p->itens, p->tempo, p->prioridade);
        p = p->prox;
    }
}