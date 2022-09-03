#include<stdio.h>
#include<stdlib.h>

int main(int argc, char argv[]){
   FILE *f = fopen("arquivos.txt", "r");
   if(f == NULL){
      puts("ERRO");
      exit(-1);
   }

   float *arr = (float *) calloc(100, sizeof(float));
   int i = 0;

   while(arr[i - 1] != -100){
      fscanf(f, "%f", &arr[i]);
      printf("%f ", arr[i]);
      i++;
   }
   puts("");
   fclose(f);
   free(arr);
   
}