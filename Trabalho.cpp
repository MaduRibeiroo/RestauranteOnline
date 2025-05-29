#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>

#include "Tad.h"

//	O programa deve utilizar: Descritor, Listas DinÃƒÆ’Ã‚Â¢micas Simplesmente e Duplamente encadeadas, todos ligados, conforme a otimizaÃƒÂ¯Ã‚Â¿Ã‚Â½ÃƒÂ¯Ã‚Â¿Ã‚Â½o do processo evidenciado
//do while(!kbhit()&& tempo)
// insere, retira, volta, esc
int totalExpresso = 0, totalRegular = 0, totalPreAgendado = 0;
int somaEsperaExpresso = 0, somaEsperaRegular = 0, somaEsperaPreAgendado = 0;
int pedidosNaoFinalizados = 0;
int temposPreparoOriginais[200]; // paralelo a pedidosGerados[]


// Vetor auxiliar para guardar tempos de entrada
const int MAX_PEDIDOS = 1000;
TpPedido* pedidosGerados[MAX_PEDIDOS];
int temposEntrada[MAX_PEDIDOS];
int pedidosGeradosTotal = 0;


char Menu(){
	printf("\n====== MENU ======\n");
    printf("[A]. Escolher quantidade de cozinheiros\n");
    printf("[B]. Remover um cozinheiro\n");
    printf("[C]. Qual o tempo de simulaÃ§Ã£o\n");
    printf("[D]. Simular\n");
    printf("[ESC]. Sair\n");
    printf("Escolha: ");
    return toupper(getch());
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


TpPedido* GerarPedidoAleatorio() {
    FILE *ptr = fopen("Pedidos.txt", "r");
    TpPedido *pedido = NULL;
    int tempo = 0, linha_aleatoria = 0, linha_atual = 1;
    char buffer[256], tipo_str[20], itens[256];

   
    if (ptr != NULL) {
        linha_aleatoria = 1 + (rand() % 15); // Supondo atÃƒÆ’Ã‚Â© 15 linhas
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
                // ForÃƒÆ’Ã‚Â§a saÃƒÆ’Ã‚Â­da do laÃƒÆ’Ã‚Â§o caso erro de leitura (sem usar break)
                linha_atual = linha_aleatoria + 1;
            }
        }

        fclose(ptr);
    }

    return pedido; // permitido aqui, pois estÃƒÆ’Ã‚Â¡ no fim da funÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Â£o
}

int EncontrarTempoPreparoOriginal(TpPedido *pedido) {
    for (int i = 0; i < pedidosGeradosTotal; i++) {
        if (pedidosGerados[i] == pedido)
            return temposPreparoOriginais[i];
    }
    return 0;
}





int CalcularCarga(TpPedido *lista) {
    int carga = 0;
    while (lista != NULL) {
        carga += lista->tempo;
        lista = lista->prox;
    }
    return carga;
}

int EncontrarTempoEntrada(TpPedido *pedido) {
    int i = 0;
    while (i < pedidosGeradosTotal) {
        if (pedidosGerados[i] == pedido)
            return temposEntrada[i];
        i++;
    }
    return 0; // Se não encontrar, retorna 0 (seguro)
}


void DistribuirPedidos(TpDesc &desc, int qtdPedidos) {
    int count = 0;

    while (count < qtdPedidos) {
        TpPedido *novoPedido = GerarPedidoAleatorio();

        // Armazena o pedido e tempo de entrada (0 por enquanto)
        pedidosGerados[pedidosGeradosTotal] = novoPedido;
        temposEntrada[pedidosGeradosTotal] = 0; // tempo inicial da simulaÃ§Ã£o
        pedidosGeradosTotal++;

        TpCozinheiro *escolhido = desc.inicio;
        int menorCarga = CalcularCarga(desc.inicio->listaPedidos);
        TpCozinheiro *atual = desc.inicio->prox;
        temposPreparoOriginais[pedidosGeradosTotal] = novoPedido->tempo;

        while (atual != NULL) {
            int cargaAtual = CalcularCarga(atual->listaPedidos);
            if (cargaAtual < menorCarga) {
                menorCarga = cargaAtual;
                escolhido = atual;
            }
            atual = atual->prox;
        }

        InserirPedidoOrdenado(escolhido->listaPedidos, novoPedido);

        if (escolhido->listaPedidos != NULL)
            escolhido->estado = 'O';

        count++;
    }

    TpCozinheiro *temp = desc.inicio;
    while (temp != NULL) {
        if (temp->listaPedidos == NULL)
            temp->estado = 'L';
        temp = temp->prox;
    }
}


