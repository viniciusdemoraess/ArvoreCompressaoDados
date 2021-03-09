//Leitura de arquivo
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LinkedList.c"
bool compara(void *data1, void *data2) {
    int *d1 = (int*)data1;
    int *d2 = (int*)data2;
    
    return (*d1==*d2)?true:false;
}
int main(void){
  LinkedList lista;
  init(&lista);
  FILE *Arq;
  char *c;  
  //abrindo o arquivo_frase em modo "somente leitura"
  Arq = fopen("KAKA.txt", "r");
  //leitura letra por letra do texto
  do{
    c = getc(Arq);
    if(!isspace(c)){
      if(isEmpty(&lista)){
        add(&lista, 0, c, 1);
      }else{
        if(indexOf(&lista, c, compara)){
            freq(&lista);
        }else{          
          add(&lista, 0, c, 1);
        }  
      }
        
    }
  }while( c != '\0');  
  //fechando o arquivo
  fclose(Arq);
  
  return(0);
}