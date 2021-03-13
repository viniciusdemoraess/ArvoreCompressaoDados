#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "ArvCompress.h"


nodeLista *novoNodeLista(nodeArvore *noArv){
    nodeLista *novo;
    if ( (novo = malloc(sizeof(*novo))) == NULL ) return NULL;

    // Adiciona a árvore ao nó
    novo->n = noArv;

    novo->proximo = NULL;

    return novo;
}


// Funcao para criar um novo no da arvore
nodeArvore *novoNodeArvore(byte c, int frequencia, nodeArvore *esquerda, nodeArvore *direita){
    nodeArvore *novo;
    if ( ( novo = malloc(sizeof(*novo)) ) == NULL ) return NULL;

    novo->c = c;
    novo->frequencia = frequencia;
    novo->esquerda = esquerda;
    novo->direita = direita;

    return novo;
}


//funcao para inserir na lista os elementos em ordem crescente do seu numero de frequencia 
void insereLista(nodeLista *n, lista *l){
    if (!l->head){
        l->head = n;
    }

    // Se o campo frequencia do no parametro for menor que o campo frequencia do head da lista
    // incluir esse novo parametro como o novo head
    else if (n->n->frequencia < l->head->n->frequencia){
        n->proximo = l->head;
        l->head = n;
    }
    else{
        nodeLista *aux = l->head->proximo;
        nodeLista *aux2 = l->head;

        // Laço que percorre a lista e insere o nó na posição certa de acordo com sua frequência.
        while (aux && aux->n->frequencia <= n->n->frequencia){
            aux2 = aux;
            aux = aux2->proximo;
        }

        // Aqui sera inserido o no na posicao correta 
        aux2->proximo = n;
        n->proximo = aux;
    }
    l->elementos++;
}


//funcao que retira o head da lista no caso o de menor frequencia
nodeArvore *popMinLista(lista *l){

    nodeLista *aux = l->head;
    nodeArvore *aux2 = aux->n;

    l->head = aux->proximo;

    free(aux);
    aux = NULL;

    l->elementos--;

    return aux2;
}

//Funcao para verificar a frequencia de cada byte
void getByteFrequency(FILE *entrada, unsigned int *listaBytes){ 

    byte c;
    
    while (fread(&c, 1, 1, entrada) >= 1){
        c = toupper(c);
        listaBytes[(byte)c]++;
    }
    rewind(entrada); // Volta ao inicio do arquivo

}




// Função recursiva que percorre uma árvore de huffman e para ao encontrar o byte procurado (c)
bool pegaCodigo(nodeArvore *n, byte c, char *buffer, int tamanho){

    // Se o nó for folha e o seu valor for o buscado, colocar o caractere terminal no buffer e encerrar
    if (!(n->esquerda || n->direita) && n->c == c){
        buffer[tamanho] = '\0';
        return true;
    }
    else{
        bool encontrado = false;

        if (n->esquerda){
            buffer[tamanho] = '0';
            encontrado = pegaCodigo(n->esquerda, c, buffer, tamanho + 1);
        }

        if (!encontrado && n->direita){
            buffer[tamanho] = '1';
            encontrado = pegaCodigo(n->direita, c, buffer, tamanho + 1);
        }
        if (!encontrado){
            buffer[tamanho] = '\0';
        }
        return encontrado;
    }
}

//Constroi a famosa arvore de Huffman
nodeArvore *BuildHuffmanTree(unsigned *listaBytes){
    lista l = {NULL, 0};

    // Preenche usando o array 'listaBytes' (que contém as frequências) uma lista encadeada de nós.
    // Cada nó contém uma árvore.
    for (int i = 0; i < 256; i++){
        if (listaBytes[i]){// Se existe ocorrência do byte        
            // Insere na lista 'l' um nó referente ao byte i e sua respectiva frequência (guardada em listaBytes[i]).
            // Faz os nós esquerdo e direito das árvores apontarem para NULL;
            insereLista(novoNodeLista(novoNodeArvore(i, listaBytes[i], NULL, NULL)), &l);
        }
    }

    while (l.elementos > 1){    
        
        nodeArvore *nodeEsquerdo = popMinLista(&l);

        // Pega o outro nó que tem menor frequência
        nodeArvore *nodeDireito = popMinLista(&l);

        nodeArvore *soma = novoNodeArvore( 
                               '#',
                               nodeEsquerdo->frequencia + nodeDireito->frequencia, nodeEsquerdo, nodeDireito
                           );

        // Reinsere o nó 'soma' na lista l
        insereLista(novoNodeLista(soma), &l);
    }
    return popMinLista(&l);
}

//Funcao para avisar se foi ou nao encontrado o arquivo
void erroArquivo(){
    printf("Arquivo nao encontrado\n");
    exit(0);
}

int execution(const char *t){    
    //abrindo o arquivo txt em modo "somente leitura"
    FILE *Arq = fopen(t, "r");
    char buffer[1024] = {0}, c, vetor[256];
    int i = 0, flag=0, j=0;
    unsigned listaBytes[256] = {0};
    if(!Arq) erroArquivo();
    //armazena a frequencia de cada byte em listaBytes    
    getByteFrequency(Arq, listaBytes);
    //cria a arvore
    nodeArvore *raiz = BuildHuffmanTree(listaBytes);    
    c = getc(Arq);
    //Armazena o primeiro caracter no vetor
    vetor[i] = toupper(c);
    i++;
    do{
        c = getc(Arq);
        //Verificacao para que nao seja armazenado uma letra repetida no vetor 
        for(j=0; j<i; j++){
            if(vetor[j] == toupper(c)){
                flag=1;
            }
        }
        //Caso nao seja repetida e armazenada no vetor
        if(flag==0){
            vetor[i] = toupper(c);
            i++;
        }
        flag = 0;
    }while(c!=EOF);    
    //Mostra as Letras com seus respectivos codigos  
    printf("-----TABELA-----\n"); 
    for(j=0; j<i-1; j++){
        pegaCodigo(raiz, vetor[j], buffer, 0);  
        printf("%c     ", vetor[j]);
         for(char *i=buffer; *i; i++){
            printf("%c", *i);
        } 
        printf("\n");
    }
    fclose(Arq);
}

