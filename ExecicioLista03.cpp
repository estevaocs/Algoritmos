#include <iostream>
#include <stdlib.h>

using namespace std;

// No - Representa um elemento da lista

/**
 * Estrutura do no
 */
struct node {
    int data;
    struct node *next;
};

typedef struct node Node;
typedef Node *Ptrnode;

/* Operacoes sobre um no */
Node *newNode(int n) {
    Node *q;
    q = new Node();
    q->data = n;
    q->next = NULL;
    return q;
}

/**
 * Liberando memoria do No
 */
void freeNode(Node *p) {
    delete(p);
    return;
}

/**
 * Funcao que imprime no
 */
Node *printNode(Node *p) {
    cout << p->data;
}

// Estrutura da Lista

typedef struct {
    Node *front;
    Node *rear;
} List;

// Estrutura de um grupo de duas filas f1 e f2
typedef struct {
	List *f1;
	List *f2;
} Group;

/* Operac鮡s sobre uma fila */
/**
 * Funcao que cria uma nova fila vazia
 */
List *newList() {
    List *p;
    p = new List();
    p->front = NULL;
    p->rear = NULL;
    return p;
}

/* Operac鮡s sobre uma fila */
/**
 * Funcao que cria uma nova fila vazia
 */
Group *newGroup() {
    Group *g;
    g = new Group();
    g->f1 = newList();
    g->f2 = newList();
    return g;
}

/**
 * Funcao que retorna a o proximo no da fila
 */
Node *nextNode(Node *p) {
    return p->next;
}

/**
 * Funcaoo que limpa todos os nos da fila
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
 * Funcao que libera a memoria utilizada por uma lista
 */
void freeList(List *p) {
    // Mem贸ria usada por cada n贸
    clearList(p);
    // Mem贸ria usada pela estrutura
    delete(p);
    return;
}

/**
 * Funcao que libera a memoria utilizada por uma lista
 */
void freeGroup(Group *g) {
    // Mememoria usada por cada no
    clearList(g->f1);
    // Mememoria usada pela estrutura
    delete(g->f1);
     // Mememoria usada por cada no
    clearList(g->f2);
    // Mememoria usada pela estrutura
    delete(g->f2);
    return;
}

/**
 * Funcao que verifica se a lista esta vazia
 */
int emptyList(List *p) {
    if (p->front == NULL)
        return true;
    else
        return false;
}

/**
 * funcao que printa a Lista
 */
List *printList(List *p) {
    Node *q;
    if (emptyList(p)) {
        cout << "A fila esta vazia!\n";
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
 * Fun莽茫o que instancia o ponteiro de referencia do proximo n贸 da fila
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
 * Fun莽玫es que insere um novo n贸 na fila
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
 * Funcao que instancia o ponteiro de referencia ao no anterior da fila
 */
List *insertAtRear(List *p, int n) {
    Node *q;
    q = p->rear;
    return insertAfter(p, q, n);
}

/**
 * Funcao que remove o primeiro no da fila
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
 * Fun玢o passa o node q de uma fila f para outra fila p
 */
Node *insertNodeInF1(List *p, Node *q, List *f) {	
	insertAtRear(p, q->data);
   	q = nextNode(q);
   	removeFromFront(f);	
	return q;
}


/**
 * Funcao cocatena as filas;
 */
Group *concatenate(Group *g) {
	List *p;
	Node *q, *w;
	int i;
	//criando fila de apoio
    p = newList();
    //pegando os primeiros nos das filas
    q = g->f1->front;
    w = g->f2->front;
    //enquanto as filas nao estiverem vazias
    while (!emptyList(g->f1) || !emptyList(g->f2)) {
		//concatenando filas
    	if(q != NULL){
    		q = insertNodeInF1(p, q, g->f1);
		}
		if(w != NULL){
			w = insertNodeInF1(p, w, g->f2);
		}
    }
    //referenciando fila de apoio p para f1;
    g->f1 = p;

    return g;
}

/**
 * Funcao que busca um determinado no na fila
 */
Node *findInList(List *p, int n) {
    Node *q;
    q = p->front;
    while (q != NULL) {
        if (q->data == n)
            break;
        q = nextNode(q);
    }
    // retorna NULL se n茫o for encontrado.
    return q;
}

List *instantiatingQueue(List *p) {
    int elem;
    cout << "\nDigite o valor do primeiro no da fila f1 ou o digito 0 para sair: ";
    cin >> elem;
    while (elem != 0) {
        // Inserindo no final da fila
        insertAtRear(p, elem);

        cout << "\nDigite o valor do proximo no da fila f1 ou 0 para sair: ";
        cin >> elem;
    }
    return p;
}

/**
 * Funcao Principal
 */
int main(int argc, char** argv) {
    Group *g;
    int elem;
    Node *q;

    g = newGroup();

    //instanciando filas
    g->f1 = instantiatingQueue(g->f1);
    g->f2 = instantiatingQueue(g->f2);

    // Exibindo filas
    cout << "\n\nfila f1 antes de concatenar: ";
        printList(g->f1);
    cout << "\n\nfila f2 antes de concatenar: ";
        printList(g->f2);

	//Se nenhuma as duas filas nao estiverem vazias
    if (!emptyList(g->f1) && !emptyList(g->f2))  
	{
		//concatenando filas
       	g = concatenate(g);
       	
        // Exibindo filas concatenadas
    	cout << "\n\nfila f1 concatenada: \n";
        printList(g->f1);
    	cout << "\n\nfila f2: \n";
        printList(g->f2);
        
    } else {
    	cout << "As filas est鉶 vazias!";
	}
	
    cout << "\n";
    system("pause");
    return 0;
}
