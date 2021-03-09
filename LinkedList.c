#include <stdio.h>
 #include <stdlib.h>
 #include "LinkedList.h"

//Init feito para inicializar a lista/fila by vinicius
void init(LinkedList *list) {
    list->first=NULL;
    list->size=0;

}

int freq(LinkedList *list){
    if(isEmpty(list)) return 0;
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;
     
    newNode->freq++; 
}

//Verifica se a lista está vazia by Naíra
bool isEmpty(LinkedList *list){
    return(list->size==0);
}


//retorna o endereço do nó localizado em uma determinada posição da lista - by Katia
Node* getNodeByPos(LinkedList *list, int pos) {
    int count;
    if (isEmpty(list) || pos>=list->size) return NULL;  //se lista vazia, ou posição maior que a lista, retorna null
    Node *aux = list->first;   //guarda o endereço de first e guarda em uma variavel do tipo node
    for (count=0;(aux!=NULL && count<pos);count++,aux=aux->next); //laço para encontrar a posição
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

// implementação da Função Add  - por Gustavo Lima
int add(LinkedList *list, int pos, void *data, int freq) {
    if (pos <= 0) return push(list,data);
    Node *aux = getNodeByPos(list, (pos-1));
    if (aux==NULL) return -2;

    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;

    newNode->data = data;
    newNode->freq = freq; 
    newNode->next = NULL;

    newNode->next = aux->next;
    aux->next = newNode;

    list->size++;    

    return 1;
}