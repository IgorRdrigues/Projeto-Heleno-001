#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura de um livro
typedef struct {
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

// Definindo a estrutura da lista de livros
typedef struct {
    Livro livros[100]; // Lista estática de livros (pode ajustar o tamanho conforme necessário)
    int tamanho;       // Tamanho atual da lista
} ListaLivros;

// Função para criar uma nova lista de livros vazia
ListaLivros criarLista() {
    ListaLivros lista;
    lista.tamanho = 0;
    return lista;
}

// Função para verificar o tamanho da lista
int tamanhoLista(ListaLivros* lista) {
    return lista->tamanho;
}

// Função para exibir os elementos da lista
void exibirLista(ListaLivros* lista) {
    if (lista->tamanho == 0) {
        printf("A lista de livros está vazia.\n");
        return;
    }

    printf("Lista de Livros:\n");
    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d. Título: %s, Autor: %s, Ano: %d\n", i + 1, lista->livros[i].titulo, lista->livros[i].autor, lista->livros[i].ano);
    }
}

// Função para consultar um livro na lista
int consultarLivro(ListaLivros* lista, char* titulo) {
    for (int i = 0; i < lista->tamanho; i++) {
        if (strcmp(lista->livros[i].titulo, titulo) == 0) {
            return i;
        }
    }
    return -1; // Livro não encontrado
}

// Função para inserir um livro na lista
void inserirLivro(ListaLivros* lista, Livro livro) {
    if (lista->tamanho < 100) { // Verifica se há espaço na lista
        lista->livros[lista->tamanho] = livro;
        lista->tamanho++;
        printf("Livro inserido com sucesso.\n");
    } else {
        printf("A lista de livros está cheia. Não é possível adicionar mais livros.\n");
    }
}

// Função para alterar um livro na lista
void alterarLivro(ListaLivros* lista, int indice, Livro novoLivro) {
    if (indice >= 0 && indice < lista->tamanho) {
        lista->livros[indice] = novoLivro;
        printf("Livro alterado com sucesso.\n");
    } else {
        printf("Índice inválido.\n");
    }
}

// Função para excluir um livro da lista
void excluirLivro(ListaLivros* lista, int indice) {
    if (indice >= 0 && indice < lista->tamanho) {
        for (int i = indice; i < lista->tamanho - 1; i++) {
            lista->livros[i] = lista->livros[i + 1];
        }
        lista->tamanho--;
        printf("Livro excluído com sucesso.\n");
    } else {
        printf("Índice inválido.\n");
    }
}

// Função para salvar a lista de livros em um arquivo
void salvarLista(ListaLivros* lista, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Erro ao abrir o arquivo para escrita");
        exit(EXIT_FAILURE);
    }

    fwrite(lista, sizeof(ListaLivros), 1, file);

    fclose(file);
}

// Função para carregar a lista de livros de um arquivo
void carregarLista(ListaLivros* lista, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo para leitura");
        exit(EXIT_FAILURE);
    }

    fread(lista, sizeof(ListaLivros), 1, file);

    fclose(file);
}

// Função para reinicializar a lista de livros
void reinicializarLista(ListaLivros* lista) {
    lista->tamanho = 0;
    printf("A lista de livros foi reinicializada.\n");
}

// Função principal
int main() {
    ListaLivros lista = criarLista();
    int choice, indice;
    char titulo[50];

    do {
        printf("\nEscolha uma operação:\n");
        printf("1. Exibir lista de livros\n");
        printf("2. Consultar livro\n");
        printf("3. Inserir livro\n");
        printf("4. Alterar livro\n");
        printf("5. Excluir livro\n");
        printf("6. Salvar lista em arquivo\n");
        printf("7. Carregar lista de arquivo\n");
        printf("8. Reinicializar lista\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                exibirLista(&lista);
                break;

            case 2:
                printf("Digite o título do livro a ser consultado: ");
                scanf("%s", titulo);
                indice = consultarLivro(&lista, titulo);
                if (indice != -1) {
                    printf("Livro encontrado na posição %d.\n", indice + 1);
                } else {
                    printf("Livro não encontrado na lista.\n");
                }
                break;

            case 3:
                printf("Digite o título do livro: ");
                scanf("%s", lista.livros[lista.tamanho].titulo);
                printf("Digite o autor do livro: ");
                scanf("%s", lista.livros[lista.tamanho].autor);
                printf("Digite o ano do livro: ");
                scanf("%d", &lista.livros[lista.tamanho].ano);
                inserirLivro(&lista, lista.livros[lista.tamanho]);
                break;

            case 4:
                printf("Digite o título do livro a ser alterado: ");
                scanf("%s", titulo);
                indice = consultarLivro(&lista, titulo);
                if (indice != -1) {
                    printf("Digite o novo título do livro: ");
                    scanf("%s", lista.livros[indice].titulo);
                    printf("Digite o novo autor do livro: ");
                    scanf("%s", lista.livros[indice].autor);
                    printf("Digite o novo ano do livro: ");
                    scanf("%d", &lista.livros[indice].ano);
                    alterarLivro(&lista, indice, lista.livros[indice]);
                } else {
                    printf("Livro não encontrado na lista.\n");
                }
                break;

            case 5:
                printf("Digite o título do livro a ser excluído: ");
                scanf("%s", titulo);
                indice = consultarLivro(&lista, titulo);
                if (indice != -1) {
                    excluirLivro(&lista, indice);
                } else {
                    printf("Livro não encontrado na lista.\n");
                }
                break;

            case 6:
                printf("Digite o nome do arquivo para salvar: ");
                char filename[50];
                scanf("%s", filename);
                salvarLista(&lista, filename);
                break;

            case 7:
                printf("Digite o nome do arquivo para carregar: ");
                scanf("%s", filename);
                carregarLista(&lista, filename);
                break;

            case 8:
                reinicializarLista(&lista);
                break;

            case 0:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 0);

    return 0;
}


