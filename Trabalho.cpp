#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>

#include filaPrio.h

//	O programa deve utilizar: Descritor, Listas Dinâmicas Simplesmente e Duplamente encadeadas, todos ligados, conforme a otimiza��o do processo evidenciado
//do while(!kbhit()&& tempo)
// insere, retira, volta, esc

void DistribuirPedidos(TpDesc &desc, FILE *arquivo, int qtdPedidos) {
    int count = 0;
    TpCozinheiro *cozAtual = desc.inicio;

    while (count < qtdPedidos) {
        if (cozAtual == NULL)
            cozAtual = desc.inicio;

        TpPedido *p = GerarPedidoAleatorio(arquivo);
        InserirPedidoOrdenado(cozAtual->listaPedidos, p);

        cozAtual = cozAtual->prox;
        count++;
    }
}

int CalcularCarga(TpPedido *lista) {
    int carga = 0;
    while (lista != NULL) {
        carga += lista->tempo;
        lista = lista->prox;
    }
    return carga;
}

void DistribuirPedidos(TpDesc &desc, FILE *arquivo, int qtdPedidos) {
    int count = 0;

    while (count < qtdPedidos) {
        TpPedido *novoPedido = GerarPedidoAleatorio(arquivo);

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

    // Após a distribuição, atualizar o estado dos demais
    TpCozinheiro *temp = desc.inicio;
    while (temp != NULL) {
        if (temp->listaPedidos == NULL)
            temp->estado = 'L';
        temp = temp->prox;
    }
}



//caixa para cuxinehiro
TpPont *NovaCaixaCozinheiro(int id, int estado){
	TpPedido *caixa = new TpPedido;
	caixa -> id = id;
	caixa -> estado = L; //L de Lula
	caixa -> prox = NULL;
	caixa -> listaPedidos = NULL;
	return caixa;
}


TpPedido* GerarPedidoAleatorio() {
    FILE *ptr;
    TpPedido *pedido = NULL;
    int tempo = 0, linha_aleatoria = 0, linha_atual = 1;
    char buffer[256], tipo_str[20], itens[256];

    ptr = fopen("Pedidos.txt", "r");
    if (ptr != NULL) {
        linha_aleatoria = 1 + (rand() % 15); // Supondo até 15 linhas
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
                // Força saída do laço caso erro de leitura (sem usar break)
                linha_atual = linha_aleatoria + 1;
            }
        }

        fclose(ptr);
    }

    return pedido; // permitido aqui, pois está no fim da função
}


void RemoverCozinheiro(TpCozinheiro* &lista, int id) {
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

void Menu() {
    int op;

    do {
        printf("\n====== MENU ======\n");
        printf("1. Escolher quantidade de cozinheiros\n");
        printf("2. Remover um cozinheiro\n");
        printf("3. Simular\n");
        printf("4. Listar cozinheiros\n");
        printf("ESC. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                int qtd, i= 1;
                printf("Quantos cozinheiros deseja adicionar? ");
                scanf("%d", &qtd);
				while(i<=qtd){
					NovaCaixaCozinheiro(i);
					i++;
				}
                break;
            }
            case 2: {
                int id;
                printf("ID do cozinheiro a remover: ");
                scanf("%d", &id);
                RemoverCozinheiro(&listaCozinheiros, id);
                break;
            }
            case 3:
                Simular();
                break;
            case 4:
                ListarCozinheiros(listaCozinheiros);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 27);
}
