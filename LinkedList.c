#include <stdio.h>
 #include <stdlib.h>
 #include "LinkedList.h"

//Init feito para inicializar a lista/fila
void init(LinkedList *list) {
    list->first=NULL;
    list->size=0;

}

int enqueue(LinkedList *list, void *data, int *freq) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->data = data;
    newNode->freq = freq;
    newNode->next = NULL;
    if (isEmpty(list))            //se a lista estiver vazia
        list->first = newNode;    //novo nó é o primeiro
    else {
        Node *aux = list->first;  //aux aponta para o primeiro
        while (aux->next != NULL) //enquanto não for o último nó
            aux = aux->next;      //aux avança para o nó seguinte
        aux->next = newNode;      //último nó aponta para o novo nó
    }
    list->size++;
    return 1;
}

int freq(LinkedList *list){ //Verificar isso daqui**************
    if(isEmpty(list)) return 0;
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->freq++; 
}

//Verifica se a lista está vazia
bool isEmpty(LinkedList *list){
    return(list->size==0);
}

int indexOf(LinkedList *list, void *data, int *freq, compare equal) {
    if (isEmpty(list)) return -1;
    int count=0;
    Node *aux = list->first;
   
    while(aux!=NULL && !equal(aux->data,data)) {
        aux=aux->next;
        count++;
    }
    return (aux==NULL)?-1:count;
}
