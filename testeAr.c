//Leitura de arquivo
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
  FILE *Arq;
  char *c;  
  //abrindo o arquivo_frase em modo "somente leitura"
  Arq = fopen("KAKA.txt", "r");
  //leitura letra por letra do texto
  do{
    c = getc(Arq);
    if(!isspace(c))
      printf("%c\n", c);
  }while( c != EOF);
    //fechando o arquivo
  fclose(Arq);
  
  return(0);
}