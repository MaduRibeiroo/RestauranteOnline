#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>

#include "Tad.h"

//	O programa deve utilizar: Descritor, Listas DinÃ¢micas Simplesmente e Duplamente encadeadas, todos ligados, conforme a otimizaï¿½ï¿½o do processo evidenciado
//do while(!kbhit()&& tempo)
// insere, retira, volta, esc


TpPedido* GerarPedidoAleatorio() {
    FILE *ptr = fopen("Pedidos.txt", "r");
    TpPedido *pedido = NULL;
    int tempo = 0, linha_aleatoria = 0, linha_atual = 1;
    char buffer[256], tipo_str[20], itens[256];

   
    if (ptr != NULL) {
        linha_aleatoria = 1 + (rand() % 15); // Supondo atÃ© 15 linhas
        rewind(ptr);

        while (linha_atual <= linha_aleatoria) {
            if (fgets(buffer, sizeof(buffer), ptr) != NULL) {
                if (linha_atual == linha_aleatoria) {
                    pedido = new TpPedido;

                    sscanf(buffer, "%[^,],%d,\"%[^\"]\"", tipo_str, &tempo, itens);

                    strcpy(pedido->tipo, tipo_str);
                    strcpy(pedido->itens, itens);
                    pedido->tempo = tempo;

                    if (strcmp(tipo_str, "Expresso") == 0)
                        pedido->prioridade = 1;
                    else if (strcmp(tipo_str, "Regular") == 0)
                        pedido->prioridade = 2;
                    else
                        pedido->prioridade = 3;

                    pedido->prox = NULL;
                    pedido->ant = NULL;
                }
                linha_atual++;
            } else {
                // ForÃ§a saÃ­da do laÃ§o caso erro de leitura (sem usar break)
                linha_atual = linha_aleatoria + 1;
            }
        }

        fclose(ptr);
    }

    return pedido; // permitido aqui, pois estÃ¡ no fim da funÃ§Ã£o
}

int CalcularCarga(TpPedido *lista) {
    int carga = 0;
    while (lista != NULL) {
        carga += lista->tempo;
        lista = lista->prox;
    }
    return carga;
}

void DistribuirPedidos(TpDesc &desc, int qtdPedidos) {
    int count = 0;

    while (count < qtdPedidos) {
        TpPedido *novoPedido = GerarPedidoAleatorio();

        TpCozinheiro *escolhido = desc.inicio;
        int menorCarga = CalcularCarga(desc.inicio->listaPedidos);
        TpCozinheiro *atual = desc.inicio->prox;

        while (atual != NULL) {
            int cargaAtual = CalcularCarga(atual->listaPedidos);
            if (cargaAtual < menorCarga) {
                menorCarga = cargaAtual;
                escolhido = atual;
            }
            atual = atual->prox;
        }

        InserirPedidoOrdenado(escolhido->listaPedidos, novoPedido);

        // Atualiza estado do cozinheiro escolhido
        if (escolhido->listaPedidos != NULL)
            escolhido->estado = 'O';

        count++;
    }

    // Atualizar estado dos que ficaram sem pedidos
    TpCozinheiro *temp = desc.inicio;
    while (temp != NULL) {
        if (temp->listaPedidos == NULL)
            temp->estado = 'L';
        temp = temp->prox;
    }
}






//caixa para cuxinehiro
TpCozinheiro *NovaCaixaCozinheiro(int id){
	TpCozinheiro *caixa = new TpCozinheiro;
	caixa -> id = id;
	caixa -> estado = 'L'; //L de Livre
	caixa -> prox = NULL;
	caixa -> listaPedidos = NULL;
	return caixa;
}


void RemoverCozinheiro(TpCozinheiro *lista, int id) {
    TpCozinheiro *anterior = NULL;
    TpCozinheiro *atual = lista;

    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            TpPedido *p = atual->listaPedidos;
            TpPedido *aux;
            while (p != NULL) {
                aux = p->prox;
                delete p;
                p = aux;
            }

            delete atual;
            atual = NULL; 
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}

char Menu(){
	printf("\n====== MENU ======\n");
    printf("[A]. Escolher quantidade de cozinheiros\n");
    printf("[B]. Remover um cozinheiro\n");
    printf("[C]. Simular\n");
    printf("[ESC]. Sair\n");
    printf("Escolha: ");
    return toupper(getch());
}

void Executar() {
    char op;
	TpPedido pedido;
	TpCozinheiro cozinheiros;
	op = Menu();
    do{
        switch (op) {
            case 'A': {
            	clrscr();
                int qtd, i= 1;
                printf("Quantos cozinheiros deseja adicionar?\n");
                scanf("%d", &qtd);
                getche();
				while(i<=qtd){
					NovaCaixaCozinheiro(i);
					i++;
				}
			}
            break;
            
            case 'B':{
            	clrscr();
                int id;
                printf("ID do cozinheiro a remover:\n");
                scanf("%d", &id);
                getche();
                RemoverCozinheiro(&cozinheiros, id);
                break;
            }
            case 'C':
                //Simular();
                break;
            default:
                printf("OpÃ§Ã£o invÃ¡lida!\n");
        }
    } while (op != 27);
}

int main(){
	Executar();
	return 0;
}