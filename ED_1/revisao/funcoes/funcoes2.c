#include<stdio.h>
#include<stdlib.h>

void func(int *px, int *py){
    px = py;

    *py = (*py) * (*px);
    *px = *px * 2;
}

int main(int argc, char *argv[]){
    int x, y;
    
    scanf("%d", &x);
    scanf("%d", &y);

    func(&x, &y);

    printf("x = %d   y = %d\n", x, y);

    return 0;
}