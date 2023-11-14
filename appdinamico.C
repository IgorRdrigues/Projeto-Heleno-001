#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó da fila
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Definindo a estrutura da fila
typedef struct {
    Node* front;  // Aponta para o primeiro elemento da fila
    Node* rear;   // Aponta para o último elemento da fila
    int size;     // Tamanho da fila
} Queue;

// Função para criar uma nova fila vazia
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        perror("Erro ao alocar memória para a fila");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// Função para verificar se a fila está vazia
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Função para obter o tamanho da fila
int getSize(Queue* queue) {
    return queue->size;
}

// Função para enfileirar um elemento
void enqueue(Queue* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++;
}

// Função para desenfileirar um elemento
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Erro: a fila está vazia.\n");
        exit(EXIT_FAILURE);
    }

    Node* frontNode = queue->front;
    int data = frontNode->data;

    queue->front = frontNode->next;
    free(frontNode);

    queue->size--;

    return data;
}

// Função para exibir os elementos da fila
void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("A fila está vazia.\n");
        return;
    }

    printf("Elementos da fila: ");
    Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Função para consultar um elemento na fila
int searchElement(Queue* queue, int target) {
    Node* current = queue->front;
    int position = 1;

    while (current != NULL) {
        if (current->data == target) {
            return position;
        }

        current = current->next;
        position++;
    }

    return -1; // Elemento não encontrado
}

// Função para inserir um elemento em uma posição específica na fila
void insertElement(Queue* queue, int position, int data) {
    if (position < 1 || position > getSize(queue) + 1) {
        fprintf(stderr, "Erro: posição inválida para inserção.\n");
        exit(EXIT_FAILURE);
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;

    if (position == 1) {
        newNode->next = queue->front;
        queue->front = newNode;
    } else {
        Node* current = queue->front;
        for (int i = 1; i < position - 1; i++) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    queue->size++;
}

// Função para alterar um elemento na fila
void modifyElement(Queue* queue, int position, int newData) {
    if (position < 1 || position > getSize(queue)) {
        fprintf(stderr, "Erro: posição inválida para modificação.\n");
        exit(EXIT_FAILURE);
    }

    Node* current = queue->front;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }

    current->data = newData;
}

// Função para excluir um elemento na fila
void deleteElement(Queue* queue, int position) {
    if (position < 1 || position > getSize(queue)) {
        fprintf(stderr, "Erro: posição inválida para exclusão.\n");
        exit(EXIT_FAILURE);
    }

    Node* temp;
    if (position == 1) {
        temp = queue->front;
        queue->front = temp->next;
    } else {
        Node* current = queue->front;
        for (int i = 1; i < position - 1; i++) {
            current = current->next;
        }

        temp = current->next;
        current->next = temp->next;
    }

    free(temp);
    queue->size--;
}

// Função para salvar a fila em um arquivo
void saveQueue(Queue* queue, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo para escrita");
        exit(EXIT_FAILURE);
    }

    Node* current = queue->front;
    while (current != NULL) {
        fprintf(file, "%d ", current->data);
        current = current->next;
    }

    fclose(file);
}

// Função para carregar a fila de um arquivo
void loadQueue(Queue* queue, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo para leitura");
        exit(EXIT_FAILURE);
    }

    int data;
    while (fscanf(file, "%d", &data) == 1) {
        enqueue(queue, data);
    }

    fclose(file);
}

// Função para reinicializar a fila
void resetQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
}

// Função principal
int main() {
    Queue* queue = createQueue();
    int choice, position, data, target;
    char filename[50];

    do {
        printf("\nEscolha uma operação:\n");
        printf("1. Enfileirar elemento\n");
        printf("2. Desenfileirar elemento\n");
        printf("3. Exibir elementos da fila\n");
        printf("4. Consultar elemento na fila\n");
        printf("5. Inserir elemento na fila\n");
        printf("6. Alterar elemento na fila\n");
        printf("7. Excluir elemento na fila\n");
        printf("8. Salvar fila em arquivo\n");
        printf("9. Carregar fila de arquivo\n");
        printf("10. Reinicializar fila\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o elemento a ser enfileirado: ");
                scanf("%d", &data);
                enqueue(queue, data);
                break;

            case 2:
                if (!isEmpty(queue)) {
                    printf("Desenfileirando elemento: %d\n", dequeue(queue));
                } else {
                    printf("A fila está vazia.\n");
                }
                break;

            case 3:
                displayQueue(queue);
                break;

            case 4:
                printf("Digite o elemento a ser consultado: ");
                scanf("%d", &target);
                position = searchElement(queue, target);
                if (position != -1) {
                    printf("Elemento %d encontrado na posição %d.\n", target, position);
                } else {
                    printf("Elemento %d não encontrado na fila.\n", target);
                }
                break;

            case 5:
                printf("Digite a posição para inserção: ");
                scanf("%d", &position);
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &data);
                insertElement(queue, position, data);
                break;

            case 6:
                printf("Digite a posição para modificação: ");
                scanf("%d", &position);
                printf("Digite o novo valor: ");
                scanf("%d", &data);
                modifyElement(queue, position, data);
                break;

            case 7:
                printf("Digite a posição para exclusão: ");
                scanf("%d", &position);
                deleteElement(queue, position);
                break;

            case 8:
                printf("Digite o nome do arquivo para salvar: ");
                scanf("%s", filename);
                saveQueue(queue, filename);
                break;

            case 9:
                printf("Digite o nome do arquivo para carregar: ");
                scanf("%s", filename);
                loadQueue(queue, filename);
                break;

            case 10:
                resetQueue(queue);
                printf("A fila foi reinicializada.\n");
                break;

            case 0:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 0);

    // Liberar a memória alocada para a fila antes de sair do programa
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);

    return 0;
}

