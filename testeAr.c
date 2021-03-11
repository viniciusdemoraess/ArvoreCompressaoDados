//Leitura de arquivo
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LinkedList.c"
bool compara(void *data1, void *data2) {
    char *d1 = (char*)data1;
    char *d2 = (char*)data2;
    
    return (*d1==*d2)?true:false;
}
int main(void){
  LinkedList lista;
  init(&lista);
  FILE *Arq;
  const char *c;  
  //abrindo o arquivo_frase em modo "somente leitura"
  Arq = fopen("KAKA.txt", "r");
  printf("ENTREI ARQUIVO");
  //leitura letra por letra do texto
  do{
    c = fgetc(Arq);
    //printf("%c", c);
    if(!isspace(*c)){
      if(isEmpty(&lista)){
       // printf("ENTREI PRIMEIRO");
        enqueue(&lista, &c, 1);
      }else{
        if(indexOf(&lista, &c, compara)){
           // printf("ENTREI CU");
            frequencia(&lista, &c, compara);
        }else{          
         // printf("ENTREI BUNDA");
          enqueue(&lista, &c, 1);
        }  
      }        
    }
   // printf("ENTREI");
  }while( c != '\0');  
  printa(&lista);
  //fechando o arquivo
  fclose(Arq);
  
  return(0);
}