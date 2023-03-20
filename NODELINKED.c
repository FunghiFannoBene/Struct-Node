#include <stdio.h>
#include <stdlib.h>

// Includiamo le librerie standard per l'input/output e la gestione della memoria dinamica.

typedef struct Node {
void* data;
struct Node* next;
} Node;

// Definiamo la struttura Node, che rappresenta un nodo della lista concatenata. Il campo "data" è un puntatore generico a un qualsiasi 
// tipo di dato, mentre il campo "next" è un puntatore al prossimo nodo.

typedef struct LinkedList {
Node* head;
int size;
} LinkedList;

// Definiamo la struttura LinkedList, che rappresenta una lista concatenata. Il campo "head" è un puntatore al primo nodo della lista, 
// mentre il campo "size" indica il numero di nodi presenti nella lista.

Node* createNode(void* data) {
Node* newNode = (Node*)malloc(sizeof(Node));
newNode->data = data;
newNode->next = NULL;
return newNode;
}

// Definiamo la funzione "createNode" che serve per creare un nuovo nodo della lista concatenata. La funzione alloca la memoria per un 
// nuovo nodo, inizializza i campi "data" e "next" del nodo con i valori passati come parametro e restituisce un puntatore al nuovo nodo.
//Il motivo per cui non viene utilizzato "malloc(sizeof(type) * n of type)" nella funzione "createNode" è che in questo caso la dimensione 
// dell'allocazione dipende dal tipo di dato del campo "data", che è un puntatore generico a un qualsiasi tipo di dato. Non è possibile 
//conoscere la dimensione precisa del tipo di dato a cui si riferisce il puntatore "data" in fase di compilazione.
//Per questo motivo, viene utilizzata l'istruzione "malloc(sizeof(Node))" per allocare la memoria necessaria per il nuovo nodo, 
//indipendentemente dal tipo di dato contenuto nel campo "data". In questo modo, il puntatore "data" può essere inizializzato con un puntatore a qualsiasi tipo di dato, senza dover preoccuparsi della sua dimensione specifica.
//In sintesi, la funzione "malloc(sizeof(Node))" alloca esattamente la quantità di memoria necessaria per un'istanza della struttura "Node" 
//e non eccede mai la dimensione necessaria


void addNode(LinkedList* list, void* data) {
Node* newNode = createNode(data);
if (list->head == NULL) {
list->head = newNode;
} else {
Node* current = list->head;
while (current->next != NULL) {
current = current->next;
}
current->next = newNode;
}
list->size++;
}

// Definiamo la funzione "addNode" che serve per aggiungere un nuovo nodo alla fine della lista concatenata. La funzione crea un nuovo 
// nodo usando la funzione "createNode" e poi lo aggiunge alla fine della lista.

void removeNode(LinkedList* list, void* data) {
Node* current = list->head;
Node* prev = NULL;
while (current != NULL && current->data != data) {
prev = current;
current = current->next;
}
if (current == NULL) {
return;
}
if (prev == NULL) {
list->head = current->next;
} else {
prev->next = current->next;
}
free(current);
list->size--;
}

// Definiamo la funzione "removeNode" che serve per rimuovere un nodo dalla lista concatenata. La funzione cerca il nodo con il dato 
// specificato, lo rimuove dalla lista e libera la memoria allocata per il nodo.

void printList(LinkedList* list, void (printFunc)(void)) {
Node* current = list->head;
while (current != NULL) {
(*printFunc)(current->data);
current = current->next;
}
printf("\n");
}

// Definiamo la funzione "printList" che serve per stampare la lista concatenata. La funzione scorre tutti i nodi della lista e 
// chiama la funzione di stampa specificata per stampare il dato contenuto in ciascun nodo.

void printInt(void* data) {
printf("%d ", ((int)data));
}

int main() {
    // Create a new list and add some nodes
    LinkedList list = {NULL, 0};
    int a = 1;
    addNode(&list, &a);
    int b = 2;
    addNode(&list, &b);
    int c = 3;
    addNode(&list, &c);
    char* d = "four";
    addNode(&list, d);

    // Print the list
    printf("List: ");
    printList(&list, &printInt);

    // Remove a node from the list
    removeNode(&list, &b);

    // Print the list again
    printf("List after removing 2: ");
    printList(&list, &printString);

    return 0;
}