void RemoverCozinheiro(TpDesc &desc, int id) {
    TpCozinheiro *anterior = NULL;
    TpCozinheiro *atual = desc.inicio;

    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) {
                desc.inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            if (desc.fim == atual) {
                desc.fim = anterior;
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

            desc.tamanho--;
            atual = (anterior == NULL) ? desc.inicio : anterior->prox;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}


void LimparCozinheiros(TpDesc &desc) {
    TpCozinheiro *atual = desc.inicio;
    while (atual != NULL) {
        TpPedido *p = atual->listaPedidos;
        while (p != NULL) {
            TpPedido *aux = p;
            p = p->prox;
            delete aux;
        }
        TpCozinheiro *auxCoz = atual;
        atual = atual->prox;
        delete auxCoz;
    }
    desc.inicio = desc.fim = NULL;
    desc.tamanho = 0;
}


void SimularRestaurante(TpDesc &desc, int tempoSimulacao) {
    int qtdPedidos;
    totalExpresso = 0;
    totalRegular = 0;
    totalPreAgendado = 0;

    somaEsperaExpresso = 0;
    somaEsperaRegular = 0;
    somaEsperaPreAgendado = 0;

    pedidosNaoFinalizados = 0;
    pedidosGeradosTotal = 0;

    for (int i = 0; i < MAX_PEDIDOS; i++) {
        pedidosGerados[i] = NULL;
        temposEntrada[i] = 0;
        temposPreparoOriginais[i] = 0;
    }
    if(tempoSimulacao == 0){
    	printf("Defina um tempo para simulacao");
    	getche();
    	clrscr();
    	Menu();
    }
    else{
    	srand(time(NULL));
	    qtdPedidos = 5 + rand() % 16; // entre 5 e 20
	    printf("Número de pedidos sorteados para distribuir: %d\n", qtdPedidos);
	
	    DistribuirPedidos(desc, qtdPedidos);
	
	    for (int i = 0; i < pedidosGeradosTotal; i++) {
	        temposEntrada[i] = 1;  
	    }
	
	    for (int tempo = 1; tempo <= tempoSimulacao; tempo++) {
	        printf("\n=== Tempo: %d ===\n", tempo);
	
	        TpCozinheiro *coz = desc.inicio;
	        while (coz != NULL) {
	            printf("Cozinheiro %d - Estado: %c\n", coz->id, coz->estado);
	            if (coz->listaPedidos != NULL) {
	                TpPedido *pedido = coz->listaPedidos;
	                pedido->tempo--;
	
	                printf("   Trabalhando no pedido: %s (%d restante)\n", pedido->itens, pedido->tempo);
	
	                if (pedido->tempo <= 0) {
	                    int tempoEntrada = EncontrarTempoEntrada(pedido);
	                    int tempoEspera = tempo - tempoEntrada;
	
	                    if (strcmp(pedido->tipo, "Expresso") == 0) {
	                        totalExpresso++;
	                        somaEsperaExpresso += tempoEspera;
	                    } else if (strcmp(pedido->tipo, "Regular") == 0) {
	                        totalRegular++;
	                        somaEsperaRegular += tempoEspera;
	                    } else {
	                        totalPreAgendado++;
	                        somaEsperaPreAgendado += tempoEspera;
	                    }
	
	                    // Remove pedido finalizado
	                    TpPedido *finalizado = pedido;
	                    coz->listaPedidos = pedido->prox;
	                    if (coz->listaPedidos != NULL)
	                        coz->listaPedidos->ant = NULL;
	
	                    printf("   Pedido finalizado!\n");
	                    delete finalizado;
	
	                    if (coz->listaPedidos == NULL)
	                        coz->estado = 'L';
	                }
	            } else {
	                printf("   Sem pedidos\n");
	                coz->estado = 'L';
	            }
	
	            coz = coz->prox;
	        }
	
	        Sleep(500); // Espera 1 segundo entre unidades de tempo
	    }
	
		// Contar pedidos não finalizados
	    pedidosNaoFinalizados = 0;
	    TpCozinheiro *cz = desc.inicio;
	    while (cz != NULL) {
	        TpPedido *p = cz->listaPedidos;
	        while (p != NULL) {
            	pedidosNaoFinalizados++;
	        	p = p->prox;
		    }
		    cz = cz->prox;
		}
		
		// Relatório final
		printf("\n=== Fim da simulação ===\n");
		printf("\n--- Relatório Final ---\n");
		printf("Pedidos Expresso finalizados: %d\n", totalExpresso);
	    printf("Pedidos Regular finalizados: %d\n", totalRegular);
	    printf("Pedidos Pré-Agendado finalizados: %d\n", totalPreAgendado);
	
	    printf("\nTempo médio de espera:\n");
	    if (totalExpresso > 0)
	        printf("  Expresso: %.2f unidades\n", (float)somaEsperaExpresso / totalExpresso);
	    if (totalRegular > 0)
	        printf("  Regular: %.2f unidades\n", (float)somaEsperaRegular / totalRegular);
	    if (totalPreAgendado > 0)
	        printf("  Pré-Agendado: %.2f unidades\n", (float)somaEsperaPreAgendado / totalPreAgendado);
	
	    printf("\nPedidos não finalizados: %d\n", pedidosNaoFinalizados);
    }
    
}




void Executar() {
	int tempoSimulacao = 0;
    char op;
	TpPedido pedido;
	TpDesc cozinheiros; 
    cozinheiros.inicio = NULL;
    cozinheiros.fim = NULL;
    cozinheiros.tamanho = 0;
	
    do{
    	clrscr();
    	op = Menu();
        switch (op) {
            case 'A': {
			    clrscr();
			    int qtd, i = 1;
			    printf("Quantos cozinheiros deseja adicionar?\n");
			    scanf("%d", &qtd);
			    getche();
			
			    // Limpa cozinheiros antigos antes de adicionar novos
			    LimparCozinheiros(cozinheiros);
			
			    while (i <= qtd) {
			        TpCozinheiro *novo = NovaCaixaCozinheiro(i);
			
			        if (cozinheiros.inicio == NULL) {
			            cozinheiros.inicio = cozinheiros.fim = novo;
			        } else {
			            cozinheiros.fim->prox = novo;
			            cozinheiros.fim = novo;
			        }
			
			        cozinheiros.tamanho++;
			        i++;
			    }
			    break;
			}

            
            case 'B': {
			    clrscr();
			    int id;
			    printf("ID do cozinheiro a remover:\n");
			    scanf("%d", &id);
			    getche();
			    RemoverCozinheiro(cozinheiros, id);
			    break;
			}

            case 'C': {
                clrscr();
                printf("Defina o tempo total de simulaÃ§Ã£o (em unidades de tempo):\n");
                scanf("%d", &tempoSimulacao);
                getche();
                printf("Tempo de simulaÃ§Ã£o definido como %d unidades.\n", tempoSimulacao);
                break;
            }
            case 'D':
            	clrscr();
    			SimularRestaurante(cozinheiros, tempoSimulacao);
    			getche();
    			break;
        }
    } while (op != 27);
}

int main(){
	Executar();
	return 0;
}