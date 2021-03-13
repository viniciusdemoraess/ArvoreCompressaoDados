#include <stdlib.h>
#include <stdio.h>

// Cria o tipo unsigned [0 .. 255] do tipo char
typedef unsigned char byte;

//Cria a estrutura do no da arvore
typedef struct nodeArvore{
    int                 frequencia;
    byte                c;
    struct nodeArvore   *esquerda;
    struct nodeArvore   *direita;
}nodeArvore;

//cria a estrutura dos nos da lista 
typedef struct nodeLista{
    nodeArvore          *n;
    struct nodeLista    *proximo;
} nodeLista;

//Cria a estrutura da lista
typedef struct lista{
    nodeLista   *head;
    int         elementos;
}lista;

nodeLista *novoNodeLista(nodeArvore *nArv);
nodeArvore *novoNodeArvore(byte c, int frequencia, nodeArvore *esquerda, nodeArvore *direita);
void insereLista(nodeLista *n, lista *l);
nodeArvore *popMinLista(lista *l);
void getByteFrequency(FILE *entrada, unsigned int *listaBytes);
bool pegaCodigo(nodeArvore *n, byte c, char *buffer, int tamanho);
nodeArvore *BuildHuffmanTree(unsigned *listaBytes);
void FreeHuffmanTree(nodeArvore *n);
void erroArquivo();
int execution(const char *t);


