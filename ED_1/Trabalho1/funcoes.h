typedef struct _lista{
    char tipo[10];
    int tamanho;
    float *valores;
} Lista;

Lista **aloc();

Lista **le_listas();

Lista **ordena_listas();

Lista *merge_sort();

void imprime_merge();

void imprime_merge_inverso();

void destroy_caso4();