#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>

#include filaPrio.h

//	O programa deve utilizar: Descritor, Listas Dinâmicas Simplesmente e Duplamente encadeadas, todos ligados, conforme a otimização do processo evidenciado
//do while(!kbhit()&& tempo)
// insere, retira, volta, esc


//descritor e cozinheiro(simplesmente)
struct TpPont{
	char cozinheiro[3];
	TpPont *prox;
};

struct TpDescritor{
	TpPont *inicio, *fim;
	int qtde;
};



TpPont *NovaCaixaPedido(char tipo[15], itens[50][50], int tempo, int prioridade){
	TpPedido *caixa = new TpPedido;
	caixa -> prox = NULL;
	caixa ->ant = NULL;
	strcpy(caixa -> tipo, tipo);
	caixa -> tempo = tempo;
	caixa -> prioridade = prioridade;
	return caixa;
}

