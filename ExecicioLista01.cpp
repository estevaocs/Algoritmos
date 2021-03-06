#include <iostream>
#include <stdlib.h>

using namespace std;

// Nó - Representa um elemento da lista

/**
 * Estrutura do nó
 */
struct node {
    int data;
    struct node *next;
};

typedef struct node Node;
typedef Node *Ptrnode;

/* Operações sobre um nó */
Node *newNode(int n) {
    Node *q;
    q = new Node();
    q->data = n;
    q->next = NULL;
    return q;
}

/**
 * Liberando memoria do Nó
 */
void freeNode(Node *p) {
    delete(p);
    return;
}

/**
 * Função que imprime nó
 */
Node *printNode(Node *p) {
    cout << p->data;
}

// Estrutura da Lista

typedef struct {
    Node *higher;
    int average;
    Node *front;
    Node *rear;
} List;

/* Operações sobre uma Lista */
/**
 * Função que cria uma nova lista vazia
 */
List *newList() {
    List *p;
    p = new List();
    p->higher = NULL;
    p->average = 0;
    p->front = NULL;
    p->rear = NULL;
    return p;
}

/**
 * Função que retorna a o proximo nó da fila
 */
Node *nextNode(Node *p) {
    return p->next;
}

/**
 * Função que limpa todos os nós da fila
 */
List *clearList(List *p) {
    Node *q, *w;
    q = p->front;
    while (q != NULL) {
        w = nextNode(q);
        freeNode(q);
        q = w;
    }
    p->front = NULL;
    p->rear = NULL;
    return p;
}

/**
 * Função que libera a memoria utilizada por uma lista
 */
void freeList(List *p) {
    // Memória usada por cada nó
    clearList(p);
    // Memória usada pela estrutura
    delete(p);
    return;
}

/**
 * Função que verifica se a lista está vazia
 */
int emptyList(List *p) {
    if (p->front == NULL)
        return true;
    else
        return false;
}

/**
 * função que printa a Lista
 */
List *printList(List *p) {
    Node *q;
    if (emptyList(p)) {
        cout << "A lista está vazia!";
        return p;
    }
    q = p->front;
    while (q != NULL) {
        cout << endl;
        printNode(q);
        q = nextNode(q);
    }
    return p;
}

/**
 * Função que instancia o ponteiro de referencia do proximo nó da fila
 */
List *insertAtFront(List *p, int n) {
    Node *q;
    q = newNode(n);
    q->next = p->front;
    p->front = q;
    if (p->rear == NULL)
        p->rear = q;
    return p;
}

/**
 * Funções que insere um novo nó na fila
 */
List *insertAfter(List *p, Node *w, int n) {
    Node *q;
    if (w == NULL || p->front == NULL)
        return insertAtFront(p, n);
    q = newNode(n);
    q->next = w->next;
    w->next = q;
    if (w == p->rear)
        p->rear = q;
    return p;
}

/**
 * Função que verifica o maior numero
 */
Node *higherNumber(List *p) {
   Node *higher = NULL;
   Node *q = p->front;
   higher = q;
   while(q != NULL) {
        if(q->data > higher->data){
            higher = q;
        }
        q = nextNode(q);
   }
   return higher;
}

/**
 * Função que calcula a media aritmetica da fila
 */
int average(List *p) {
    Node *q;
    int sum, cont, avg;
    sum = 0;
    cont = 0;
    q = p->front;
    while (q != NULL) {
        sum += q->data;
        q = nextNode(q);
        cont++;
    }
    avg = sum / cont;
    return avg;
}

/**
 * Função que instancia o ponteiro de referencia ao nó anterior da fila
 */
List *insertAtRear(List *p, int n) {
    Node *q;
    q = p->rear;
    return insertAfter(p, q, n);
}

/**
 * Função que remove o primeiro nó da fila
 */
int removeFromFront(List *p) {
    int n;
    Node *q;
    if (emptyList(p)) {
        cout << endl << "Underflow na lista";
        return 0;
    }
    n = p->front->data;
    q = p->front;
    p->front = p->front->next;
    freeNode(q);
    if (p->front == NULL)
        p->rear = NULL;
    return n;
}

/**
 * Função que busca um determinado nó na fila
 */
Node *findInList(List *p, int n) {
    Node *q;
    q = p->front;
    while (q != NULL) {
        if (q->data == n)
            break;
        q = nextNode(q);
    }
    // retorna NULL se não for encontrado.
    return q;
}

/**
 * Função principal
 */
int main(int argc, char** argv) {
    List *p;
    int elem, avg;
    Node *q;

    // Criando uma nova fila
    p = newList();

    // Inserindo dados na fila
    cout << "Digite o valor do primeiro no:";
    cin >> elem;
    while (elem != 0) {
        // Inserindo no final da fila (fila)
        insertAtRear(p, elem);

        cout << "Digite o valor do proximo no ou 0 para sair:";
        cin >> elem;
    }

    // Exibindo a fila
    printList(p);
    higherNumber(p);
    average(p);

    if (!emptyList(p))  {

        // Exibindo maior numero da fila
        q = higherNumber(p);
        cout << "\nO maior numero da fila eh: ";
        printNode(q);

        // Exibir o a media dos numeros que estão na fila
        avg = average(p);
        cout << "\nA media aritmetica da fila eh: ";
        cout << avg;
    }

    system("pause");
    return 0;
}
