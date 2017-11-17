#include <iostream>
#include <stdlib.h>

using namespace std;

// Nó - Representa um elemento da lista

struct node {
    char data;
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
  * Libera Memoria do No
  */
void freeNode(Node *p) {
    delete(p);
    return;
}

/**
 * Função que imprime o No
 */
Node *printNode(Node *p) {
    cout << p->data;
    cout << "-";
}

// Estrutura da Lista
typedef struct {
    int lenght;
    Node *front;
    Node *rear;
} List;

/* Operações sobre uma Lista */
List *newList() {
    List *p;
    p = new List();
    p->lenght = 0;
    p->front = NULL;
    p->rear = NULL;
    return p;
}

/**
 * Função que traz o proximo no da pilha
 */
Node *nextNode(Node *p) {
    return p->next;
}

/**
 * Função que limpa a pilha
 */// Inserindo no início da pilha
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
    p->lenght = 0;
    return p;
}

/**
 * Função que libera a memoria da pilha
 */
void freeList(List *p) {
    // Memória usada por cada nó
    clearList(p);
    // Memória usada pela estrutura
    delete(p);
    return;
}

/**
 * Função que verifica se a pilha está vazia
 */
int emptyList(List *p) {
    if (p->front == NULL)
        return true;
    else
        return false;
}

/**
 * Funcao que imprime a Pilha
 */
List *printList(List *p) {
    Node *q;
    if (emptyList(p)) {
        cout << "A lista está vazia!";
        return p;
    }
    q = p->front;
    while (q != NULL) {
        printNode(q);
        q = nextNode(q);
    }
    cout << endl;
    return p;
}

/**
 * Funcao que insere um nó encima da pilha
 */
List *insertAtFront(List *p, char n) {// Inserindo no início da pilha

    Node *q;
    q = newNode(n);
    q->next = p->front;
    p->front = q;
    if (p->rear == NULL)
        p->rear = q;
    p->lenght += 1;
    return p;
}

/**
 * Funcao que inserer um novo no no final na pilha
 */
List *insertAfter(List *p, Node *w, char n) {
    Node *q;
    if (w == NULL || p->front == NULL)
        return insertAtFront(p, n);
    q = newNode(n);
    q->next = w->next;
    w->next = q;
    if (w == p->rear)
        p->rear = q;
    p->lenght += 1;
    return p;
}

/**
 *  Funcao que insere um novo no atraz da pilha
 */
List *insertAtRear(List *p, char n) {
    Node *q;
    q = p->rear;
    return insertAfter(p, q, n);
}

/**
 * Funcao que remove o no de cima da pilha
 */
int removeFromFront(List *p) {
    int n;
    Node *q;
    if (emptyList(p)) {
        cout << endl << "Underflow na lista";
        exit(EXIT_FAILURE);
    }
    n = p->front->data;
    q = p->front;
    p->front = p->front->next;
    freeNode(q);
    if (p->front == NULL)
        p->rear = NULL;// Inserindo no início da pilha
    p->lenght -= 1;
    return n;
}

/**
 * Funcao que procura um determinado no na pilha
 */
Node *findInList(List *p, char n) {
    Node *q;
    q = p->front;
    while (q != NULL) {
        if (q->data == n)// Inserindo no início da pilha
            break;
        q = nextNode(q);
    }
    // retorna NULL se não for encontrado.
    return q;
}

int compare(List *x, List *y, int ref) {
    Node *q, *w;
    q = x->front;
    w = y->front;
    for(int i = 0; i < ref; i++) {
        if(q->data != w->data)
            return false;
        q = nextNode(q);
        w = nextNode(w);
    }
    return true;
}

/**
 * Função que verifica se esta no formato
 */
int verify(List *p) {
    List *x, *y;
    Node *q;
    int ref, cont;
    if (p->lenght % 2 == 0) {
        x = newList();
        y = newList();
        cont = 0;
        ref = p->lenght / 2;
        q = p->front;
        for(cont = 0; cont <= p->lenght; cont++) {
            if(cont <= ref) {
                insertAtFront(x, q->data);
            } else {
                insertAtRear(y, q->data);
            }
            q = nextNode(q);
        }
        return compare(x, y, ref);
    } else
        return false;
}

/**
 * Funcao Principal do programa
 */
int main(int argc, char** argv) {
    List *p;
    char elem;
    string nome;

    // Criando uma nova pilha
    p = newList();

    // Inserindo dados na pilha
    cout << "Digite uma palavra: ";
    cin >> nome;
    for(int i = 0; i < sizeof(nome); i++){
        elem = nome[i];

        // Inserindo no início da pilha
         insertAtFront(p, elem);
    }

    // Exibindo a pilha
    cout << "A lista \n";
    printList(p);

    if(verify(p)) {
        cout << "segue a regra onde Y é o reverso de X\n";
    } else {
        cout << "Não segue a regra do espelhamento\n";
    }

    return 0;
}
