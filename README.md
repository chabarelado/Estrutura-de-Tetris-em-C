🎮 Gerenciador de Peças – Fila Circular e Pilha

Este projeto implementa um gerenciador de peças inspirado em jogos de estratégia, utilizando duas estruturas de dados clássicas:

Fila circular com capacidade para 5 peças.

Pilha com capacidade para 3 peças.

As peças podem ser jogadas, reservadas, usadas ou trocadas entre as duas estruturas, seguindo regras específicas.

📌 Funcionalidades

O programa permite as seguintes ações:

Jogar peça da frente da fila

Remove a peça da frente da fila (dequeue).

Uma nova peça é gerada automaticamente para manter a fila cheia.

Reservar peça

Move a peça da frente da fila para o topo da pilha, se houver espaço.

Uma nova peça é adicionada à fila para manter seu tamanho.

Usar peça reservada

Remove a peça do topo da pilha (pop), simulando seu uso.

Trocar peça atual

Substitui a peça da frente da fila com a peça do topo da pilha.

Troca múltipla

Troca as 3 primeiras peças da fila com as 3 peças da pilha, caso ambas tenham pelo menos 3 elementos.

Sair do programa

📊 Estruturas utilizadas
📌 Peça (struct Peca)

Cada peça possui:

tipo: caractere representando o tipo da peça ('I', 'O', 'T', 'L').

id: número inteiro único que identifica a ordem de criação.

📌 Fila Circular (struct Fila)

Armazena até 5 peças.

Implementada de forma circular para reaproveitar o espaço.

📌 Pilha (struct Pilha)

Armazena até 3 peças.

Estilo LIFO (último a entrar, primeiro a sair).
