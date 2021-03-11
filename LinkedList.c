#include <stdio.h>
 #include <stdlib.h>
 #include "LinkedList.h"

//Init feito para inicializar a lista/fila
void init(LinkedList *list) {
    list->first=NULL;
    list->size=0;
}

//Verifica se a lista está vazia
bool isEmpty(LinkedList *list){
    return(list->size==0);
}

void printa(LinkedList *list){
    Node *aux = list->first;
    while (aux!= NULL){
        printf("%c || %d", aux->data, aux->freq);
    }
}
//incrementa a frequencia das letras
int frequencia(LinkedList *list, void *data, compare equal){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode==NULL) return -1;
    Node *aux = list->first;
    while (aux!= NULL && !equal(aux->data, data)) {// enquanto nao chega no final da lista, e nao encontra o valor fornecido na lista, continua o loop.
        aux = aux->next; // passa para o proximo elemento.
    }
    aux->freq++; 
    newNode->freq = aux->freq;   
 
}

//Insere um elemento ao final da lista 
int enqueue(LinkedList *list, void *data, int freq){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode==NULL) return -1;
    newNode->data = data;
    newNode->freq = freq;
    newNode->next = NULL;
    if(isEmpty(list)) //se a lista estiver vazia
        list->first = newNode; //novo nó é o primeiro
    else{
        Node *aux = list->first; //aux aponta para o primeiro
        while(aux->next!=NULL) //enquanto não for o último nó
            aux = aux->next; //aux avança para o nó seguinte
        aux->next = newNode; //último nó aponta para o novo nó
    }
    list->size++;
    return 1;
}
// retorna o primeiro valor da lista by vinicius
void* first(LinkedList *list) {
    return (isEmpty(list))?NULL:list->first->data;
}
//retorna o ultimo valor da lista by vinicius
void* last(LinkedList *list) {
    void *data = NULL;
    if (!isEmpty(list)) {          //Se a lista não estiver vazia
        Node *aux = list->first;   //aux aponta para o primeiro nó
        while (aux->next != NULL)  //enquanto não for o último nó
            aux = aux->next;       //aux avança para o nó seguinte
        data = aux->data;          //endereço de memória do dado no último nó
    }
    return data;
}

//retira o primeiro elemento da fila by Mariana
void* dequeue(LinkedList *list) {
    if (isEmpty(list)) return NULL;
    Node *trash = list->first;       //variável que guarda o endereço do nó que será removido
    list->first = list->first->next; //primeiro elemento passa a ser o segundo da lista
    void *data = trash->data;        //dado do nó removido
    free(trash);
    list->size--;
    return data;
}

//para usar a pilha, reaproveita-se as operações da fila

//pop
void* pop(LinkedList *list) {
    return dequeue(list);
}

//top
void* top(LinkedList *list) {
    return first(list);
}

//adiciona na primeira posição um novo elemento by Mariana
int push(LinkedList *list, void *data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(list))               //se a lista estiver vazia
        list->first = newNode;       //novo nó é o primeiro
    else {
        newNode->next = list->first; //o topo atual será o segundo da lista
        list->first = newNode;       //o novo nó será o topo
    }
    list->size++;
    return 1;
}

//retorna o endereço do nó localizado em uma determinada posição da lista - by Katia
Node* getNodeByPos(LinkedList *list, int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL;  //se lista vazia, ou posição maior que a lista, retorna null
    Node *aux = list->first;   //guarda o endereço de first e guarda em uma variavel do tipo node
    for (int count=0;(aux!=NULL && count<pos);count++,aux=aux->next); //laço para encontrar a posição
    return aux; //aux guarda o endereço da posição encontrada no for
}
//retorna o conteúdo que está no endereço de nó retornado anteriormente - by Katia
void* getPos(LinkedList *list, int pos) {
    Node *aux = getNodeByPos(list,pos);
    if (aux==NULL)   //se o aux, não for nulo
        return NULL;
    else           //retorna o conteudo do nó encontrado
        return aux->data;
}

// remove um elemento da lista de uma posicao fornecida. by Leonardo
void* removePos (LinkedList *list, int pos) {
    if (isEmpty(list) || pos >=list->size)  // verifica se a lista esta vazia ou se a posicao fornecida eh invalida.
        return NULL;

    Node *nodeRemove = NULL; // variavel auxilar que aponta para o noh a ser removido.
    Node *aux = NULL; // variavel auxiliar que aponta para o noh anterior ao que sera removido.

    if (pos<=0) // verifica se eh o primeiro elemento da lista.
        return dequeue(list); // se for o primeiro podemos aproveitar a funcao dequeue.
    else
        aux = getNodeByPos(list, pos-1); // busca o elemento anterior da posicao a ser removida.

    // realiza a remocao.
    nodeRemove = aux->next;
    aux->next = nodeRemove->next; // faz com que o noh anterior aponte para o noh seguinte, pulando o elemento que sera removido.

    void* dataRemove = nodeRemove->data;// salva o valor do elemento removido.
    free(nodeRemove); // limpa o noh da memoria.
    list->size--;// diminui um do tamanho da lista.

    return dataRemove; // retorna o valor do elemento removido.
}

// retorna a posicao da lista de um elemento determinado. by Leonardo
int indexOf (LinkedList *list, void *data, compare equal){
    if (isEmpty (list)) // verifica se a lista esta vazia.
        return -1; // se estiver vazia, retorna -1, identificando que eh invalida.

    int count = 0;// variavel contadora, para as posicoes da lista.
    Node *aux = list->first; // variavel auxiliar para navegar na lista.

    while (aux!= NULL && !equal(aux->data, data)) {// enquanto nao chega no final da lista, e nao encontra o valor fornecido na lista, continua o loop.
        aux = aux->next; // passa para o proximo elemento.
        count++; // soma mais um na posicao.
    }

    return (aux==NULL) ?-1:count; // se aux igual a NULL, quer dizer que chegou no final da lista e nao encontrou o elemento, senao retorna a posicao onde parou.
}
// implementação do removeData - por Gustavo Lima
bool removeData(LinkedList *list, void *data, compare equal) {
    if (isEmpty(list)) return -1;
    Node *nodeRemove = NULL;
    if (equal(list->first->data,data)) {
        nodeRemove = list->first;
        list->first = list->first->next;
        free(nodeRemove->data);
        free(nodeRemove);
        list->size--;
        return true;
    } else {
        Node *aux = list->first;
        while(aux->next!=NULL && !equal(aux->next->data,data))
            aux=aux->next;

        if (aux->next!=NULL) {
            Node *nodeRemove = aux->next;
            aux->next = nodeRemove->next;
            free(nodeRemove->data);
            free(nodeRemove);
            list->size--;
            return true;
        } else {
            return false;
        }
    }
}

// implementação da Função Add  - por Gustavo Lima
int add(LinkedList *list, int pos, void *data) {
    if (pos <= 0) return push(list,data);
    Node *aux = getNodeByPos(list, (pos-1));
    if (aux==NULL) return -2;

    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;

    newNode->data = data;
    newNode->next = NULL;

    newNode->next = aux->next;
    aux->next = newNode;

    list->size++;

    return 1;
}