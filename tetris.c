#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PECAS 5 
#define MAX_PILHA 3

// Estrutura de uma peça do Tetris Stack
typedef struct {
    char tipo; 
    int id;    
} Peca;

// Estrutura de Fila Circular
typedef struct {
    Peca pecas[MAX_PECAS];
    int inicio, fim, total;
} Fila;

// Estrutura de Pilha
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

void Inicializa_Fila(Fila *f);
void Inicializa_Pilha(Pilha *p);
Peca Gera_Pecas();
void Inserir_Peca(Fila *f, Peca p);
void Inserir_Pilha(Pilha *p, Peca a);
Peca Remover_Peca(Fila *f);
Peca Remover_Pilha(Pilha *p);
int Fila_Cheia(Fila *f);
int Pilha_Cheia(Pilha *p);
int Fila_Vazia(Fila *f);
int Pilha_Vazia(Pilha *p);
void Imprime_Fila(Fila *f);
void Imprime_Pilha(Pilha *p);
void Troca_Unica(Fila *f, Pilha *p);
void Troca_Multipla(Fila *f, Pilha *p);

int Contador = 0; // contador global de IDs

int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    Peca jogada;
    int opcao;

    Inicializa_Fila(&fila);
    Inicializa_Pilha(&pilha);

    // Preenche a fila inicial
    for (int i = 0; i < MAX_PECAS; i++) {
        Inserir_Peca(&fila, Gera_Pecas());
    }

    do {   
        printf("\n--- Menu ---\n");
        printf("1. Jogar peça (dequeue).\n");
        printf("2. Reservar uma peça (enqueue para pilha).\n");
        printf("3. Usar peça reservada (pop da pilha).\n");
        printf("4. Trocar peça da frente da fila com o topo da pilha.\n");
        printf("5. Trocar as 3 primeiras da fila com as 3 peças da pilha.\n");
        printf("0. Sair do programa\n");
        printf("-> Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: // Jogar peça
            if (!Fila_Vazia(&fila)) {
                jogada = Remover_Peca(&fila);
                printf("\n-> Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
                Inserir_Peca(&fila, Gera_Pecas());
            } else {
                printf("\n--- Fila Vazia ---\n");
            }
            break;

        case 2: // Reservar peça
            if (!Fila_Vazia(&fila)) {
                if (!Pilha_Cheia(&pilha)) {
                    jogada = Remover_Peca(&fila);
                    Inserir_Pilha(&pilha, jogada);
                    printf("\n-> Peça reservada: [%c %d]\n", jogada.tipo, jogada.id);
                    Inserir_Peca(&fila, Gera_Pecas()); // mantém a fila cheia
                } else {
                    printf("\n--- Pilha Cheia ---\n");
                }
            } else {
                printf("\n--- Fila Vazia ---\n");
            }
            break;

        case 3: // Usar peça reservada
            if (!Pilha_Vazia(&pilha)) {
                jogada = Remover_Pilha(&pilha);
                printf("\n-> Peça usada da reserva: [%c %d]\n", jogada.tipo, jogada.id);
            } else {
                printf("\n--- Pilha Vazia ---\n");
            }
            break;

        case 4: // Troca única
            Troca_Unica(&fila, &pilha);
            break;

        case 5: // Troca múltipla
            Troca_Multipla(&fila, &pilha);
            break;

        case 0:
            printf("\n--- Fim do programa ---\n");
            break;

        default:
            printf("\n--- Opção inválida ---\n");
            break;
        }

        Imprime_Fila(&fila);
        Imprime_Pilha(&pilha);

    } while (opcao != 0);

    return 0;
}

void Inicializa_Fila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void Inicializa_Pilha(Pilha *p) {
    p->topo = -1;
}

Peca Gera_Pecas() {
    char tipos[] = {'T', 'O', 'I', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = Contador++;
    return nova;
}

void Inserir_Peca(Fila *f, Peca p) {
    if (Fila_Cheia(f)) {   
        printf("\n--- Fila cheia ---\n");
        return;
    }
    f->pecas[f->fim] = p;    
    f->fim = (f->fim + 1) % MAX_PECAS;
    f->total++;
}

void Inserir_Pilha(Pilha *p, Peca a){
    if(Pilha_Cheia(p)){
        printf("\n--- Pilha cheia ---\n");
        return;
    }
    p->topo++;
    p->pecas[p->topo] = a;
}

Peca Remover_Peca(Fila *f) {
    Peca removida = {'-', -1};
    if (Fila_Vazia(f)) {
        return removida;
    }  
    removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PECAS;
    f->total--;
    return removida;
}

Peca Remover_Pilha(Pilha *p){
    Peca removida = {'-', -1};
    if (Pilha_Vazia(p)) {
        return removida;
    }
    removida = p->pecas[p->topo];
    p->topo--;
    return removida;
}

int Fila_Cheia(Fila *f) {
    return f->total == MAX_PECAS;
}

int Pilha_Cheia(Pilha *p){
    return p->topo == MAX_PILHA - 1;
}

int Fila_Vazia(Fila *f) {
    return f->total == 0;
}

int Pilha_Vazia(Pilha *p){
    return p->topo == -1;
}

void Imprime_Fila(Fila *f) {
    printf("\nFila de peças: ");
    if (Fila_Vazia(f)) {
        printf("--- Vazia ---");
    } else {
        for (int i = 0; i < f->total; i++) {
            int idx = (f->inicio + i) % MAX_PECAS;
            printf("[%c %d] ", f->pecas[idx].tipo, f->pecas[idx].id); 
        }
    }
    printf("\n");
}

void Imprime_Pilha(Pilha *p){
    printf("Pilha de reserva (Topo -> Base): ");
    if (Pilha_Vazia(p)) {
        printf("--- Vazia ---");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pecas[i].tipo, p->pecas[i].id);
        }
    }
    printf("\n");
}

void Troca_Unica(Fila *f, Pilha *p) {
    if (Fila_Vazia(f) || Pilha_Vazia(p)) {
        printf("\n--- Não é possível trocar: fila ou pilha vazia ---\n");
        return;
    }
    Peca temp = f->pecas[f->inicio];
    f->pecas[f->inicio] = p->pecas[p->topo];
    p->pecas[p->topo] = temp;
    printf("\n-> Troca realizada entre frente da fila e topo da pilha!\n");
}

void Troca_Multipla(Fila *f, Pilha *p) {
    if (f->total < 3 || p->topo < 2) {
        printf("\n--- Não é possível trocar múltiplas peças (faltam elementos) ---\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int idx = (f->inicio + i) % MAX_PECAS;
        Peca temp = f->pecas[idx];
        f->pecas[idx] = p->pecas[p->topo - i];
        p->pecas[p->topo - i] = temp;
    }
    printf("\n-> Troca múltipla realizada (3 peças trocadas)!\n");
}
