#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// Estrutura que representa o buffer de entrada do usuário
typedef struct {
    char* buffer;           // Ponteiro para armazenar a linha digitada
    size_t buffer_length;   // Tamanho total do buffer alocado
    size_t input_length;    // Comprimento real da entrada do usuário
} InputBuffer;

// Função que inicializa e aloca um novo InputBuffer
InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

// Função que imprime o prompt do banco de dados na tela
void print_prompt() { 
    printf("db > "); 
}

// Função que lê a entrada do usuário e armazena no InputBuffer
void read_input(InputBuffer* input_buffer) {
    // getline lê uma linha do stdin e armazena no buffer
    size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Erro na leitura da entrada\n");
        exit(EXIT_FAILURE);
    }

    // Atualiza o tamanho real da entrada e remove o caractere de nova linha
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

// Função que libera a memória alocada para o InputBuffer
void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

// Função principal do programa
int main(int argc, char* argv[]) {
    // Cria um novo buffer de entrada
    InputBuffer* input_buffer = new_input_buffer();

    // Loop principal: lê comandos do usuário até que ele digite ".exit"
    while (true) {
        print_prompt();             // Mostra o prompt
        read_input(input_buffer);   // Lê a entrada do usuário

        // Se o usuário digitar ".exit", encerra o programa
        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            // Caso contrário, apenas exibe o que foi digitado
            printf("Você digitou: %s\n", input_buffer->buffer);
        }
    }
}
