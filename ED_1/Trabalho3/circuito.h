typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
void libera_NO(struct NO* no);
int insere_ArvBin(ArvBin* raiz, char pai[], char lado[], char filho[]);
struct NO *procura_pai(ArvBin *raiz, char pai[], struct NO *no_pai);
void preOrdem_ArvAVL(ArvBin *raiz);
void acha_sigla(ArvBin *raiz, char *sigla);
void confere_folhas(ArvBin *raiz);
void insere_valor_INP(ArvBin *raiz, int valor, char no[], int flag);
void insere_valor_NOT(ArvBin *raiz, int flag);
void insere_valor_AND(ArvBin *raiz, int flag);
void insere_valor_OR(ArvBin *raiz, int flag);
void insere_valor_OUTPUT(ArvBin *raiz);
void imprime_saida(ArvBin *raiz);
